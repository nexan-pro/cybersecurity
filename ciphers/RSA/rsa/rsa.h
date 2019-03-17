/*
 * RSA Algorithm
 * @see: https://en.wikipedia.org/wiki/RSA_(cryptosystem)
 */

#ifndef RSA_RSA_H
#define RSA_RSA_H

#define DEBUG

#include <string>
#include <time.h>
#include <math.h>
#include <iostream>

typedef ulong ulong8_t;

class RSA {
private:
  ulong8_t m_p; // !< first input num
  ulong8_t m_q; // !< second input num
  ulong8_t m_n; // !< product of input prime nums
  ulong8_t m_eFunc; // !< Euler func
  ulong8_t m_e; // !< open e
  ulong8_t m_d; // !< secret e
  ulong8_t* src_sieve; // !< source sieve
  bool* sieve_mask; // !< mask with prime nums
  size_t m_cntOfPrimes = 0; // !< count of prime nums in mask
  ulong8_t* getPrimeSequence(ulong8_t n);
  bool isPrime(ulong8_t max, ulong8_t min);
  bool* sieveOfEratosthenes(ulong8_t n);
  ulong8_t findSecret_d();
public:
  explicit RSA(ulong8_t p, ulong8_t q);
  std::string encrypt(ulong8_t*& src_text, size_t sizeOfArray);
  bool binarySearch(ulong8_t*& lhs, size_t sizeOfArray, ulong8_t k);
  ~RSA() {
    delete[] src_sieve;
    delete[] sieve_mask;
  };
};

struct key {
  ulong8_t lhs;
  ulong8_t rhs;
};


#endif //RSA_RSA_H
