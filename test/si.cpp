#include <iostream>
#include <si.hpp>

using namespace si;


int main() {
  auto slow = 10_km / 1_h;
  auto fast = 10_m / 1_s;
  
  std::cout << "the slow speed is: " << slow.value() << " m/s\n";
  std::cout << "the fast speed is: " << fast.value() << " m/s\n";
  std::cout << "slow < fast " << std::boolalpha << (slow < fast) << std::endl;
  //Mass M = fast;
      
  return 0;
}
