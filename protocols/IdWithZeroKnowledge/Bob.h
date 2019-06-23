#ifndef IDWITHZEROKNOWLEDGE_BOB_H
#define IDWITHZEROKNOWLEDGE_BOB_H


#include "Alice.h"


class Bob : public Generator {
  uint1024_t m_x;
  uint1024_t m_r;
  uint1024_t m_y;


public:
  void set_x(uint1024_t x);
  void sendRandBit(Alice& side_a);
  void set_r(uint1024_t r);
  void set_y(uint1024_t y);
  uint1024_t get_x();
};


#endif //IDWITHZEROKNOWLEDGE_BOB_H
