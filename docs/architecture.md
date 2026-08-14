# Architecture

The original 1186-line single C file is separated by responsibility instead of arbitrary line ranges.

The `.h` files expose module interfaces, while `.c` files contain the implementations. Shared arrays and counters are defined once in `data.c` and declared with `extern` in `common.h`.
