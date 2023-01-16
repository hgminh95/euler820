#include <string>
#include <iostream>
#include <cstdint>
#include <thread>
#include <vector>

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

constexpr int NUM_THREADS = 8;

int main(int argc, char *argv[]) {
  int64_t N = std::stoll(argv[1]);

  std::vector<std::thread> threads;

  std::atomic<int64_t> res{0};
  for (int index = 0; index <= NUM_THREADS; ++index) {
    threads.push_back(std::thread([&res, N, index]() {
      auto start_index = N / NUM_THREADS * index;
      auto end_index = N / NUM_THREADS * (index + 1) - 1;
      if (index == NUM_THREADS)
        end_index = N;
      int64_t partial_sum = 0;
      for (int64_t i = start_index; i <= end_index; ++i) {
        partial_sum += GetNthDigit(i, N);
      }

      res.fetch_add(partial_sum);
    }));
  }

  for (auto &thread : threads) {
    thread.join();
  }

  std::cout << "S(" << N << ") = " << res << "\n";

  return 0;
}
