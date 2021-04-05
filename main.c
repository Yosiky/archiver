#include "stdio.h"
#include "stdlib.h"
#include "symbol.h"
#include "file_work.h"

Pair* input(FILE* file)
{
	size_t* mas = file_read(file);
	pair* res = processing(mas, MAX_SIZE_STR);
	free(mas);
	return res;
}

int main() 
{
	FILE* file = file_open();
	Pair* value = input(file);


	free(pair->mas);
	free(pair);
	fclose(file);
	return 0;
}