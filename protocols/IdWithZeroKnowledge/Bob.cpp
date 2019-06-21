#include "Bob.h"

void Bob::set_x(uint1024_t x) {
  this->m_x = x;
#ifdef DEBUG
std::cout << "Bob: x was successfully setted: " << this->m_x << std::endl;
#endif
}

void Bob::sendRandBit(Alice& side_a) {
  uint8_t rand_bit = rand() % 2;
  side_a.setBit(rand_bit);
}

void Bob::set_r(uint1024_t r) {
  this->m_r = r;
}

void Bob::set_y(uint1024_t y) {
  this->m_y = y;
}

void Bob::checkForSignalBit() {

}
