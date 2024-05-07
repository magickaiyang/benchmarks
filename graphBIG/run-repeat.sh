#!/bin/bash
set -e
set -x

for i in {1..10}; do
	numactl --cpunodebind=0 --membind=0 -- $@ --threadnum 1 --dataset dataset/big --separator ' '
done

