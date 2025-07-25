#!/bin/bash

# scale-factor controls memory usage. When it is 30, the peak memory usage is 119GB
# runtime controls how long the benchmark runs.
# num-threads controls the number of threads

# On a two NUMA node machine, when memory and cpu are from different nodes, avg_per_core_throughput: 46303.2 ops/sec/core
# When memory and cpu are from the same node, avg_per_core_throughput: 54424.3 ops/sec/core
# A perf loss of -15%

out-perf.masstree/benchmarks/dbtest \
    --verbose \
    --bench tpcc \
    --num-threads 26 \
    --scale-factor 30 \
    --runtime 240 \
