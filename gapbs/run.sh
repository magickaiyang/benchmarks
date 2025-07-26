#!/bin/bash

# Requires openmp.
# The original suite Sequentially runs different graph algorithms with different datasets.
# Memory usage is about 20GB per instance.
# By default, uses all available cpus. Set OMP_NUM_THREADS env var to limit it.
# The outputs are in results/*.out. Use the "average time" reported on the last line as application performance.

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

rm -rf $SCRIPT_DIR/results/
mkdir -p $SCRIPT_DIR/results/

export OMP_NUM_THREADS=26

# Run the benchmarks in the suite in groups of 2 or 3

# Group 1
$SCRIPT_DIR/bfs -f $SCRIPT_DIR/benchmark/graphs/web.sg -n64 > $SCRIPT_DIR/results/bfs-web.out &
$SCRIPT_DIR/pr -f $SCRIPT_DIR/benchmark/graphs/web.sg -i1000 -t1e-4 -n16 > $SCRIPT_DIR/results/pr-web.out &
$SCRIPT_DIR/cc -f $SCRIPT_DIR/benchmark/graphs/web.sg -n16 > $SCRIPT_DIR/results/cc-web.out &
wait

# Group 2
$SCRIPT_DIR/bc -f $SCRIPT_DIR/benchmark/graphs/web.sg -i4 -n16 > $SCRIPT_DIR/results/bc-web.out &
$SCRIPT_DIR/bfs -f $SCRIPT_DIR/benchmark/graphs/urand.sg -n64 > $SCRIPT_DIR/results/bfs-urand.out &
$SCRIPT_DIR/pr -f $SCRIPT_DIR/benchmark/graphs/urand.sg -i1000 -t1e-4 -n16 > $SCRIPT_DIR/results/pr-urand.out &
wait

# Group 3
$SCRIPT_DIR/cc -f $SCRIPT_DIR/benchmark/graphs/urand.sg -n16 > $SCRIPT_DIR/results/cc-urand.out &
$SCRIPT_DIR/bc -f $SCRIPT_DIR/benchmark/graphs/urand.sg -i4 -n16 > $SCRIPT_DIR/results/bc-urand.out &
$SCRIPT_DIR/tc -f $SCRIPT_DIR/benchmark/graphs/urandU.sg -n3 > $SCRIPT_DIR/results/tc-urand.out &
wait

# Group 4
$SCRIPT_DIR/sssp -f $SCRIPT_DIR/benchmark/graphs/web.wsg -n64 -d2 > $SCRIPT_DIR/results/sssp-web.out &
$SCRIPT_DIR/tc -f $SCRIPT_DIR/benchmark/graphs/webU.sg -n3 > $SCRIPT_DIR/results/tc-web.out
$SCRIPT_DIR/sssp -f $SCRIPT_DIR/benchmark/graphs/kron.wsg -n64 -d2 > $SCRIPT_DIR/results/sssp-kron.out &
wait
