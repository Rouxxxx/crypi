#ifndef FILE_HH
#define FILE_HH

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sys/stat.h>

#include "seal/seal.h"

using namespace seal;

bool test_if_file_exists(std::string path);

void create_folder_if_not_exists(std::string path);
void save_secret_key(SecretKey secret_key, std::string path);
void load_secret_key(SEALContext& context, SecretKey secret_key,
                     std::string path);

void save_ciphertext(Ciphertext ciphertext, std::string path);
Ciphertext load_ciphertext(SEALContext& context, std::string path);

#endif