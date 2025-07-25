#!/bin/bash

# Requires openmp.
# Sequentially runs different graph algorithms with different datasets.
# Memory usage is about 20GB.
# By default, uses all available cpus. Set OMP_NUM_THREADS env var to limit it.
# The outputs are in benchmark/out/*.out. Use the "average time" reported on the last line as application performance.

rm -rf benchmark/out

export OMP_NUM_THREADS=26
make bench-run
