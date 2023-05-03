#ifndef BASICS_HH
#define BASICS_HH

#include <stddef.h>
#include <cstdint>
#include <string>
#include <fstream>

#include "nlohmann_json.hpp"


class Infos {
public :
    size_t poly_modulus_degree;
    uint64_t plain_modulus;
    std::string data_folder;
    std::string secret_key_file;
    void build_static_info(std::string path) {
        std::ifstream f(path);
        nlohmann::json data = nlohmann::json::parse(f);

        poly_modulus_degree = data.value("poly_modulus_degree", 0);
        plain_modulus = data.value("plain_modulus", 0);

        data_folder = data.value("data_folder", ".");
        secret_key_file = data.value("secret_key_file", ".");
   }
};

#endif