/*
 * fastmem.h
 *
 * Fast versions of memset() and memcpy() that use unrolled loops, acheiving
 * maximum possible speed on the AVR8 architecture.
 */


#ifndef FASTMEM_H_
#define FASTMEM_H_

#include <string.h>

#ifndef __OPTIMIZE__
# warning "Compiler optimizations disabled; functions from fastmem.h won't work as designed"
#endif

#define MAX_UNROLL	511		// Limits maximum iterations to be unrolled before falling back
							// to avr-libc functions. Cannot be more than 511 unless you add
							// additional conditions below



static inline void * fmemset(void *str, uint16_t c, size_t n)
{
	if (n > MAX_UNROLL)
		return memset(str, c, n);

	void *p = str;

#define __ms1		"st		X+, %[cb]"	"\n\t"
#define __ms8		__ms1 __ms1 __ms1 __ms1 __ms1 __ms1 __ms1 __ms1
#define __msz1		"st		X+, __zero_reg__"	"\n\t"
#define __msz8		__msz1 __msz1 __msz1 __msz1 __msz1 __msz1 __msz1 __msz1

	if (c == 0)
	{
		if (n >= 256)
		{
			asm volatile(
				__msz8 __msz8 __msz8 __msz8 __msz8 __msz8 __msz8 __msz8
				__msz8 __msz8 __msz8 __msz8 __msz8 __msz8 __msz8 __msz8
				__msz8 __msz8 __msz8 __msz8 __msz8 __msz8 __msz8 __msz8
				__msz8 __msz8 __msz8 __msz8 __msz8 __msz8 __msz8 __msz8
			: "=x" (p)
			: "x" (p)
			: // no clobbers
			);
			n -= 256;
		}

		if (n >= 128)
		{
			asm volatile(
				__msz8 __msz8 __msz8 __msz8 __msz8 __msz8 __msz8 __msz8
				__msz8 __msz8 __msz8 __msz8 __msz8 __msz8 __msz8 __msz8
			: "=x" (p)
			: "x" (p)
			: // no clobbers
			);
			n -= 128;
		}

		if (n >= 64)
		{
			asm volatile(
				__msz8 __msz8 __msz8 __msz8 __msz8 __msz8 __msz8 __msz8
			: "=x" (p)
			: "x" (p)
			: // no clobbers
			);
			n -= 64;
		}

		if (n >= 32)
		{
			asm volatile(
				__msz8 __msz8 __msz8 __msz8
			: "=x" (p)
			: "x" (p)
			: // no clobbers
			);
			n -= 32;
		}

		if (n >= 16)
		{
			asm volatile(
				__msz8 __msz8
			: "=x" (p)
			: "x" (p)
			: // no clobbers
			);
			n -= 16;
		}

		if (n >= 8)
		{
			asm volatile(
				__msz8
			: "=x" (p)
			: "x" (p)
			: // no clobbers
			);
			n -= 8;
		}

		if (n >= 4)
		{
			asm volatile(
				__msz1 __msz1 __msz1 __msz1
			: "=x" (p)
			: "x" (p)
			: // no clobbers
			);
			n -= 4;
		}

		if (n >= 2)
		{
			asm volatile(
				__msz1 __msz1
			: "=x" (p)
			: "x" (p)
			: // no clobbers
			);
			n -= 2;
		}

		if (n >= 1)
		{
			asm volatile(
				__msz1
			: "=x" (p)
			: "x" (p)
			: // no clobbers
			);
			n -= 1;
		}

		return str;
	}

	// c != 0
	if (n >= 256)
	{
		asm volatile(
			__ms8 __ms8 __ms8 __ms8 __ms8 __ms8 __ms8 __ms8
			__ms8 __ms8 __ms8 __ms8 __ms8 __ms8 __ms8 __ms8
			__ms8 __ms8 __ms8 __ms8 __ms8 __ms8 __ms8 __ms8
			__ms8 __ms8 __ms8 __ms8 __ms8 __ms8 __ms8 __ms8
		: "=x" (p)
		: "x" (p), [cb] "r" (c & 0xFF)
		: // no clobbers
		);
		n -= 256;
	}

	if (n >= 128)
	{
		asm volatile(
			__ms8 __ms8 __ms8 __ms8 __ms8 __ms8 __ms8 __ms8
			__ms8 __ms8 __ms8 __ms8 __ms8 __ms8 __ms8 __ms8
		: "=x" (p)
		: "x" (p), [cb] "r" (c & 0xFF)
		: // no clobbers
		);
		n -= 128;
	}

	if (n >= 64)
	{
		asm volatile(
			__ms8 __ms8 __ms8 __ms8 __ms8 __ms8 __ms8 __ms8
		: "=x" (p)
		: "x" (p), [cb] "r" (c & 0xFF)
		: // no clobbers
		);
		n -= 64;
	}

	if (n >= 32)
	{
		asm volatile(
			__ms8 __ms8 __ms8 __ms8
		: "=x" (p)
		: "x" (p), [cb] "r" (c & 0xFF)
		: // no clobbers
		);
		n -= 32;
	}

	if (n >= 16)
	{
		asm volatile(
			__ms8 __ms8
		: "=x" (p)
		: "x" (p), [cb] "r" (c & 0xFF)
		: // no clobbers
		);
		n -= 16;
	}

	if (n >= 8)
	{
		asm volatile(
			__ms8
		: "=x" (p)
		: "x" (p), [cb] "r" (c & 0xFF)
		: // no clobbers
		);
		n -= 8;
	}

	if (n >= 4)
	{
		asm volatile(
			__ms1 __ms1 __ms1 __ms1
		: "=x" (p)
		: "x" (p), [cb] "r" (c & 0xFF)
		: // no clobbers
		);
		n -= 4;
	}

	if (n >= 2)
	{
		asm volatile(
			__ms1 __ms1
		: "=x" (p)
		: "x" (p), [cb] "r" (c & 0xFF)
		: // no clobbers
		);
		n -= 2;
	}

	if (n >= 1)
	{
		asm volatile(
			__ms1
		: "=x" (p)
		: "x" (p), [cb] "r" (c & 0xFF)
		: // no clobbers
		);
		n -= 1;
	}

	return str;

#undef __ms1
#undef __ms8
#undef __msz1
#undef __msz8
}

