#pragma once

#include <cstdint>
#include <utility>

#include "fastmod.h"
#include "libdivide.h"

constexpr int GetKBitOfN(int32_t n, int k) {
  return (n >> k) & 1;
}

// Get index of highest set bit in a 32-bit integer.
// In 1-index.
constexpr int GetHighestSetBit(int32_t n) {
  return sizeof(int32_t) * 8 - __builtin_clz(n);
}

constexpr int32_t ExpModuloRecursive(int32_t power, int32_t modulo) {
  if (power == 0)
    return 1;

  auto res = ExpModuloRecursive(power / 2, modulo);
  if (power % 2 == 0) {
    return (static_cast<int64_t>(res) * res) % modulo;
  } else {
    return (static_cast<int64_t>(res) * res * 10) % modulo;
  }
}

constexpr int32_t ExpModuloBit(int32_t power, int32_t modulo) {
  int64_t res = 1;
  int64_t curr_power = 10;

  for (int i = 0; i < GetHighestSetBit(power); ++i) {
    if (GetKBitOfN(power, i)) {
      res = (res * curr_power) % modulo;
    }
    curr_power = (curr_power * curr_power) % modulo;
  }

  return res;
}

int32_t ExpModuloBitWithLibDivide(int32_t power, int32_t modulo) {
  int64_t res = 1;
  int64_t curr_power = 10;

  libdivide::divider<int64_t> fast_modulo(modulo);

  auto fast_mod = [](int64_t x, auto modulo, auto fast_modulo) {
    return x - (x / fast_modulo) * modulo;
  };

  for (int i = 0; i < GetHighestSetBit(power); ++i) {
    if (GetKBitOfN(power, i)) {
      res = fast_mod((res * curr_power), modulo, fast_modulo);
    }
    curr_power = fast_mod((curr_power * curr_power), modulo, fast_modulo);
  }

  return res;
}

// Using faster modulo
// https://lemire.me/blog/2019/02/08/faster-remainders-when-the-divisor-is-a-constant-beating-compilers-and-libdivide/
constexpr int32_t ExpModuloBitWithFastMod(int32_t power, int32_t modulo) {
  int64_t res = 1;
  int64_t curr_power = 10;

  auto M = fastmod::computeM_u64(modulo);

  for (int i = 0; i < GetHighestSetBit(power); ++i) {
    if (GetKBitOfN(power, i)) {
      res = fastmod::fastmod_u64(res * curr_power, M, modulo);
    }
    curr_power = fastmod::fastmod_u64(curr_power * curr_power, M, modulo);
  }

  return res;
}

template <typename Func>
constexpr int GetNDigitOfFracX(int32_t n, int32_t x, Func &&exp) {
  return exp(n - 1, x) * 10 / x;
}

template <typename Func>
constexpr int32_t CalculateS(int32_t n, Func &&exp) {
  int32_t res = 0;
  for (auto i = 1; i <= n; ++i) {
    res += GetNDigitOfFracX(n, i, exp);
  }

  return res;
}

template <typename Func>
constexpr int32_t CalculatePartialS(int32_t n, int32_t start, int32_t end, Func &&exp) {
  int32_t res = 0;
  for (auto i = start; i <= end; ++i) {
    res += GetNDigitOfFracX(n, i, exp);
  }

  return res;
}

#ifdef ENABLE_ARM_NEON

#include <arm_neon.h>

int32_t CalculateSWithArmNeon(int32_t n) {
  int32_t res = 0;
  // Assume N % 2 == 0
  for (auto i = 1; i <= n / 2; ++i) {
    // Handle 2 * i - 1 and 2 * i
    uint64x2_t digits = {2 * i - 1, 2 * i};
    uint64x2_t curr_power = {10, 10};

      curr_power = (curr_power * curr_power) % modulo;

    for (int bit = 0; i < GetHighestSetBit(power); ++bit) {
      if (GetKBitOfN(power, i)) {
        res = (res * curr_power) % modulo;
      }
      curr_power = (curr_power * curr_power) % modulo;
    }
  }


  return res;
}

#endif
