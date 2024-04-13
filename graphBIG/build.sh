#!/bin/bash
set -e
set -x

cd benchmark/
make clean
make PFM=0 EDGES=1 SIM=1 -j16 clean all
