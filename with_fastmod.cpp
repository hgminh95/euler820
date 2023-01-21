#include "common.h"
#include "cpu.h"

#include <iostream>

int main() {
  std::cout << "N = " << N << std::endl;
  std::cout
      << CalculateS(N, [](int32_t n, int32_t x) { return ExpModuloBitWithFastMod(n, x); })
      << std::endl;
  return 0;
}
