#ifndef BFV_HH
#define BFV_HH

#include "../utils/utils.hh"
#include "seal/seal.h"

using namespace seal;

class Container
{
public:
    Container(Infos infos);
    void init_secret_key();
    void init_public_key();

    void save_secret();
    void save_secret(std::string path);

    void load_secret();
    void load_secret(std::string path);

    void print_parameters();

    Ciphertext encrypt(std::string str);
    std::string decrypt(Ciphertext x_encrypted);
private:
    SecretKey secret_key;
    PublicKey public_key;
    SEALContext context;
    KeyGenerator keygen;
    Infos infos_struct;
};

Container build_context(Infos infos);
void print_parameters(const SEALContext &context);

#endif