static inline void * fmemcpy(void *dest, void *src, size_t n)
{
	if (n > MAX_UNROLL)
		return memcpy(dest, src, n);

	void *pd = dest;
	void *ps = src;

#define __cp1		"ld		__tmp_reg__, Z+"	"\n\t" \
					"st		X+, __tmp_reg__"	"\n\t"
#define __cp8		__cp1 __cp1 __cp1 __cp1 __cp1 __cp1 __cp1 __cp1

	if (n >= 256)
	{
		asm volatile(
			__cp8 __cp8 __cp8 __cp8 __cp8 __cp8 __cp8 __cp8
			__cp8 __cp8 __cp8 __cp8 __cp8 __cp8 __cp8 __cp8
			__cp8 __cp8 __cp8 __cp8 __cp8 __cp8 __cp8 __cp8
			__cp8 __cp8 __cp8 __cp8 __cp8 __cp8 __cp8 __cp8
		: "=x" (pd), "=z" (ps)
		: "x" (pd), "z" (ps)
		: // no clobbers
		);
		n -= 256;
	}

	if (n >= 128)
	{
		asm volatile(
			__cp8 __cp8 __cp8 __cp8 __cp8 __cp8 __cp8 __cp8
			__cp8 __cp8 __cp8 __cp8 __cp8 __cp8 __cp8 __cp8
		: "=x" (pd), "=z" (ps)
		: "x" (pd), "z" (ps)
		: // no clobbers
		);
		n -= 128;
	}

	if (n >= 64)
	{
		asm volatile(
			__cp8 __cp8 __cp8 __cp8 __cp8 __cp8 __cp8 __cp8
		: "=x" (pd), "=z" (ps)
		: "x" (pd), "z" (ps)
		: // no clobbers
		);
		n -= 64;
	}

	if (n >= 32)
	{
		asm volatile(
			__cp8 __cp8 __cp8 __cp8
		: "=x" (pd), "=z" (ps)
		: "x" (pd), "z" (ps)
		: // no clobbers
		);
		n -= 32;
	}

	if (n >= 16)
	{
		asm volatile(
			__cp8 __cp8
		: "=x" (pd), "=z" (ps)
		: "x" (pd), "z" (ps)
		: // no clobbers
		);
		n -= 16;
	}

	if (n >= 8)
	{
		asm volatile(
			__cp8
		: "=x" (pd), "=z" (ps)
		: "x" (pd), "z" (ps)
		: // no clobbers
		);
		n -= 8;
	}

	if (n >= 4)
	{
		asm volatile(
			__cp1 __cp1 __cp1 __cp1
		: "=x" (pd), "=z" (ps)
		: "x" (pd), "z" (ps)
		: // no clobbers
		);
		n -= 4;
	}

	if (n >= 2)
	{
		asm volatile(
			__cp1 __cp1
		: "=x" (pd), "=z" (ps)
		: "x" (pd), "z" (ps)
		: // no clobbers
		);
		n -= 2;
	}

	if (n >= 1)
	{
		asm volatile(
			__cp1
		: "=x" (pd), "=z" (ps)
		: "x" (pd), "z" (ps)
		: // no clobbers
		);
		n -= 1;
	}

	return dest;

#undef __cp1
#undef __cp8
}



#endif /* FASTMEM_H_ */