#include "bfv.hh"

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
    parms.set_plain_modulus(infos.plain_modulus);

    return SEALContext(parms);
}


Container::Container(Infos infos)
    : context(set_context(infos)), keygen(KeyGenerator(context))
{
    infos_struct = infos;
}

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
    save_secret(infos_struct.data_folder + "/" + infos_struct.secret_key_file);
}
void Container::save_secret(std::string path)
{
    save_secret_key(secret_key, path);
}

void Container::load_secret()
{
    load_secret(infos_struct.data_folder + "/" + infos_struct.secret_key_file);
}
void Container::load_secret(std::string path)
{
    load_secret_key(context, secret_key, path);
}


Ciphertext Container::encrypt(std::string str)
{
    Encryptor encryptor(context, public_key);
    Plaintext x_plain(str);

    Ciphertext x_encrypted;
    encryptor.encrypt(x_plain, x_encrypted);

    return x_encrypted;
}

std::string Container::decrypt(Ciphertext x_encrypted)
{
    Plaintext x_decrypted;

    Decryptor decryptor(context, secret_key);
    decryptor.decrypt(x_encrypted, x_decrypted);

    return x_decrypted.to_string();
}




/*
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#
#               Other
#
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
*/

void Container::print_parameters() {
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