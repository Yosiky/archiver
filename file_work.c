#include "file_work.h"

const size_t MAX_SIZE_STR = 256;

FILE* file_open() 
{
	char name_file[MAX_SIZE_STR];
	scanf("%s", name_file);
	return fopen(name_file, "r");
}

size_t* file_read(FILE* file)
{
	size_t* mas = (size_t*)calloc(MAX_SIZE_STR, sizeof(size_t));
	int value;
	do {
		value = fgetc(file);
		if (value == EOF)
			break;
		mas[value]++;
	} while (value != EOF);
	return mas;
}
