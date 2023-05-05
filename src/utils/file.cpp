#include "file.hh"

#include <cstdio>
#include <fstream>

void create_folder_if_not_exists(std::string path)
{
    struct stat sb;
    if (stat(path.c_str(), &sb) == 0)
        return;

    std::cout << path << " folder doesn't exist. Creating.\n";
    mkdir(path.c_str(), 0777);
}

/*
    Save secret key to a specific file
*/
void save_secret_key(SecretKey secret_key, std::string path)
{
    // Delete file if already exists
    struct stat sb;
    if (stat(path.c_str(), &sb) == 0)
        remove(path.c_str());

    std::ofstream outfile(path.c_str());

    std::cout << "Saving secret key...";
    secret_key.save(outfile);
    std::cout << "Secret key saved!\n";

    outfile.close();
}

/*
    Load secret key from a specific file
*/
void load_secret_key(SEALContext& context, SecretKey secret_key,
                     std::string path)
{
    struct stat sb;
    if (stat(path.c_str(), &sb) != 0)
        return;

    std::ifstream infile(path.c_str());

    std::cout << "Importing secret key...";
    secret_key.load(context, infile);
    std::cout << "Secret key imported!\n";
}