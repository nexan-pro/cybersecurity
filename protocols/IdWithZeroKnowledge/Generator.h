#ifndef IDWITHZEROKNOWLEDGE_GENERATOR_H
#define IDWITHZEROKNOWLEDGE_GENERATOR_H


#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <iostream>


#define DEBUG


typedef boost::multiprecision::uint1024_t uint1024_t;
typedef boost::multiprecision::cpp_int cpp_int_t;


class Generator {
  uint1024_t m_v;
  uint1024_t quadratic_deduction();
  uint1024_t gcdex(uint1024_t a, uint1024_t b, uint1024_t &x, uint1024_t &y);
  uint1024_t reverseElement(uint1024_t a, uint1024_t N, uint1024_t &result);

protected:
  uint1024_t m_s; // secret

public:
  uint1024_t m_n;
  uint1024_t pow_mod(uint1024_t arg, uint1024_t power, uint1024_t module);
  uint1024_t gen_V();
  uint1024_t gen_N(uint1024_t lhs, uint1024_t rhs);
};


#endif //IDWITHZEROKNOWLEDGE_GENERATOR_H
