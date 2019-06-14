#include "rsa_sign.h"

unsigned int CRSA_sign::MaHash7(unsigned char *str, unsigned int len) {
  unsigned int hash = len, i;

  for (i = 0; i != len * ITERATIONS; i++)
  {
    str += (i % len);
    hash = LROT13 (hash + ((hash << 8) ^ (hash >> 12))) - sTable[(*str + i) & 255];
  }
  return hash;
}

void CRSA_sign::sign_msg(u_char* msg) {
  m_pSign_scheme->msg = msg;
  this->m_h = MaHash7(msg, std::strlen(reinterpret_cast<char*>(msg)));
  this->sys_keys = genKeys();
  m_pSign_scheme->sign = pow_mod(this->m_h, sys_keys.second.lhs, sys_keys.second.rhs);

#ifdef DEBUG
  std::cout << "generated sign scheme is: { " << m_pSign_scheme->msg << ", "
  << m_pSign_scheme->sign << " };" << std::endl;
#endif
}

void CRSA_sign::check_sign(u_char* msg) {
  ulong512_t tmp_hash = static_cast<ulong512_t>(pow_mod(m_pSign_scheme->sign, sys_keys.first.lhs, sys_keys.first.rhs));
  ulong512_t verification_hash = MaHash7(msg, std::strlen(reinterpret_cast<char*>(msg)));

  if (tmp_hash == verification_hash) std::cout << "good" << std::endl;
  else std::cout << "wrong" << std::endl;
}


