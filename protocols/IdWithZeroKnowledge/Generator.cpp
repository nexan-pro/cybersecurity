#include "Generator.h"

uint1024_t Generator::quadratic_deduction() {
  return uint1024_t();
}

uint1024_t Generator::gen_N(uint1024_t lhs, uint1024_t rhs) {
  this->m_n = lhs * rhs;
  return this->m_n;
}

uint1024_t Generator::gen_V() {
  uint1024_t res;
  for(uint1024_t v("99999"); v < this->m_n; v++) {
    for (uint1024_t x = 1; x < 10000; ++x) {
      uint1024_t tmp = ((x * x - v) % this->m_n);
      if (tmp == 0 && reverseElement(v, this->m_n, res) == 0) {
        this->m_v = v;
        this->m_s = sqrt(res);
#ifdef DEBUG
std::cout << "secret key: " << this->m_s << std::endl;
#endif
        return v;
      }
    }
  }

  std::cout << "rex = " << res << std::endl;
  return uint1024_t();
}

uint1024_t Generator::gcdex(uint1024_t a, uint1024_t b, uint1024_t &x, uint1024_t &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  uint1024_t x1, y1;
  uint1024_t d1 = gcdex(b, a % b, x1, y1);
  x = y1;
  y = x1 - (a / b) * y1;
  return d1;
}

// Function returns 1 if such element doesn't exist and 0 if exists and puts it
// in result.
uint1024_t Generator::reverseElement(uint1024_t a, uint1024_t N, uint1024_t &result) {
  uint1024_t x, y, d;
  d = gcdex(a, N, x, y);
  if (d != 1) {
    return -1;
  } else {
    result = x;
    return 0;
  }
}

uint1024_t Generator::pow_mod(uint1024_t arg, uint1024_t power, uint1024_t module) {
  if (power == 1)
    return arg % module;
  uint1024_t res;
  res = pow_mod(arg, power / 2, module);
  res = (res * res) % module;
  if (power % 2 == 1) res = (res * arg) % module;
  return res;
}

uint1024_t Generator::get_v() {
  return this->m_v;
}
