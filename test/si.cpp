#include <iostream>
#include <si.hpp>

using namespace si;


int main() {
  auto side = 10_m;
  Area area = side * side;
  Volume vol = area * side;

  Speed s = 30_m / 1_s;

  auto vol = 1.0_foot3;
  std::cout << "one cubic foot is " << vol.value() << " [m^3]" << std::endl;

  Angle alpha = 180_deg;
  std::cout << "180 [deg] =  " << alpha.value() << " [rad]" << std::endl;

  return 0;
}
