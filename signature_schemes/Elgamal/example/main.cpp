#include <iostream>
#include "../Elgamal_sign.h"


//void extended_euclid(long a, long b, long *x, long *y, long *d) {
//  long q, r, x1, x2, y1, y2;
//
//  if (b == 0) {
//    *d = a, *x = 1, *y = 0;
//    return;
//  }
//
//  x2 = 1, x1 = 0, y2 = 0, y1 = 1;
//  while (b > 0) {
//    q = a / b, r = a - q * b;
//    *x = x2 - q * x1, *y = y2 - q * y1;
//    a = b, b = r;
//    x2 = x1, x1 = *x, y2 = y1, y1 = *y;
//  }
//  *d = a, *x = x2, *y = y2;
//}
//
//
//
///* computes the inverse of a modulo n */
//long inverse(long a, long n) {
//  long d, x, y;
//  extended_euclid(a, n, &x, &y, &d);
//  if (d == 1) return x;
//  return 0;
//}


int main() {
  CElgamal_sign obj;
  u_char msg[4] = "qwe";
  obj.sign_msg(msg);
  obj.check_sign(msg);
  return 0;
}



//#include <stdio.h>
///*
//А затем уже находится s по формуле:
//s = ((m-x*r)*y) mod (p-1);
// */
//
//typedef long long int long512_t;
//
///* calculates a * *x + b * *y = gcd(a, b) = *d */
//void extended_euclid(long a, long b, long *x, long *y, long *d) {
//  long q, r, x1, x2, y1, y2;
//
//  if (b == 0) {
//    *d = a, *x = 1, *y = 0;
//    return;
//  }
//
//  x2 = 1, x1 = 0, y2 = 0, y1 = 1;
//  while (b > 0) {
//    q = a / b, r = a - q * b;
//    *x = x2 - q * x1, *y = y2 - q * y1;
//    a = b, b = r;
//    x2 = x1, x1 = *x, y2 = y1, y1 = *y;
//  }
//  *d = a, *x = x2, *y = y2;
//}
//
//
//
///* computes the inverse of a modulo n */
//long inverse(long a, long n) {
//  long d, x, y;
//  extended_euclid(a, n, &x, &y, &d);
//  if (d == 1) return x;
//  return 0;
//}
//
//int main() {
////  printf("the inverse of %ld modulo %2ld is %ld\n", a, n, inverse(a, n));
//  int x, y;
//  long long int b = MOD(((3 - 7 * 20) * inverse(5, 22)), 22); // formula: p + ((m - x * r) * y) % 22
//  std::cout << "b is: " << b << std::endl;
//
//  return 0;
//}