#include <stdint.h>
int memory_dump(char *filename, uint8_t *pointer, size_t length, size_t offset);
int rom_load(char *filename, uint8_t *pointer, size_t size, size_t offset);
