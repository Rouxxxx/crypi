#ifndef MY_JSON_LIB_H
#define MY_JSON_LIB_H

#include <string>

/**
Class to store a JSON file content and read its values.
*/
class JsonLib {
public:
    /**
    Constructs the class by reading the JSON file content.
    @param[in] path The path of the JSON file
    */
    JsonLib(const std::string& path);

    /**
    Finds key from the content stored and casts the result as an int.
    @param[in] key The name of the key in the JSON
    @param[in] value The value which will store the result
    @return True if we found the key / False otherwise
    */
    bool readInt(const std::string& key, int& value);
    /**
    Finds key from the content stored and casts the result as an uint64.
    @param[in] key The name of the key in the JSON
    @param[in] value The value which will store the result
    @return True if we found the key / False otherwise
    */
    bool readUint64(const std::string& key, uint64_t& value);
    /**
    Finds key from the content stored and casts the result as a string.
    @param[in] key The name of the key in the JSON
    @param[in] value The value which will store the result
    @return True if we found the key / False otherwise
    */
    bool readString(const std::string& key, std::string& value);

    /**
    Builds the file string before casting the value
    @param[in] key The name of the key in the JSON
    @param[in] is_string Check if the value in the JSON is a string (surrounded by ") or an int
    @return Empty string if it wasn't found, otherwise the value
    */
    std::string build_string(const std::string& key, bool is_string);

private:
    std::string content;
};

#endif // MY_JSON_LIB_H
