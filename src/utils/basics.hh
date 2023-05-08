#ifndef BASICS_HH
#define BASICS_HH

#include <cstdint>
#include <fstream>
#include <stddef.h>
#include <string>

#include "nlohmann_json.hpp"

inline int hex_to_int(std::string hexString)
{
    int intValue;
    std::stringstream ss;
    ss << std::hex << hexString;
    ss >> intValue;

    return intValue;
}

class Infos
{
public:
    size_t poly_modulus_degree;
    uint64_t plain_modulus;
    std::string data_folder;
    std::string secret_key_file;
    std::string vote_count_file;
    std::string votes_file;
    void build_static_info(std::string path)
    {
        std::ifstream f(path);
        nlohmann::json data = nlohmann::json::parse(f);

        poly_modulus_degree = data.value("poly_modulus_degree", 0);
        plain_modulus = data.value("plain_modulus", 0);

        data_folder = data.value("data_folder", ".");
        secret_key_file = data.value("secret_key_file", ".");

        vote_count_file = data.value("vote_count_file", ".");
        votes_file = data.value("votes_file", ".");
    }
};

#endif