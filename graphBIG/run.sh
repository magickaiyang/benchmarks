#!/bin/bash
set -e
set -x

script_dir=$(dirname $0)
$script_dir/benchmark/bench_DFS/dfs --dataset $script_dir/dataset/ldbc
