#include <stdio.h>
#include "libchicken.h"

int main(int argc, char **argv)
{
	fprintf(stderr, "hello, world\n");
	uint8_t *rom = malloc(0x800);
//	rom_load_zip("invaders.h","invaders.zip", rom, 0x800, 0);
//	memory_dump("test.dmp", rom, 0x800, 0);	 
	free(rom);	
	return 0;
}
