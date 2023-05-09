#include "jsonLib.hh"
#include <fstream>
#include <iostream>
#include <sstream>

JsonLib::JsonLib(const std::string& path) {
    std::ifstream json_file(path);
    if (!json_file.is_open()) {
        std::cerr << "Error: Unable to open file " << path << std::endl;
        return;
    }

    std::stringstream buffer;
    buffer << json_file.rdbuf();
    file = buffer.str();
}

bool JsonLib::readUint64(const std::string& key, uint64_t& value) {
    // Find key in JSON string
    size_t key_pos = file.find("\"" + key + "\"");
    if (key_pos == std::string::npos) {
        std::cerr << "Error: Key \"" << key << "\" not found in JSON file" << std::endl;
        return false;
    }

    // Find value of key in JSON string
    size_t value_pos = file.find(":", key_pos);
    if (value_pos == std::string::npos) {
        std::cerr << "Error: Value of key \"" << key << "\" not found in JSON file" << std::endl;
        return false;
    }

    // Parse uint64_t value
    try {
        value = static_cast<uint64_t>(std::stoull(file.substr(value_pos + 1)));
    } catch (const std::exception& e) {
        std::cerr << "Error: Unable to parse uint64_t value for key \"" << key << "\" in JSON file" << std::endl;
        return false;
    }

    return true;
}


bool JsonLib::readString(const std::string& key, std::string& value) {
    // Find key in JSON string
    size_t key_pos = file.find("\"" + key + "\"");
    if (key_pos == std::string::npos) {
        std::cerr << "Error: Key \"" << key << "\" not found in JSON file" << std::endl;
        return false;
    }

    // Find value of key in JSON string
    size_t value_pos = file.find(":", key_pos);
    if (value_pos == std::string::npos) {
        std::cerr << "Error: Value of key \"" << key << "\" not found in JSON file" << std::endl;
        return false;
    }

    size_t next_quote_pos = file.find("\"", value_pos + 1);
    if (value_pos == std::string::npos) {
        std::cerr << "Error: Non terminated string in JSON at pos " << value_pos << std::endl;
        return false;
    }

    // Extract string value
    std::string value_str = file.substr(value_pos + 3);

    next_quote_pos = value_str.find("\"", 0);
    value_str.erase(next_quote_pos, value_str.size());

    // Set output parameter
    value = value_str;

    return true;
}