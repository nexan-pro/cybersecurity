#include "rsa.h"

RSA::RSA(ulong8_t p, ulong8_t q) {
  ulong8_t max = std::max(p, q);
  ulong8_t min = (max == p) ? q : p;
  if (isPrime(max, min)) {
    this->m_p = p;
    this->m_q = q;
  } else throw std::runtime_error("Error, values of p or q is not prime numbers!");
}

bool RSA::isPrime(ulong8_t max, ulong8_t min) {
  if (min >= 2) {
    auto primeSequence = getPrimeSequence(max);
    return binarySearch(primeSequence, this->m_cntOfPrimes, max) &&
           binarySearch(primeSequence, this->m_cntOfPrimes, min);
  } else return false;
}

ulong8_t* RSA::getPrimeSequence(ulong8_t n){
  this->sieve_mask = sieveOfEratosthenes(n);
  this->src_sieve = new ulong8_t[n + 1];
  for (size_t c = 2; c <= n; c++)
    this->src_sieve[c] = c;
  for (size_t c = 2; c <= n; c++)
    if (this->sieve_mask[c])
      this->m_cntOfPrimes++;
  auto prime_sieve = new ulong8_t[this->m_cntOfPrimes];
  int ecx = 0;
  for (size_t c = 2; c <= n; c++)
    if (sieve_mask[c]) {
      prime_sieve[ecx] = src_sieve[c];
      ecx++;
    }
#ifdef DEBUG
  for (size_t c = 0; c < ecx; c++)
    std::cout << prime_sieve[c] << ' ';
  std::cout << std::endl;
#endif
  return prime_sieve;
}

std::string RSA::encrypt(ulong8_t*& src_text, size_t sizeOfArray) {
  this->m_n = this->m_p * this->m_q;
  this->m_eFunc = (m_p - 1) * (m_q - 1);
  for (size_t c = 1; c < this->m_eFunc; c+=2)
    if (this->m_eFunc % c != 0) {
      this->m_e = c;
      break;
    }

#ifdef DEBUG
  std::cout << "[DEBUG | encrypt()] e: " << this->m_e << std::endl;
#endif

  findSecret_d();

  struct key open_key = { m_e, m_n };
  struct key private_key = { m_d, m_n };

#ifdef DEBUG
  std::cout << "[DEBUG | encrypt()] d: " << this->m_d << std::endl;
  std::cout << "[DEBUG | encrypt()] open_key: " << "{" << open_key.lhs << ", " << open_key.rhs << "};" << std::endl;
  std::cout << "[DEBUG | encrypt()] private_key: " << "{" << private_key.lhs << ", " << private_key.rhs << "};" << std::endl;
#endif

  //TODO: work with text
  std::string tmp;
  for (size_t c = 0; c < sizeOfArray; c++) {
    src_text[c] = static_cast<ulong8_t>(pow(src_text[c], this->m_e)) % this->m_n;
    tmp += std::to_string(src_text[c]) + " ";
  }
  /**********************************************************************************/
  return tmp;
}

/*
 * @brief: In mathematics, the sieve of Eratosthenes is a simple, ancient algorithm for finding all prime
 * numbers up to any given limit.
 * @see: https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 */
bool* RSA::sieveOfEratosthenes(ulong8_t n) {
  bool* sequence = new bool[n + 1];
  for (size_t i = 0; i <= n; i++)
    sequence[i] = true;
  for (size_t i = 2; i * i <= n; i++)
    if (sequence[i])
      for (size_t j = i * i; j <= n; j+=i)
        sequence[j] = false;
  return sequence;
}

/*
 * @brief: Binary search is a search algorithm that finds the position of a target value within a sorted array.
 * @see: https://en.wikipedia.org/wiki/Binary_search_algorithm
 */
bool RSA::binarySearch(ulong8_t*& lhs, size_t sizeOfArray, ulong8_t k) {
  uint32_t start = 0;
  uint32_t end = sizeOfArray;
  int mid = 0;
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

ulong8_t RSA::findSecret_d() {
  long double tmp_d = 0;
  for (ulong8_t k = 1; k < this->m_n * 2; k++) {
#ifdef DEBUG
    std::cout << "[DEBUG | encrypt()] k: " << k << std::endl;
#endif
    tmp_d = static_cast<long double>((k * this->m_eFunc + 1)) / this->m_e;
    if (tmp_d - static_cast<unsigned long int>(tmp_d) > 0)
      continue;
    else {
      this->m_d = static_cast<ulong8_t>(tmp_d);
      break;
    }
  }
  return this->m_d;
}


