#include "jsonLib.hh"
#include <fstream>
#include <iostream>
#include <sstream>

JsonLib::JsonLib(const std::string& path) {
    // Open the JSON file
    std::ifstream json_file(path);
    if (!json_file.is_open()) {
        std::cerr << "Error: Unable to open file " << path << std::endl;
        return;
    }

    // Read the JSON file
    std::stringstream buffer;
    buffer << json_file.rdbuf();
    content = buffer.str();
}

std::string JsonLib::build_string(const std::string& key, bool is_string = false) {
    // Find key in JSON string
    size_t key_pos = content.find("\"" + key + "\"");
    if (key_pos == std::string::npos) {
        std::cerr << "Error: Key \"" << key << "\" not found in JSON file" << std::endl;
        return "";
    }

    // Find value of key in JSON string
    size_t value_pos = content.find(":", key_pos);
    if (value_pos == std::string::npos) {
        std::cerr << "Error: Value of key \"" << key << "\" not found in JSON file" << std::endl;
        return "";
    }

    if (is_string) {
        value_pos = content.find("\"", value_pos + 1);
            if (value_pos == std::string::npos) {
            std::cerr << "Error: non termined string in JSON file" << std::endl;
            return "";
        }
    }

    // Cut the first part of the file content (before value)
    std::string substring = content.substr(value_pos + 1);
    std::size_t next_quote_pos;

    // Find the terminator of the value
    if (is_string)
        next_quote_pos = substring.find("\"");
    else {
        next_quote_pos = substring.find(",", 0);
        if (next_quote_pos == std::string::npos)
            next_quote_pos = substring.find("}", 0);
    }

    if (value_pos == std::string::npos) {
        std::cerr << "Error: non termined value / string in JSON file" << std::endl;
        return "";
    }

    // Cut the second part of the file content (after value)
    substring.erase(next_quote_pos, substring.size());

    return substring;
}

bool JsonLib::readUint64(const std::string& key, uint64_t& value) {
    std::string substring = build_string(key);
    if (substring == "")
        return false;

    // Parse uint64_t value
    try {
        value = static_cast<uint64_t>(std::stoull(substring));
    } catch (const std::exception& e) {
        std::cerr << "Error: Unable to parse uint64_t value for key \"" << key << "\" in JSON file" << std::endl;
        return false;
    }

    return true;
}

bool JsonLib::readInt(const std::string& key, int& value) {
    std::string substring = build_string(key);
    if (substring == "")
        return false;

    // Parse integer value
    try {
        value = std::stoi(substring);
    } catch (const std::exception& e) {
        std::cerr << "Error: Unable to parse integer value for key \"" << key << "\" in JSON file" << std::endl;
        return false;
    }

    return true;
}


bool JsonLib::readString(const std::string& key, std::string& value) {
    std::string substring = build_string(key, true);
    if (substring == "")
        return false;

    // Set output parameter
    value = substring;

    return true;
}