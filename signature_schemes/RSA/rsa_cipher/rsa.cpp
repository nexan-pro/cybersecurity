#include "rsa.h"

CRSA::CRSA(ulong512_t p, ulong512_t q) {
  ulong512_t max = std::max(p, q);
  ulong512_t min = (max == p) ? q : p;
  if (isPrime(max, min)) {
    this->m_p = p;
    this->m_q = q;
  } else throw std::runtime_error("Error, values of p or q is not prime numbers!");
}

bool CRSA::isPrime(ulong512_t max, ulong512_t min) {
  if (min >= 2) {
    auto primeSequence = getPrimeSequence(max);
    return binarySearch(primeSequence, this->m_cntOfPrimes, max) &&
           binarySearch(primeSequence, this->m_cntOfPrimes, min);
  } else return false;
}

cpp_int_t* CRSA::getPrimeSequence(ulong512_t n){
  this->sieve_mask = sieveOfEratosthenes(n);
  this->src_sieve = new cpp_int_t[n + 1];
  for (size_t c = 2; c <= n; c++)
    this->src_sieve[c] = c;
  for (size_t c = 2; c <= n; c++)
    if (this->sieve_mask[c])
      this->m_cntOfPrimes++;
  auto prime_sieve = new cpp_int_t[this->m_cntOfPrimes];
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

cpp_int_t* CRSA::encrypt(cpp_int_t*& src_text, size_t sizeOfArray) {
  struct key open_key = genKeys().first;
  struct key private_key = genKeys().second;

#ifdef DEBUG
  std::cout << "[DEBUG | encrypt()] d: " << this->m_d << std::endl;
  std::cout << "[DEBUG | encrypt()] open_key: " << "{" << open_key.lhs << ", " << open_key.rhs << "};" << std::endl;
  std::cout << "[DEBUG | encrypt()] private_key: " << "{" << private_key.lhs << ", " << private_key.rhs << "};" << std::endl;
#endif

  //TODO: work with text
#ifdef DEBUG
  std::cout << "[DEBUG | encrypt()] encrypted_text: ";
#endif
  for (size_t c = 0; c < sizeOfArray; c++) {
    src_text[c] = boost::multiprecision::pow(src_text[c], this->m_e) % this->m_n;
#ifdef DEBUG
    std::cout << src_text[c] << ' ';
#endif
  }
#ifdef DEBUG
  std::cout << std::endl;
#endif
  return src_text;
}

/*
 * @brief: In mathematics, the sieve of Eratosthenes is a simple, ancient algorithm for finding all prime
 * numbers up to any given limit.
 * @see: https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 */
bool* CRSA::sieveOfEratosthenes(ulong512_t n) {
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
bool CRSA::binarySearch(cpp_int_t*& lhs, size_t sizeOfArray, cpp_int_t k) {
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

cpp_int_t CRSA::findSecret_d() {
  long double tmp_d = 0;
  for (cpp_int_t k = 1; k < this->m_n * 2; k++) {
#ifdef DEBUG
    std::cout << "[DEBUG | encrypt()] k: " << k << std::endl;
#endif
    tmp_d = static_cast<long double>((k * this->m_eFunc + 1)) / this->m_e;
    if (tmp_d - static_cast<ulong512_t>(tmp_d) > 0)
      continue;
    else {
      this->m_d = static_cast<ulong512_t>(tmp_d);
      break;
    }
  }
  return this->m_d;
}

cpp_int_t* CRSA::decrypt(cpp_int_t*& encrypted_text, size_t sizeOfArray) {
#ifdef DEBUG
  std::cout << "[DEBUG | decrypt()] decrypted: ";
#endif
  for (size_t c = 0; c < sizeOfArray; c++)
    encrypted_text[c] = pow_mod(encrypted_text[c], this->m_d, this->m_n);
#ifdef DEBUG
  std::cout << std::endl;
#endif
  return encrypted_text;
}

cpp_int_t* CRSA::addSalt(cpp_int_t*& encrypted_text, size_t sizeOfArray, int secretNum) {
  cpp_int_t* encryptedWithSalt = new cpp_int_t[sizeOfArray + 1];
  encryptedWithSalt[0] = secretNum;
  for (size_t i = 1; i < sizeOfArray + 1; i++)
    encryptedWithSalt[i] = encrypted_text[i - 1];

  cpp_int_t totalSum = encryptedWithSalt[0];

  for (size_t i = 1; i < sizeOfArray + 1; i++) {
    totalSum = (encryptedWithSalt[i] + totalSum) % this->m_n;
    encryptedWithSalt[i] = totalSum;
  }
  return encryptedWithSalt;
}

cpp_int_t* CRSA::rmSalt(cpp_int_t*& encrypted_text, size_t sizeOfArray) {
  auto* tmp = new cpp_int_t[sizeOfArray];
  tmp[0] = encrypted_text[0];
  for (size_t i = 1; i < sizeOfArray; i++)
    tmp[i] = (((encrypted_text[i] - encrypted_text[i - 1]) % this->m_n) + this->m_n) % this->m_n;
  return tmp;
}

cpp_int_t CRSA::pow_mod(cpp_int_t arg, cpp_int_t power, cpp_int_t module) {
  if (power == 1)
    return arg % module;
  cpp_int_t res;
  res = pow_mod(arg, power / 2, module);
  res = (res * res) % module;
  if (power % 2 == 1) res = (res * arg) % module;
  return res;
}

std::vector<ulong512_t> CRSA::factorize(ulong512_t x) {
  std::vector<ulong512_t> factors;
  for (ulong512_t i = 2; i <= sqrt(x); i++) {
    while (x % i == 0) {
      factors.push_back(i);
      x /= i;
    }
  }
  if (x != 1)
    factors.push_back(x);

  return factors;
}

std::pair<key, key> CRSA::genKeys() {
  this->m_n = this->m_p * this->m_q;
  this->m_eFunc = (m_p - 1) * (m_q - 1);
  bool flag = false;
  int ecx = 0;
  for (ulong512_t c = 1; c < this->m_n; c+=2) {
    if (flag) break;
    if (this->m_eFunc % c != 0) { //TODO: enhancement
      auto fact_e = factorize(c);
      for (ulong512_t &it : fact_e)
        if (this->m_eFunc % it == 0)
          break;
        else ecx++;
      if (ecx == fact_e.size()) {
        this->m_e = c;
        flag = true;
        break;
      }
    }
  }

#ifdef DEBUG
  std::cout << "[DEBUG | encrypt()] e: " << this->m_e << std::endl;
#endif

  findSecret_d();

  struct key open_key = { m_e, m_n };
  struct key private_key = { m_d, m_n };
  return std::make_pair(open_key, private_key);
}
