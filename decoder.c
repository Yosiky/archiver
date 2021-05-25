#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "file_work.h"
#include "test.h"

Tree* read_code(FILE* file) {
	Tree* head = (Tree*)malloc(sizeof(Tree));
	int buff;
	Tree* iter = head;
	do {
		buff = fgetc(file);
		if (buff == '\0')
			break;
		Tree* value = (Tree*)malloc(sizeof(Tree));
		value->obj = (Symbol*)malloc(sizeof(Symbol));
		value->obj.ch = (char*)malloc(sizeof(char)); 
		// todo

	} while (buff != '\0');
	return 
}

int main(int argc, char** argv) {
	if (argc == 2)
		return 1;
        FILE* file = fopen(argb[1], "r");
	Tree* value = read(file);		
	
	for (size_t i = 0; i < value->size; ++i) {
                free(value->mas[i].word);
                free(value->mas[i].ch);
        }
        free(value->mas);
        free(value);
	free(value);
	return 0;
}
