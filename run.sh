#!/bin/bash

# Runs 2 or 3 instances of gapbs with 1 instance of silo
# Repeats gapbs if it finishes earlier than silo
# There are more descriptions of the workloads in run.sh in silo/ and gapbs/
# Notice the memory usage and number of threads in run.sh in the two workload folders and adjust accordingly!

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

"$SCRIPT_DIR/silo/run.sh" &
SILO_PID=$!

"$SCRIPT_DIR/gapbs/run.sh" &
GAPBS_PID=$!

while kill -0 $SILO_PID 2>/dev/null; do
    if ! kill -0 $GAPBS_PID 2>/dev/null; then
        "$SCRIPT_DIR/gapbs/run.sh" &
        GAPBS_PID=$!
    fi
    sleep 1
done

if kill -0 $GAPBS_PID 2>/dev/null; then
    wait $GAPBS_PID
fi

wait $SILO_PID 2>/dev/null
