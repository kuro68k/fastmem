# fastmem

Fast `memset()` and `memcpy()` functions for AVR.

The `fmemset()` and `fmemcpu()` functions compile down to unrolled loops of load/store instructions, which on the AVR 8 bit archtiecture is the fastest possible way to implement these functions. No loops are used at all, trading speed for code size.

The `avr-libc` functions use loops and are significantly slower, but also significantly smaller.
