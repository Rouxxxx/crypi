#ifndef FILE_HH
#define FILE_HH

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sys/stat.h>

#include "nlohmann_json.hpp"
#include "seal/seal.h"

using namespace seal;

void create_folder_if_not_exists(std::string path);
void save_secret_key(SecretKey secret_key, std::string path);
void load_secret_key(SEALContext& context, SecretKey secret_key,
                     std::string path);

#endif