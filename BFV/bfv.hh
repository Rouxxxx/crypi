#ifndef BFV_HH
#define BFV_HH

#include "../utils/utils.hh"
#include "seal/seal.h"
#include <vector>

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

    Ciphertext encrypt(Plaintext plain);
    Ciphertext encrypt(std::string str);

    Plaintext decrypt(Ciphertext x_encrypted);

    Ciphertext sum(Ciphertext encrypted1, Ciphertext encrypted2);
    Ciphertext multiply(Ciphertext encrypted1, Ciphertext encrypted2);

    Plaintext encode_vector(std::vector<uint64_t> vote);
    std::vector<uint64_t> decode_vector(Plaintext vector_decrypted);
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