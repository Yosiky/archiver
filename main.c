#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "symbol.h"
#include "file_work.h"

Pair* input(FILE* file)
{
	size_t* mas = file_read(file);
	Pair* res = processing(mas, MAX_SIZE_STR);
	free(mas);
	return res;
}

void print_pair(const Pair* obj) 
{
	for (size_t i = 0; i < obj->size; i++) {
		print_sym(&(obj->mas[i]));
	}
}

int main() 
{
	FILE* file = file_open();
	Pair* value = input(file);
	print_pair(value);

	free(value->mas);
	free(value);
	fclose(file);
	return 0;
}
