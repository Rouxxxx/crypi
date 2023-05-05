#include "bfv.hh"
#include <cstdlib>

/*
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#
#              Container
#
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
*/

// See https://github.com/microsoft/SEAL/blob/main/native/examples/1_bfv_basics.cpp

SEALContext set_context(Infos infos)
{
    EncryptionParameters parms(scheme_type::bfv);
    parms.set_poly_modulus_degree(infos.poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::BFVDefault(infos.poly_modulus_degree));
    //parms.set_plain_modulus(infos.plain_modulus);
    parms.set_plain_modulus(PlainModulus::Batching(infos.poly_modulus_degree, 20)); // Batching enabled


    return SEALContext(parms);
}


Container::Container(Infos infos)
    : context(set_context(infos)), keygen(KeyGenerator(context))
{
    infos_struct = infos;
}

/*
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#
#            Keys handling
#
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
*/

void Container::init_secret_key()
{
    secret_key = keygen.secret_key();
}
void Container::init_public_key()
{
    keygen.create_public_key(public_key);
}

void Container::save_secret()
{
    create_folder_if_not_exists(infos_struct.data_folder);
    save_secret(infos_struct.data_folder + "/" + infos_struct.secret_key_file);
}
void Container::save_secret(std::string path)
{
    save_secret_key(secret_key, path);
}

void Container::load_secret()
{
    create_folder_if_not_exists(infos_struct.data_folder);
    load_secret(infos_struct.data_folder + "/" + infos_struct.secret_key_file);
}
void Container::load_secret(std::string path)
{
    load_secret_key(context, secret_key, path);
}


/*
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#
#             Operations
#
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
*/

Ciphertext Container::encrypt(Plaintext plain)
{
    Encryptor encryptor(context, public_key);
    Ciphertext encrypted;
    encryptor.encrypt(plain, encrypted);

    return encrypted;
}
Ciphertext Container::encrypt(std::string str)
{
    return encrypt(Plaintext(str));
}

Plaintext Container::decrypt(Ciphertext x_encrypted)
{
    Plaintext x_decrypted;

    Decryptor decryptor(context, secret_key);
    decryptor.decrypt(x_encrypted, x_decrypted);
    
    return x_decrypted;
}

Ciphertext Container::sum(Ciphertext encrypted1, Ciphertext encrypted2)
{
    Ciphertext res;

    Evaluator evaluator(context);
    evaluator.add(encrypted1, encrypted2, res);

    return res;
}

Ciphertext Container::multiply(Ciphertext encrypted1, Ciphertext encrypted2)
{
    Ciphertext res;

    Evaluator evaluator(context);
    evaluator.multiply(encrypted1, encrypted2, res);

    return res;
}

Plaintext Container::encode_vector(std::vector<uint64_t> vote)
{
    BatchEncoder batch_encoder(context);
    Plaintext vote_plain;
    batch_encoder.encode(vote, vote_plain);
    return vote_plain;
}
std::vector<uint64_t> Container::decode_vector(Plaintext vector_decrypted)
{
    BatchEncoder batch_encoder(context);
    std::vector<uint64_t> tally;
    batch_encoder.decode(vector_decrypted, tally);

    return tally;
}

Ciphertext encrypt_number(Container* container, std::uint64_t value)
{
    std::string value1 = uint64_to_hex_string(value);
    Ciphertext value_encrypted = container->encrypt(value1);
    return value_encrypted;
}


/*
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#
#               Other
#
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
*/

std::string uint64_to_hex_string(std::uint64_t value) 
{
    return util::uint_to_hex_string(&value, std::size_t(1));
}


void Container::print_parameters() 
{
  auto &context_data = *context.key_context_data();

  std::cout << "/" << std::endl;
  std::cout << "| Encryption parameters :" << std::endl;
  std::cout << "|   scheme: BFV" << std::endl;
  std::cout << "|   poly_modulus_degree: "
            << context_data.parms().poly_modulus_degree() << std::endl;

  /*
  Print the size of the true (product) coefficient modulus.
  */
  std::cout << "|   coeff_modulus size: ";
  std::cout << context_data.total_coeff_modulus_bit_count() << " (";
  auto coeff_modulus = context_data.parms().coeff_modulus();
  std::size_t coeff_modulus_size = coeff_modulus.size();
  for (std::size_t i = 0; i < coeff_modulus_size - 1; i++) {
    std::cout << coeff_modulus[i].bit_count() << " + ";
  }
  std::cout << coeff_modulus.back().bit_count();
  std::cout << ") bits" << std::endl;

  /*
  For the BFV scheme print the plain_modulus parameter.
  */
  if (context_data.parms().scheme() == seal::scheme_type::bfv) {
    std::cout << "|   plain_modulus: "
              << context_data.parms().plain_modulus().value() << std::endl;
  }

  std::cout << "\\" << std::endl;
}