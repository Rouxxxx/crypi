#ifndef BFV_HH
#define BFV_HH

#include <sstream>
#include <vector>

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

    Ciphertext encrypt(Plaintext plain);
    Ciphertext encrypt(std::string str);

    Plaintext decrypt(Ciphertext x_encrypted);

    Ciphertext sum(Ciphertext encrypted1, Ciphertext encrypted2);
    Ciphertext multiply(Ciphertext encrypted1, Ciphertext encrypted2);

    Plaintext encode_vector(std::vector<uint64_t> vote);
    std::vector<uint64_t> decode_vector(Plaintext vector_decrypted);

    void save_votes(Ciphertext ciphertext);
    void save_vote_count(Ciphertext ciphertext);

    Ciphertext load_cipher(std::string path);

    Ciphertext load_votes();
    Ciphertext load_vote_count();

    bool test_if_votes_exists();
    bool test_if_vote_count_exists();
    SEALContext context;
    Infos infos_struct;

private:
    Evaluator evaluator;
    SecretKey secret_key;
    PublicKey public_key;

    KeyGenerator keygen;
};

std::string uint64_to_hex_string(std::uint64_t value);
Container build_context(Infos infos);
void print_parameters(const SEALContext& context);
Ciphertext encrypt_number(Container* container, std::uint64_t value);
int hex_to_int(std::string hexString);

#endif