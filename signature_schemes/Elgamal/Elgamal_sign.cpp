#include "Elgamal_sign.h"

void CElgamal_sign::sign_msg(u_char* msg) {
  this->m_p = 23;
//  this->m_p = genRandPrime();
  this->m_g = 5;
//  this->m_g = genPrimitiveRoot();
  this->m_x = 7;
//  this->m_x = rand() % this->m_p + 1;
  this->m_y = 17;
//  this->m_y = pow_mod(this->m_g, this->m_x, this->m_p);

#ifdef DEBUG
  std::cout << "private key: { " << this->m_p << ", " << this->m_g << ", "
            << this->m_y << " }";
#endif

  this->m_k = 5;//rand() % this->m_p + 1;
  this->m_h = 3;//MaHash7(msg, std::strlen(reinterpret_cast<char*>(msg)));

  m_pSign_scheme->msg = msg;
  m_pSign_scheme->a = pow_mod(this->m_g, this->m_k, this->m_p);
  m_pSign_scheme->b = MOD(((this->m_h - this->m_x * m_pSign_scheme->a) * inverse(static_cast<ulong512_t>(this->m_k), static_cast<ulong512_t>(this->m_p - 1))),
    (this->m_p - 1));
  std::cout << "<" << msg << ", " << m_pSign_scheme->a << ", " << m_pSign_scheme->b << ">";
}

unsigned int CElgamal_sign::MaHash7(unsigned char *str, unsigned int len) {
  unsigned int hash = len, i;

  for (i = 0; i != len * ITERATIONS; i++)
  {
    str += (i % len);
    hash = LROT13 (hash + ((hash << 8) ^ (hash >> 12))) - sTable[(*str + i) & 255];
  }
  return hash;
}

void CElgamal_sign::extended_euclid(long a, long b, long *x, long *y, long *d) {
  long q, r, x1, x2, y1, y2;

  if (b == 0) {
    *d = a, *x = 1, *y = 0;
    return;
  }

  x2 = 1, x1 = 0, y2 = 0, y1 = 1;
  while (b > 0) {
    q = a / b, r = a - q * b;
    *x = x2 - q * x1, *y = y2 - q * y1;
    a = b, b = r;
    x2 = x1, x1 = *x, y2 = y1, y1 = *y;
  }
  *d = a, *x = x2, *y = y2;
}

long CElgamal_sign::inverse(long a, long n) {
  long d, x, y;
  extended_euclid(a, n, &x, &y, &d);
  if (d == 1) return x;
  return 0;
}

void CElgamal_sign::check_sign(u_char* msg) {
  ulong512_t tmp_hash = 3;
//  ulong512_t tmp_hash = MaHash7(msg, std::strlen(reinterpret_cast<char*>(msg)));
  ulong512_t lhs = static_cast<ulong512_t>((pow_mod(this->m_y, m_pSign_scheme->a, this->m_p) * pow_mod(m_pSign_scheme->a, m_pSign_scheme->b, this->m_p)) % this->m_p);
  ulong512_t rhs = static_cast<ulong512_t>(pow_mod(this->m_g, tmp_hash, this->m_p));

  if (lhs == rhs) std::cout << "good" << std::endl;
  else std::cout << "wrong" << std::endl;
}
