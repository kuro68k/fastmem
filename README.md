# fastmem

Fast `memset()` and `memcpy()` functions for AVR.

The `fmemset()` and `fmemcpy()` functions compile down to unrolled loops of load/store instructions, which on the AVR 8 bit archtiecture is the fastest possible way to implement these functions. No loops are used at all, trading speed for code size.

`MAX_UNROLL` sets the maximum number of iterations to be unrolled, after which `memset()` and `memcpy()` will be used instead. If you increase it beyond 511 you will need to add additional power of two unrolled loops to the code.

The `avr-libc` functions use loops and are significantly slower, but also significantly smaller.
