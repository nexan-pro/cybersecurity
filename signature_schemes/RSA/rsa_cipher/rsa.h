/*
 * RSA Algorithm
 * @see: https://en.wikipedia.org/wiki/RSA(cryptosystem)
 */

#ifndef RSA_RSA_H
#define RSA_RSA_H

#define DEBUG

#include <string>
#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int cpp_int_t;
typedef unsigned long long int ulong512_t;


struct key {
  cpp_int_t lhs;
  cpp_int_t rhs;
};


class CRSA {
private:
  cpp_int_t m_p; // !< first input num
  cpp_int_t m_q; // !< second input num
  cpp_int_t m_n; // !< product of input prime nums
  cpp_int_t m_eFunc; // !< Euler func
  ulong512_t m_e; // !< open e
  ulong512_t m_d; // !< secret e
  cpp_int_t* src_sieve; // !< source sieve
  bool* sieve_mask; // !< mask with prime nums
  size_t m_cntOfPrimes = 0; // !< count of prime nums in mask
  cpp_int_t* getPrimeSequence(ulong512_t n);
  bool isPrime(ulong512_t max, ulong512_t min);
  bool* sieveOfEratosthenes(ulong512_t n);
  cpp_int_t findSecret_d();
  bool binarySearch(cpp_int_t*& lhs, size_t sizeOfArray, cpp_int_t k);
  std::vector<ulong512_t> factorize(ulong512_t x);
public:
  explicit CRSA(ulong512_t p, ulong512_t q);
  std::pair<key, key> genKeys();
  cpp_int_t* encrypt(cpp_int_t*& src_text, size_t sizeOfArray);
  cpp_int_t* decrypt(cpp_int_t*& encrypted_text, size_t sizeOfArray);
  cpp_int_t* addSalt(cpp_int_t*& encrypted_text, size_t sizeOfArray, int secretNum);
  cpp_int_t* rmSalt(cpp_int_t*& encrypted_text, size_t sizeOfArray);
  cpp_int_t pow_mod(cpp_int_t arg, cpp_int_t power, cpp_int_t module);
  ~CRSA() {
    delete[] src_sieve;
    delete[] sieve_mask;
  };
};


#endif //RSA_RSA_H
