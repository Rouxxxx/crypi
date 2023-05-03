#include "seal/seal.h"
#include "../utils/utils.hh"
#include <iostream>

using namespace seal;

std::string uint64_to_hex_string(std::uint64_t value) {
  return util::uint_to_hex_string(&value, std::size_t(1));
}

void print_parameters(const SEALContext &context) {
  auto &context_data = *context.key_context_data();

  /*
  Which scheme are we using?
  */
  std::string scheme_name;
  switch (context_data.parms().scheme()) {
  case seal::scheme_type::bfv:
    scheme_name = "BFV";
    break;
  case seal::scheme_type::ckks:
    scheme_name = "CKKS";
    break;
  case seal::scheme_type::bgv:
    scheme_name = "BGV";
    break;
  default:
    throw std::invalid_argument("unsupported scheme");
  }
  std::cout << "/" << std::endl;
  std::cout << "| Encryption parameters :" << std::endl;
  std::cout << "|   scheme: " << scheme_name << std::endl;
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

int main() {
  Infos infos_obj;
  infos_obj.build_static_info("src/config.json");
  
  size_t poly_modulus_degree = infos_obj.poly_modulus_degree;
  std::uint64_t plain_modulus = infos_obj.plain_modulus;
  
  EncryptionParameters parms(scheme_type::bfv);
  parms.set_poly_modulus_degree(poly_modulus_degree);
  parms.set_coeff_modulus(CoeffModulus::BFVDefault(poly_modulus_degree));
  parms.set_plain_modulus(plain_modulus);

  /*
  Now that all parameters are set, we are ready to construct a SEALContext
  object. This is a heavy class that checks the validity and properties of the
  parameters we just set.
  */
  SEALContext context(parms);

  /*
  Print the parameters that we have chosen.
  */
  std::cout << "==================================\n";
  std::cout << "Set encryption parameters and print" << std::endl;
  print_parameters(context);

  KeyGenerator keygen(context);
  SecretKey secret_key = keygen.secret_key();
  PublicKey public_key;
  keygen.create_public_key(public_key);

  create_folder_if_not_exists("data");
  save_secret_key(secret_key, "data/secret_key.txt");
  load_secret_key(context, secret_key, "data/secret_key.txt");

  Encryptor encryptor(context, public_key);

  Evaluator evaluator(context);

  Decryptor decryptor(context, secret_key);

  std::cout << "==================================\n";
  uint64_t x = 6;
  Plaintext x_plain(uint64_to_hex_string(x));
  std::cout << "Express x = " + std::to_string(x) +
                   " as a plaintext polynomial 0x" + x_plain.to_string() + "."
            << std::endl;

  /*
  We then encrypt the plaintext, producing a ciphertext..
  */
  std::cout << "==================================\n";
  Ciphertext x_encrypted;
  std::cout << "Encrypt x_plain to x_encrypted." << std::endl;
  encryptor.encrypt(x_plain, x_encrypted);

  /*
  In Microsoft SEAL, a valid ciphertext consists of two or more polynomials
  whose coefficients are integers modulo the product of the primes in the
  coeff_modulus. The number of polynomials in a ciphertext is called its `size'
  and is given by Ciphertext::size(). A freshly encrypted ciphertext always
  has size 2.
  */
  std::cout << "    + size of freshly encrypted x: " << x_encrypted.size()
            << std::endl;

  /*
  There is plenty of noise budget left in this freshly encrypted ciphertext.
  */
  std::cout << "    + noise budget in freshly encrypted x: "
            << decryptor.invariant_noise_budget(x_encrypted) << " bits"
            << std::endl;

  /*
  We decrypt the ciphertext and print the resulting plaintext in order to
  demonstrate correctness of the encryption.
  */
  Plaintext x_decrypted;
  std::cout << "    + decryption of x_encrypted: ";
  decryptor.decrypt(x_encrypted, x_decrypted);
  std::cout << "0x" << x_decrypted.to_string() << " ...... Correct."
            << std::endl;

  std::cout << "encrypted value: " << std::to_string(x)
            << "\ndecrypted value: " << x_decrypted.to_string() << "\n";
}