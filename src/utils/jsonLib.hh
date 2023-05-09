#ifndef MY_JSON_LIB_H
#define MY_JSON_LIB_H

#include <string>

class JsonLib {
public:
    JsonLib(const std::string& filename);

    bool readUint64(const std::string& key, uint64_t& value);
    bool readString(const std::string& key, std::string& value);

private:
    std::string file;
};

#endif // MY_JSON_LIB_H
