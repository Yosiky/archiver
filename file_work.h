#ifndef FILE_WORK_H
#define FILE_WORK_H

#include "stdio.h"
#include "stddef.h"

extern const size_t MAX_SIZE_STR = 256;

FILE* file_open() 
{
	char name_file[MAX_SIZE_STR];
	scanf("%s", name_file);
	return fopen(name_file, "r");
}

unsigned char* file_read(FILE* file)
{
	size_t* mas = (size_t*)calloc(MAX_SIZE_STR, size_of(size_t));
	int value;
	do {
		value = fgetc(file);
		if (value == EOF)
			break;
		mas[value]++;
	} while (value != EOF);
	return mas;
}

#endif