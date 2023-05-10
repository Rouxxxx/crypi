#ifndef FILE_HH
#define FILE_HH

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sys/stat.h>

#include "seal/seal.h"

using namespace seal;

/**
Tests if a file exists.
@param[in] path The file path
@return True if we found the file / False otherwise
*/
bool test_if_file_exists(std::string path);

/**
Ensures a folder exists in our architecture.
@param[in] path The folder path
*/
void create_folder_if_not_exists(std::string path);

/**
Saves a secret key to a specific file.
@param[in] secret_key The secret key to be saved
@param[in] path The file where the key will be stored
*/
void save_secret_key(SecretKey secret_key, std::string path);

/**
Loads a secret key from a specific file.
@param[in] context The current BFV's context (to check if the secret key is valid)
@param[in] secret_key The secret key to be loaded
@param[in] path The file where the key is stored
*/
void load_secret_key(SEALContext& context, SecretKey secret_key,
                     std::string path);

/**
Saves a ciphertext to a specific file.
@param[in] ciphertext The ciphertext to be saved
@param[in] path The file where the ciphertext will be stored
*/
void save_ciphertext(Ciphertext ciphertext, std::string path);
/**
Loads a ciphertext from a specific file.
@param[in] context The current BFV's context (to check if the ciphertext key is valid)
@param[in] path The file where the ciphertext is stored
@return The loaded ciphertext
*/
Ciphertext load_ciphertext(SEALContext& context, std::string path);

#endif