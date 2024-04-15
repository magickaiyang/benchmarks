#!/bin/bash
set -e
set -x

# around 32GB resident size
# around 1.3s runtime on entropy
./gups_opt 32 3000
