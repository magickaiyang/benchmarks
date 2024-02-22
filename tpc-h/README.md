# Usage

1. Compile sqlite shell using `make`
2. Generate the data using dbgen
    - Compile it first by going into the `tpc-h-3.0.1/dbgen` dir and `make`
    - Run `dbgen -s <scale factor>`
    - The scale factor controls the data size. 
    - The default factor 1 has a memory usage of ~1.3GB.
    - Factor 2 uses ~2.6GB.
    - 
3. Run `run.sh`
    - Instrumentations are in the sqlite shell
    - Sets `/proc/self/sim_target` in the main function.
    - `.sim` command issues start sim magicop.
    - `.quit` command issues end sim magicop. 
