#include <stdio.h>
#include <strings.h>
#include <ctype.h>
#include <assert.h>
#include "unzip.h"
#include "libchicken.h"

int memory_dump(char *filename, uint8_t *pointer, size_t length, size_t offset)
{
	FILE *fp = fopen(filename, "wb+");
	fwrite(&pointer[offset], length, 1, fp);
	fclose(fp);
}

void flags_print(char *string, size_t length, uint32_t value)
{
	int i;
	assert(strlen(string) == length);
	for(i = 0; i < length; i++)
	{
		char print;
		if(value & (0x1 << (length-i)))
		{
			print = toupper(string[i]);
		}
		else
		{
			
			print = tolower(string[i]);
		}
		fprintf(stderr, "%c", print); 



	}



}
//TODO: add path argument
size_t rom_load(char *filename, uint8_t *pointer, size_t size, size_t offset)
{
	size_t ret;

	FILE *fp = fopen(filename,"rb");
	if(fp == NULL)
	{
		fprintf(stderr, "Couldn't open file: %s\n",filename);
		return -1;
	}
	ret = fread(&pointer[offset], 1, size, fp);
	fclose(fp);

	return ret;
}
//TODO
size_t rom_load_zip(char *filename, char *zipfile, uint8_t *pointer, size_t size, size_t offset)
{
	size_t ret;

/*	unzFile fp = unzOpen(filename);
	if(unzLocateFile(fp, filename, 2) == UNZ_OK)
	{ 

	}
	else
	{
		ret = -1;	
	}
	unzClose(fp);*/
	return -1;
}

