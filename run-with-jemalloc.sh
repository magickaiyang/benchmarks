#!/bin/bash
set -e
set -x

export LD_PRELOAD=`realpath jemalloc/libjemalloc.so.2`
$@
