/*
 * fastmem.c
 *
 */

#include <avr/io.h>
#include <stddef.h>
#include "fastmem.h"

uint8_t buffer[1024];
uint8_t test = 2;

void testing(void)
{
	GPIO0 = buffer[5];
	fmemcpy(buffer, buffer+512, 5);
	GPIO0 = buffer[5];
}

int main(void)
{
	fmemset(buffer, 0, 19);

	buffer[0] = 1;

	GPIO2 = test;
	testing();
	GPIO2 = test;

	for(;;);
}

