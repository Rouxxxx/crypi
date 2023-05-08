#include "file.hh"

#include <cstdio>
#include <fstream>

bool test_if_file_exists(std::string path)
{
    struct stat sb;
    return (stat(path.c_str(), &sb) == 0);
}

void create_folder_if_not_exists(std::string path)
{
    if (test_if_file_exists(path))
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
    if (test_if_file_exists(path))
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
    if (!test_if_file_exists(path))
        return;

    std::ifstream infile(path.c_str());

    std::cout << "Importing secret key...";
    secret_key.load(context, infile);
    std::cout << "Secret key imported!\n";
}



/*
    Save ciphertext to a specific file
*/
void save_ciphertext(Ciphertext ciphertext, std::string path)
{
    // Delete file if already exists
    if (test_if_file_exists(path))
        remove(path.c_str());


    std::cout << "Saving ciphertext " << path << "...";

    std::ofstream outfile(path, std::ios::binary);
    ciphertext.save(outfile);
    outfile.close();

    std::cout << "Ciphertext saved!\n";
}

Ciphertext load_ciphertext(SEALContext& context,
                     std::string path)
{
    Ciphertext ciphertext;
    if (!test_if_file_exists(path))
        return ciphertext;

    std::cout << "Importing ciphertext " << path << "...";

    std::ifstream infile(path, std::ios::binary);
    ciphertext.load(context, infile);
    infile.close();

    std::cout << "Ciphertext imported!\n";

    return ciphertext;
}