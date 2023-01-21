#!/bin/bash

set -e

sed 1,8d $0 > /tmp/gpu.cu
nvcc --arch=sm_70 /tmp/gpu.cu -o gpu
./gpu

#include <iostream>
#include <cstdio>

int GetKBitOfN(int32_t n, int k) {
  return (n >> k) & 1;
}

int GetHighestSetBit(int32_t n) {
  return sizeof(int32_t) * 8 - __builtin_clz(n);
}

int32_t ExpModuloBit(int32_t power, int32_t modulo) {
  int32_t res = 1;
  int64_t curr_power = 10;

  for (int i = 0; i < GetHighestSetBit(power); ++i) {
    if (GetKBitOfN(power, i)) {
      res = (res * curr_power) % modulo;
    }
    curr_power = (curr_power * curr_power) % modulo;
  }

  return res;
}

const int N = 10000000;

__global__ void CalculateS(int32_t *res) {
  atomicAdd_system(res, 10);
  printf("%d\n", res);
}

int main() {
  int32_t *res;
  cudaMallocManaged(&res, sizeof(res));
  *res = 0;

  CalculateS<<<1, 1>>>(res);

  std::cout << "N = " << N << std::endl;
  std::cout << *res << std::endl;
  return 0;
}
