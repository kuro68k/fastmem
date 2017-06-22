/*
 * fastmem.c
 *
 */

#include <avr/io.h>
#include <stddef.h>
#include "fastmem.h"

uint8_t buffer[1024];

int main(void)
{
	fmemset(buffer, 0, 19);

	buffer[0] = 1;
	GPIO0 = buffer[0];

	fmemcpy(buffer, buffer+512, 5);

	GPIO1 = buffer[0];

	for(;;);
}

