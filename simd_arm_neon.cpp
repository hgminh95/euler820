#include "common.h"
#include "cpu.h"

#include <iostream>

int main() {
  std::cout << "N = " << N << std::endl;
  std::cout
      << CalculateSWithArmNeon(N)
      << std::endl;
  return 0;
}
