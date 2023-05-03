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
  infos_obj.build_static_info("src/config.json");
  
  Container container(infos_obj);

  container.print_parameters();

  container.init_public_key();
  container.init_secret_key();

  create_folder_if_not_exists("data");
  container.save_secret();
  container.load_secret();

  uint64_t x = 6;
  Ciphertext x_encrypted = container.encrypt(uint64_to_hex_string(x));

  uint64_t y = 40;
  Ciphertext y_encrypted = container.encrypt(uint64_to_hex_string(y));

  Ciphertext sum = container.sum(x_encrypted, y_encrypted);
  std::string decrypt = container.decrypt(sum);

  std::cout << "decrypted string: " << decrypt << "\n";
}