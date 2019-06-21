#ifndef ELGAMAL_ELGAMAL_H
#define ELGAMAL_ELGAMAL_H


#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include "time.h"


#define DEBUG
#define MOD(a, b) (a % b + b) % b


typedef boost::multiprecision::cpp_int cpp_int_t;
typedef unsigned long long int ulong512_t;


/**
 * @see: https://en.wikipedia.org/wiki/ElGamal_encryption
 */
class CElgamal {
public:
  explicit CElgamal() {
    srand(time(0));
  }

  CElgamal(cpp_int_t msg) {
    srand(time(0));
    this->m_msg = msg;
  }

  std::pair<cpp_int_t, cpp_int_t> encrypt();
  std::pair<cpp_int_t, cpp_int_t> encrypt(cpp_int_t msg);
  cpp_int_t decrypt(cpp_int_t a, cpp_int_t b, cpp_int_t x);

protected: //TODO: Key generator!!!!!!!!!!!!!!!!!!!!!!!!!! 0xD34DB33F
  cpp_int_t m_msg;
  cpp_int_t m_p; // rand prime num
  cpp_int_t m_g; // primitive root
  cpp_int_t m_x; // rand num 1 < x < p
  cpp_int_t m_y;
  cpp_int_t m_k; // rand num 1 < k < (p - 1)
  cpp_int_t m_a; // first num of ciphertext
  cpp_int_t m_b; // second num of ciphertext
  size_t m_nSizeOfPrimeSequence = 0;

  cpp_int_t genPrimitiveRoot();
  ulong512_t genRandPrime();
  bool isPrime(ulong512_t nP);
  bool* sieveOfEratosthenes(ulong512_t n);
  bool binarySearch(cpp_int_t*& lhs, size_t sizeOfArray, cpp_int_t k);
  cpp_int_t pow_mod(cpp_int_t arg, cpp_int_t power, cpp_int_t module);
  cpp_int_t mul(cpp_int_t a, cpp_int_t b, cpp_int_t n);
  cpp_int_t* getPrimeSequence(ulong512_t n);
};


#endif //ELGAMAL_ELGAMAL_H
