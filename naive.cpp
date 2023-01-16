#include <string>
#include <iostream>
#include <cstdint>

int64_t TenPowerModulo(int64_t power, int64_t modulo) {
  if (power == 0)
    return 1;

  auto half = TenPowerModulo(power / 2, modulo);

  if (power % 2 == 0) {
    return (half * half) % modulo;
  }

  return (half * half * 10) % modulo;
}


// Get N-th decimal digit of 1/i
// It is (10^N / i) % 10
//     = 10^(N - 1) % i * 10 / i
int GetNthDigit(int64_t i, int64_t N) {
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
