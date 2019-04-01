#include <iostream>
#include <chrono>
#include "../rsa/rsa.h"

#define SIZE 6

int main() {
  auto start = std::chrono::steady_clock::now();
  RSA rsa(99251, 99257);
  auto msg = new cpp_int_t[SIZE];
  msg[0] = 7;
  msg[1] = 17;
  msg[2] = 25;
  msg[3] = 9;
  msg[4] = 11;
  msg[5] = 5;
  cpp_int_t* encryptedValue = rsa.encrypt(msg, SIZE);
  std::cout << "encrypted value without salt: ";
  for (size_t i = 0; i < SIZE; i++)
    std::cout << encryptedValue[i] << ' ';
  std::cout << std::endl;

  cpp_int_t* decryptedValue = rsa.decrypt(encryptedValue, SIZE);
  std::cout << "decrypted msg: ";
  for (size_t i = 0; i < SIZE; i++)
    std::cout << decryptedValue[i] << ' ';
  std::cout << std::endl;

  encryptedValue = rsa.addSalt(encryptedValue, SIZE, 13);
  std::cout << "encrypted value with salt: ";
  for (size_t i = 0; i < SIZE + 1; i++)
    std::cout << encryptedValue[i] << ' ';
  std::cout << std::endl;

  decryptedValue = rsa.rmSalt(encryptedValue, SIZE + 1);
  std::cout << "decrypted value from salt (native rsa): ";
  for (size_t i = 0; i < SIZE + 1; i++)
    std::cout << decryptedValue[i] << ' ';
  std::cout << std::endl;

  auto end = std::chrono::steady_clock::now();
  std::cout << "Elapsed time(ms): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
            << std::endl;

  return 0;
}