#include "Alice.h"

Alice::Alice(Generator& gen) {
  boost::random::mt19937 mt;
  boost::random::uniform_int_distribution<cpp_int_t> ui(-(cpp_int_t(1) << 128), cpp_int_t(1) << 128);

  uint8_t rand_num = rand() % 10 + 1;
  for (size_t i = rand_num; i < 300; i++) {
    cpp_int_t tmp = ui(mt);
    if (tmp > 0) {
      this->m_r = uint1024_t(tmp) / rand_num;
      break;
    }
  }
  this->m_n = gen.m_n;
  this->m_x = pow_mod(this->m_r, 2, this->m_n);

  std::cout << "x = " << this->m_x << std::endl;
}

void Alice::setBit(uint8_t bit) {
  this->bit = bit;
}

uint1024_t Alice::get_x() {
  return uint1024_t(this->m_x);
}

uint1024_t Alice::get_r() {
  return uint1024_t(this->m_r);
}

uint1024_t Alice::get_bit() {
  return uint1024_t(bit);
}

uint1024_t Alice::mul_mod(uint1024_t a, uint1024_t b, uint1024_t n) {
  uint1024_t sum = 0;
  for (uint1024_t i = 0; i < b; i++) {
    sum += a;
    if (sum >= n)
      sum -= n;
  }
  return sum;
}

uint1024_t Alice::get_y() {
  return mul_mod(this->m_r, this->m_s, this->m_n);
}
