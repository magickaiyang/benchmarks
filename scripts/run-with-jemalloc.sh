#!/bin/bash
set -e
set -x

script_path=$(dirname $0)
export LD_PRELOAD=`realpath $script_path/jemalloc/libjemalloc.so.2`
"$@"
