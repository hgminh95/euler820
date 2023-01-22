#include "common.h"
#include "cpu.h"

#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <array>

int32_t CalculatePartialSUnroll(int32_t start, int32_t end) {
  auto i = start;
  int32_t res{0};

  for (; i + 3 <= end; i += 4) {
    std::array<int64_t, 4> digits{1, 1, 1, 1};
    std::array<int64_t, 4> curr_power{10, 10, 10, 10};

    for (int k = 0; k < GetHighestSetBit(N - 1); ++k) {
      if (GetKBitOfN(N - 1, k)) {
        for (int j = 0; j < 4; ++j) {
          digits[j] = (digits[j] * curr_power[j]) % (i + j);
        }
      }

      for (int j = 0; j < 4; ++j) {
        curr_power[j] = (curr_power[j] * curr_power[j]) % (i + j);
      }
    }

    for (int j = 0; j < 4; ++j) {
      digits[j] *= 10;
      digits[j] /= i + j;
    }

    for (int j = 0; j < 4; ++j) {
      res += digits[j];
    }
  }

  for (; i <= end; ++i) {
    res += GetNDigitOfFracX(N, i,
            [](int32_t n, int32_t x) { return ExpModuloBit(n, x); });
  }

  return res;
}

int main() {
  std::cout << "N = " << N << std::endl;

  std::atomic<int32_t> sum{0};

  static int NUM_THREADS = std::min<int>(8, std::thread::hardware_concurrency());

  std::cout << "Spawn into " << NUM_THREADS << " threads" << std::endl;

  std::vector<std::thread> threads;

  for (int i = 0; i < NUM_THREADS; ++i) {
    threads.push_back(std::thread([&sum, i]() {
        // Run from i * N / NUM_THREADS + 1
        auto start = i * N / NUM_THREADS + 1;
        auto end = (i + 1) * N / NUM_THREADS;
        sum.fetch_add(CalculatePartialSUnroll(start, end));
    }));
  }

  for (auto &thread : threads) {
    thread.join();
  }

  std::cout << sum << std::endl;
  return 0;
}
