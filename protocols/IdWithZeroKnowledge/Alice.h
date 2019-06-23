#ifndef IDWITHZEROKNOWLEDGE_ALICE_H
#define IDWITHZEROKNOWLEDGE_ALICE_H


#include "Generator.h"
#include <time.h>


class Alice : public Generator {
  uint1024_t m_r;
  uint1024_t m_x;
  uint8_t bit;

public:
  explicit Alice(Generator& gen);
  void setBit(uint8_t bit);
  uint1024_t get_x();
  uint1024_t get_r();
  uint1024_t get_bit();
  uint1024_t get_y();
  uint1024_t mul_mod(uint1024_t a, uint1024_t b, uint1024_t n);
};


#endif //IDWITHZEROKNOWLEDGE_ALICE_H
