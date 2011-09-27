#include <stdio.h>
#include "util.h"
int memory_dump(char *filename, uint8_t *pointer, size_t length, size_t offset)
{
	FILE *fp = fopen(filename, "wb+");
	fwrite(&pointer[offset], length, 1, fp);
	fclose(fp);
}

int rom_load(char *filename, uint8_t *pointer, size_t size, size_t offset)
{
	FILE *fp;
	fp = fopen(filename,"rb");
	if(fp == NULL)
	{
		fprintf(stderr, "Couldn't open file: %s\n",filename);
		return -1;
	}
	fread(&pointer[offset], 1, size, fp);
	fclose(fp);
	return 0;
}

/*
int loadROM()
{
	FILE *fp;
	fp = fopen("invaders.h","rb");
	fread(RAM, 1, 0x800, fp);
	fclose(fp);
	fp = fopen("invaders.g","rb");
	fread(&RAM[0x800], 1, 0x800, fp);
	fclose(fp);
	fp = fopen("invaders.f","rb");
	fread(&RAM[0x1000], 1, 0x800, fp);
	fclose(fp);
	fp = fopen("invaders.e","rb");
	fread(&RAM[0x1800], 1, 0x800, fp);
	fclose(fp);

	return 0;
	
}*/

