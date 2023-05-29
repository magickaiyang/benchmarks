#!/bin/bash
set -e
set -x

cd benchmark/
make PFM=0 EDGES=1 clean all
