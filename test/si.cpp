#include <type_traits>
#include <iostream>
#include <si.hpp>

using namespace si;


Energy Ekin(Mass m, Speed v) {
  return 0.5 * m * (v * v);
}


int main() {
  auto slow = 10_km / 1_h;
  auto fast = 10_m / 1_s;

  std::cout << "slow: " << slow.value() << ' ' << unit_str(slow) << '\n';
  std::cout << "fast: " << fast.value() << ' ' << unit_str(fast) << '\n';
  std::cout << "slow < fast " << std::boolalpha << (slow < fast) << '\n';

  auto ekin = Ekin(80_kg, fast);
  std::cout << "ekin = " << ekin.value() << " " << unit_str(ekin) << '\n';
  std::cout << "ekin == 4000 J: " << std::boolalpha << (ekin == 4000_J) << '\n';

  {
    // type_traits? decltype??? decltype!
    static_assert(std::is_same_v<decltype(ekin), Energy>);

    using Accel = decltype(1_m / (1_s * 1_s));
    Force f = 2_kg * Accel{5};
  }

  constexpr auto GHz = 1'000'000'000 / 1_s;
  constexpr auto ns = 1_s / 1'000'000'000;

  const auto cpu_clock = 4 * GHz;
  auto memory_latency = 70 * ns;
  std::cout << "clock cycles wasted: " << double(cpu_clock * memory_latency) << '\n';

  return 0;
}
