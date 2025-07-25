#!/usr/bin/env bash

count_thp() {
  sum=0
  read_stdin=0
  while read -r line; do
      read_stdin=1
      value=$(echo "$line" | awk '{print $2}')
      sum=$((sum + value))
  done
  # Convert the sum to MB
  sum=$((sum / 1024))
  [ $read_stdin -eq 1 ] && echo "$sum MB"
}

pidtarget=$(pidof ${1:-"memcached"})
echo $pidtarget

grep -i anonhugepages /proc/$(pidof ${1:-"memcached"})/smaps_rollup 2>/dev/null | count_thp

while sleep 1; do
    grep -i anonhugepages /proc/$(pidof ${1:-"memcached"})/smaps_rollup 2>/dev/null | count_thp
done
