#include <iostream>
#include "Generator.h"
#include "Alice.h"
#include "Bob.h"


int main() {
  srand(time(0));
  Generator sample;
  uint1024_t p("3586420730428501486799804587268520423291459681059978161140231860633948450858040593963"),
    q("7267029064107019078863797763923946264136137803856996670313708936002281582249587494493");


  std::cout << sample.gen_N(p, q) << std::endl;
  std::cout << "v = " << sample.gen_V() << std::endl;
  Alice alice(sample);
  Bob bob;
  bob.set_x(alice.get_x());
  bob.sendRandBit(alice);
  if (alice.get_bit() == 0) {
    bob.set_r(alice.get_r());
  }
  else {
    bob.set_y(alice.get_y());
    
  }
  return 0;
}