#!/bin/bash

# scale-factor, runtime, and number of threads influence memory usage. Memory usage gradually increases.
# The current settings has a peak memory usage of about 120 GB right before the benchmark ends.
# runtime controls how long the benchmark runs.
# num-threads controls the number of threads

# On a two NUMA node machine, when memory and cpu are from different nodes, avg_per_core_throughput: 46303.2 ops/sec/core
# When memory and cpu are from the same node, avg_per_core_throughput: 54424.3 ops/sec/core
# A perf loss of -15%

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

rm -rf $SCRIPT_DIR/results/
mkdir -p $SCRIPT_DIR/results/

$SCRIPT_DIR/out-perf.masstree/benchmarks/dbtest \
    --verbose \
    --bench tpcc \
    --num-threads 10 \
    --scale-factor 29 \
    --runtime 600 > $SCRIPT_DIR/results/silo.out 2>&1
