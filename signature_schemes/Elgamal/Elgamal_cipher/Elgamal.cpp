#include "Elgamal.h"


/**
 * @brief: Generate a rand number in the range [2; 999.999] and check it for primality
 * @return: Prime rand number
 */
ulong512_t CElgamal::genRandPrime() {
  ulong512_t nRand = rand() % 999999 + 2;
  while (!isPrime(nRand))
    nRand = rand() % 999999 + 2;

  return nRand;
}

/**
 * @brief: Check number for prime
 * @param nP - possible prime num
 * @return: @if num is prime @return true @else false
 */
bool CElgamal::isPrime(ulong512_t nP) {
  auto primeSequence = getPrimeSequence(nP);
  return binarySearch(primeSequence, this->m_nSizeOfPrimeSequence, nP);
}

/**
 * @brief: In mathematics, the sieve of Eratosthenes is a simple, ancient algorithm for finding all prime
 * numbers up to any given limit.
 * @see: https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 * @param n - possible prime num
 * @return: mask of prime nums
 */
bool* CElgamal::sieveOfEratosthenes(ulong512_t n) {
  bool* mask = new bool[n + 1];

  for (size_t c = 0; c <= n; c++)
    mask[c] = true;

  for (size_t i = 2; i * i <= n; i++)
    if (mask[i])
      for (size_t j = i * i; j <= n; j+=i)
        mask[j] = false;

  return mask;
}

/**
 * @brief: Generate prime sequence in range [2;n]
 * @param n - possible prime num
 * @return: primeSequence - The sequence of Prime nums
 */
cpp_int_t* CElgamal::getPrimeSequence(ulong512_t n) {
  auto mask = sieveOfEratosthenes(n);
  auto primeSequence = new cpp_int_t[n + 1];

  int ecx = 0;
  for (size_t i = 2; i <= n; i++)
    if (mask[i]) {
      primeSequence[ecx] = i;
      ecx++;
    }

  this->m_nSizeOfPrimeSequence = ecx;

  delete mask;

#ifdef DEBUG
  std::cout << "[DEBUG]: Source prime sequence: ";
  for (size_t c = 0; c < this->m_nSizeOfPrimeSequence; c++)
    std::cout << primeSequence[c] << ' ';
  std::cout << std::endl;
#endif

  return primeSequence;
}

/**
 * @brief: Binary search is a search algorithm that finds the position of a target value within a sorted array.
 * @see: https://en.wikipedia.org/wiki/Binary_search_algorithm
 * @param lhs - pointer to array
 * @param sizeOfArray - size of array
 * @param k - key which need to find in array
 * @return: @if key exist @return true @else @return false
 */
bool CElgamal::binarySearch(cpp_int_t*& lhs, size_t sizeOfArray, cpp_int_t k) {
  uint32_t start = 0;
  uint32_t end = sizeOfArray;
  uint32_t mid = 0;

  while (start <= end) {
    mid = start + (end - start) / 2;

    if (lhs[mid] == k)
      return true;
    else if (lhs[mid] > k)
      end = mid - 1;
    else
      start = mid + 1;
  }
  return false;
}

/**
 * @brief: Function of exponentiation modulo
 * @param arg - num to be raised to the power
 * @param power - power
 * @param module - module
 * @return: result of exponentiation modulo
 */
cpp_int_t CElgamal::pow_mod(cpp_int_t arg, cpp_int_t power, cpp_int_t module) {
  if (power == 1)
    return arg % module;
  cpp_int_t res;
  res = pow_mod(arg, power / 2, module);
  res = (res * res) % module;
  if (power % 2 == 1) res = (res * arg) % module;
  return res;
}

/**
 * @brief: Generate primitive root
 * @return: Generated primitive root
 */
cpp_int_t CElgamal::genPrimitiveRoot() {
  cpp_int_t d = (this->m_p - 1) / 2;
  cpp_int_t nRand = rand() % this->m_p - 1 + 2;


  while (pow_mod(nRand, d, this->m_p) != this->m_p - 1)
    nRand = rand() % this->m_p - 1 + 2;

  return nRand;
}

/**
 * @brief: mul by modulo
 * @param a - num of exponentiation modulo
 * @param b - private key
 * @param n - generated p
 * @return: sum
 */
cpp_int_t CElgamal::mul(cpp_int_t a, cpp_int_t b, cpp_int_t n) {
  cpp_int_t sum = 0;
  for (cpp_int_t i = 0; i < b; i++) {
    sum += a;
    if (sum >= n)
      sum -= n;
  }
  return sum;
}

/**
 * @brief: encrypt message
 * @see: https://en.wikipedia.org/wiki/ElGamal_encryption
 * @return: ciphertext
 */
std::pair<cpp_int_t, cpp_int_t> CElgamal::encrypt() {
  this->m_p = genRandPrime();
  this->m_g = genPrimitiveRoot();
  this->m_x = rand() % this->m_p + 1;
  this->m_y = pow_mod(this->m_g, this->m_x, this->m_p);

#ifdef DEBUG
  std::cout << "private key: { " << this->m_p << ", " << this->m_g << ", "
            << this->m_y << " }";
#endif

  this->m_k = rand() % this->m_p + 1;
  this->m_a = pow_mod(this->m_g, this->m_k, this->m_p);
  this->m_b = mul(pow_mod(this->m_y, this->m_k, this->m_p), this->m_msg, this->m_p);

#ifdef DEBUG
  std::cout << " encrypted: { " << this->m_a << ", " << this->m_b << " }" << std::endl;
#endif

  return std::make_pair(this->m_a, this->m_b);
}

/**
 * @brief: encrypt message
 * @param msg - message which will be encrypted
 * @see: https://en.wikipedia.org/wiki/ElGamal_encryption
 * @return: ciphertext
 */
std::pair<cpp_int_t, cpp_int_t> CElgamal::encrypt(cpp_int_t msg) {
  this->m_msg = msg;

  return encrypt();
}

/**
 * @brief: decrypt message
 * @see: https://en.wikipedia.org/wiki/ElGamal_encryption
 * @details: M = b * a^(p-1-x) mod p
 * @param a - first num of ciphertext
 * @param b - second num of ciphertext
 * @param x - private key
 * @return: decrypted message
 */
cpp_int_t CElgamal::decrypt(cpp_int_t a, cpp_int_t b, cpp_int_t x) {
  cpp_int_t power = this->m_p - 1 - x;
  cpp_int_t tmp = mul(pow_mod(a, power, this->m_p), b, this->m_p);

#ifdef DEBUG
  std::cout << "decrypted msg is: " << tmp << std::endl;
#endif

  return tmp;
}
