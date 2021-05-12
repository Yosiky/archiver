#ifndef SYMBOL_H
#define SYMBOL_H

#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"

typedef struct Symbol{
        unsigned char* ch;
        float freq;
        size_t count;
        char* word;
        size_t size;
} Symbol;

typedef struct Pair {
        Symbol* mas; 
        size_t size;
	size_t count;
        
} Pair;


typedef struct Tree_ {
	Symbol* obj;
	struct Tree_* next_left;
	struct Tree_* next_right;
	
} Tree;


Pair* processing(const size_t* mas, const size_t size) {
        Pair* res = (Pair*)malloc(sizeof(Pair));
        size_t k = 0;
        for (size_t i = 0; i < size; i++) {
                if (mas[i]) {
			++k;
                }
        }
        res->mas = (Symbol*)malloc(sizeof(Symbol)*(k));
        res->size = 0;
	res->count = 0;
	for (size_t i = 0; i < size; i++) {
                res->count += mas[i];
        }
        for (size_t i = 0; i < size; i++) {
                if (mas[i]/* && i != 10*/) {
			res->mas[++res->size - 1].ch = (unsigned char*)malloc(2*sizeof(char));
                        res->mas[res->size - 1].ch[0] = (unsigned char)i;
                        res->mas[res->size - 1].ch[1] = '\0';
                        res->mas[res->size - 1].freq = (double)mas[i] / res->count;
                        res->mas[res->size - 1].count = mas[i];
                }
        }
        return res;
}

void print_sym(const Symbol* obj)
{
        printf("%s %f %ld %s\n", (obj->ch), (obj->freq), (obj->count), (obj->word));
}


#endif
