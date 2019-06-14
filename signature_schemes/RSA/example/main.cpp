#include <iostream>
#include <chrono>
#include "../rsa_cipher/rsa_sign.h"


int main() {
  /* CLIENT */ //TODO:
  auto start = std::chrono::steady_clock::now();
  CRSA_sign rsa(20999899, 20999767);
  u_char msg[4] = "qwe";
  u_char another_msg[4] = "asd";
  rsa.sign_msg(msg);
  rsa.check_sign(msg);
  auto end = std::chrono::steady_clock::now();
  std::cout << "Elapsed time(ms): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
            << std::endl;
  return 0;
}
