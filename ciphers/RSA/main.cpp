#include <iostream>
#include "rsa/rsa.h"

int main() {
  RSA f(3557, 2579);
  auto msg = new ulong8_t[6];
  msg[0] = 7;
  msg[1] = 17;
  msg[2] = 25;
  msg[3] = 67;
  msg[4] = 11;
  msg[5] = 5;
  std::cout << f.encrypt(msg, 6) << std::endl;
  return 0;
}