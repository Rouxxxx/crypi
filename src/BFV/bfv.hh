#ifndef BFV_HH
#define BFV_HH

#include <sstream>
#include <vector>

#include "../utils/utils.hh"
#include "seal/seal.h"

using namespace seal;

class Container
{
    /**
    Class to store our BFV structure.

    @par Memory Management

    @par Thread Safety

    @see Plaintext for the class that stores plaintexts.
    */
public:
    /**
    Constructs the Container using an info struct, to keep track of the important files.
    */
    Container(Infos infos);



    /**
    Initiates public and secret key, and store them in the current container.
    */
    void init_secret_key();
    void init_public_key();



    /**
    Saves/Load the secret key.
    @param[in] path If we want a specific path not mentionned in the JSON file loaded, use this one instead
    */
    void save_secret();
    void save_secret(std::string path);

    void load_secret();
    void load_secret(std::string path);



    /**
    Pretty prints the container
    */
    void print_parameters();



    /**
    Encrypts a message with our public key. Returns the computed Ciphertext
    @param[in] str A basic string, which will be converted into a Plaintext before encryption
    @param[in] plain The plaintext we want to encrypt
    */
    Ciphertext encrypt(std::string str);
    Ciphertext encrypt(Plaintext plain);
    


    /**
    Decrypts a message with our secret key. Returns the computed Plaintext
    @param[in] x_encrypted The encrypted Ciphertext
    */
    Plaintext decrypt(Ciphertext x_encrypted);



    /**
    Computes the desired homomorphic operations (x1 + x2) and (x1 * x2).
    Returns the computed sum / multiple
    @param[in] encrypted1 The first encrypted Ciphertext (x1)
    @param[in] encrypted2 The first encrypted Ciphertext (x2)
    */
    Ciphertext sum(Ciphertext encrypted1, Ciphertext encrypted2);
    Ciphertext multiply(Ciphertext encrypted1, Ciphertext encrypted2);



    /**
    Encode a vector into a plaintext (vector -> plaintext)
    Returns the computed plaintext
    @param[in] vote the current vector
    */
    Plaintext encode_vector(std::vector<uint64_t> vote);
    /**
    Decodes a plaintext into a vector (plaintext -> vector)
    Returns our previously encoded vector
    @param[in] vector_decrypted The plaintext
    */
    std::vector<uint64_t> decode_vector(Plaintext vector_decrypted);



    /**
    Saved the encrypted votes sum to a file
    @param[in] ciphertext The ciphertext containing the votes
    */
    void save_votes(Ciphertext ciphertext);
    /**
    Saved the encrypted number of votes to a file
    @param[in] ciphertext The ciphertext containing the votes nb
    */
    void save_vote_count(Ciphertext ciphertext);


    /**
    Load encrypted ciphertext from a specific file
    @param[in] path The file containing the ciphertext
    */
    Ciphertext load_cipher(std::string path);
    /**
    Load votes and votes count thanks to the path contained in the JSON file
    */
    Ciphertext load_votes();
    Ciphertext load_vote_count();
    /**
    Test if the previous files exists before loading them
    */
    bool test_if_votes_exists();
    bool test_if_vote_count_exists();
    SEALContext context;

    /**
    Struct containing important values for our BFV, such as file paths and poly_modulus_degree
    @see Infos for more informations.
    */
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