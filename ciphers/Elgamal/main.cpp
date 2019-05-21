#include <iostream>
#include "Elgamal.h"

int main() {
  CElgamal hEl(5);
  std::pair<cpp_int_t, cpp_int_t> encrypted = hEl.encrypt();
  std::cout << "ciphertext: { " << encrypted.first << ", " << encrypted.second << " }" << std::endl;
  return 0;
}