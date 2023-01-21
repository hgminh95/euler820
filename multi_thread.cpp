#include "common.h"
#include "cpu.h"

#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

int main() {
  std::cout << "N = " << N << std::endl;

  std::atomic<int32_t> sum{0};

  static int NUM_THREADS = std::min<int>(12, std::thread::hardware_concurrency());

  std::cout << "Spawn into " << NUM_THREADS << " threads" << std::endl;

  std::vector<std::thread> threads;

  for (int i = 0; i < NUM_THREADS; ++i) {
    threads.push_back(std::thread([&sum, i]() {
        // Run from i * N / NUM_THREADS + 1
        auto start = i * N / NUM_THREADS + 1;
        auto end = (i + 1) * N / NUM_THREADS;
        sum.fetch_add(CalculatePartialS(
            N, start, end,
            [](int32_t n, int32_t x) { return ExpModuloBit(n, x); }
        ));
    }));
  }

  for (auto &thread : threads) {
    thread.join();
  }

  std::cout << sum << std::endl;
  return 0;
}
