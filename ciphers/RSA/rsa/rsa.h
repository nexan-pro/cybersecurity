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
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int cpp_int_t;
typedef ulong ulong8_t;

class RSA {
private:
  cpp_int_t m_p; // !< first input num
  cpp_int_t m_q; // !< second input num
  cpp_int_t m_n; // !< product of input prime nums
  cpp_int_t m_eFunc; // !< Euler func
  ulong8_t m_e; // !< open e
  ulong8_t m_d; // !< secret e
  cpp_int_t* src_sieve; // !< source sieve
  bool* sieve_mask; // !< mask with prime nums
  size_t m_cntOfPrimes = 0; // !< count of prime nums in mask
  cpp_int_t pow_mod(cpp_int_t arg, cpp_int_t power, cpp_int_t module);
  cpp_int_t* getPrimeSequence(ulong8_t n);
  bool isPrime(ulong8_t max, ulong8_t min);
  bool* sieveOfEratosthenes(ulong8_t n);
  cpp_int_t findSecret_d();
  bool binarySearch(cpp_int_t*& lhs, size_t sizeOfArray, cpp_int_t k);
public:
  explicit RSA(ulong8_t p, ulong8_t q);
  cpp_int_t* encrypt(cpp_int_t*& src_text, size_t sizeOfArray);
  cpp_int_t* decrypt(cpp_int_t*& encrypted_text, size_t sizeOfArray);
  cpp_int_t* addSalt(cpp_int_t*& encrypted_text, size_t sizeOfArray, int secretNum);
  cpp_int_t* rmSalt(cpp_int_t*& encrypted_text, size_t sizeOfArray);
  ~RSA() {
    delete[] src_sieve;
    delete[] sieve_mask;
  };
};

struct key {
  cpp_int_t lhs;
  cpp_int_t rhs;
};


#endif //RSA_RSA_H
