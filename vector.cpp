#include "common.h"
#include "cpu.h"

#include <iostream>
#include <array>

int main() {
  std::cout << "N = " << N << std::endl;

  int res = 0;

  for (int i = 0; i < N / 4; ++i) {
    std::array<int64_t, 4> digits{1, 1, 1, 1};
    std::array<int64_t, 4> curr_power{10, 10, 10, 10};

    for (int k = 0; k < GetHighestSetBit(N - 1); ++k) {
      if (GetKBitOfN(N - 1, k)) {
        for (int j = 0; j < 4; ++j) {
          digits[j] = (digits[j] * curr_power[j]) % (4 * i + j + 1);
        }
      }

      for (int j = 0; j < 4; ++j) {
        curr_power[j] = (curr_power[j] * curr_power[j]) % (4 * i + j + 1);
      }
    }

    for (int j = 0; j < 4; ++j) {
      digits[j] *= 10;
      digits[j] /= 4 * i + j + 1;
    }

    for (int j = 0; j < 4; ++j) {
      res += digits[j];
    }
  }

  std::cout << res << std::endl;

  return 0;
}
