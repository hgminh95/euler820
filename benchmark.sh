#!/bin/bash

set -e

PLATFORM=$1


if [[ "$PLATFORM" == "m2" || "$PLATFORM" == "zen" || "$PLATFORM" == "cascadelake" ]]; then
  bazel build --config $PLATFORM \
      :recursive \
      :loop \
      :with_fastmod \
      :with_libdivide \
      :vector \
      :multi_thread

  echo "N=10^7"
  echo ""

  echo "Recursive"
  /usr/bin/time ./bazel-bin/recursive
  echo "Loop"
  /usr/bin/time ./bazel-bin/loop
  echo "With FastMod"
  /usr/bin/time ./bazel-bin/with_fastmod
  echo "With libdivide"
  /usr/bin/time ./bazel-bin/with_libdivide
  echo "Vector"
  /usr/bin/time ./bazel-bin/vector
  echo "Multi-Thread"
  /usr/bin/time ./bazel-bin/multi_thread

  bazel build --config $PLATFORM --copt -DM_N=100000000 \
      :recursive \
      :loop \
      :with_fastmod \
      :with_libdivide \
      :vector \
      :multi_thread

  echo "N=10^8"
  echo ""

  echo "Recursive"
  /usr/bin/time ./bazel-bin/recursive
  echo "Loop"
  /usr/bin/time ./bazel-bin/loop
  echo "With FastMod"
  /usr/bin/time ./bazel-bin/with_fastmod
  echo "With libdivide"
  /usr/bin/time ./bazel-bin/with_libdivide
  echo "Vector"
  /usr/bin/time ./bazel-bin/vector
  echo "Multi-Thread"
  /usr/bin/time ./bazel-bin/multi_thread
elif [[ "$PLATFORM" == "gpu" ]]; then
  ./gpu.cu
fi
