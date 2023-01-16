#include <string>
#include <iostream>
#include <cstdint>

#define ALWAYS_INLINE inline __attribute__((always_inline))

ALWAYS_INLINE int GetKBitOfN(int64_t n, int k) {
  return (n >> k) & 1;
}

// Calculate 10^power % modulo
ALWAYS_INLINE int64_t TenPowerModulo(int64_t power, int64_t modulo) {
  int64_t res = 1;
  int64_t curr_power = 10;

  for (int i = 0; i < fls(power); ++i) {
    if (GetKBitOfN(power, i)) {
      res = (res * curr_power) % modulo;
    }
    curr_power = (curr_power * curr_power) % modulo;
  }

  return res;
}

// Get N-th decimal digit of 1/i
// It is (10^N / i) % 10
//     = 10^(N - 1) % i * 10 / i
ALWAYS_INLINE int GetNthDigit(int64_t i, int64_t N) {
  return TenPowerModulo(N - 1, i) * 10 / i;
}

int main(int argc, char *argv[]) {
  // Calculate S(N)
  int64_t N = std::stoll(argv[1]);

  int64_t res = 0;
  for (int64_t i = 1; i <= N; ++i) {
    res += GetNthDigit(i, N);
  }

  std::cout << "S(" << N << ") = " << res << "\n";

  return 0;
}
