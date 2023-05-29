#!/bin/bash
set -e
set -x

taskset -c 20 ./gups_opt 30 1000
