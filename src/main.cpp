#include "seal/seal.h"
#include "../utils/utils.hh"
#include "../BFV/bfv.hh"
#include <iostream>

using namespace seal;

std::string uint64_to_hex_string(std::uint64_t value) {
  return util::uint_to_hex_string(&value, std::size_t(1));
}

int main() {
  Infos infos_obj;

  // Load infos from JSON
  infos_obj.build_static_info("src/config.json");
  
  Container container(infos_obj);

  // Pretty Print
  container.print_parameters();

  // Init BGV keys
  container.init_public_key();
  container.init_secret_key();

  // Test of the save / import feature
  container.save_secret();
  container.load_secret();


  // Init two values and encrypt them
  uint64_t x = 6;
  std::string x1 = uint64_to_hex_string(x);
  Ciphertext x_encrypted = container.encrypt(x1);

  uint64_t y = 40;
  std::string y1 = uint64_to_hex_string(y);
  Ciphertext y_encrypted = container.encrypt(y1);


  // Compute the sum / multiplication
  Ciphertext sum = container.sum(x_encrypted, y_encrypted);
  std::string sum_decrypted = container.decrypt(sum);

  Ciphertext mult = container.multiply(x_encrypted, y_encrypted);
  std::string mult_decrypted = container.decrypt(mult);

  uint64_t s = x + y;
  uint64_t m = x * y;


  // Print to see if everything's right
  std::cout << "x:" << x1 << ", y:" << y1 << "\n";
  std::cout << "addition: " << uint64_to_hex_string(s) << ", decrypted addition: " << sum_decrypted << "\n";
  std::cout << "multiplication: " << uint64_to_hex_string(m) << ", decrypted multiplication: " << mult_decrypted << "\n";
}