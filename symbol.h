#ifndef SYMBOL_H
#define SYMBOL_H

#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"

typedef struct Symbol{
	unsigned char ch;
	float freq;
	size_t count;
} Symbol;

typedef struct Pair {
	Symbol* mas; 
	size_t size;
} Pair;

Pair* processing(const size_t*, const size_t);
void print_sym(const Symbol*);

#endif 	