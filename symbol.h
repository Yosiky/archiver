#ifndef SYMBOL_H
#define SYMBOL_H

typedef sturct {
	unsigned char ch;
	float freq;
	size_t count;
} Symbol;

typedef struct {
	Symbol* mas; 
	size_t size;
} Pair;

Pair* processing(const unsigned char* mas, const size_t size) {
	Pair* res = (Pair*)malloc(size_of(Pair));
	size_t count = 0;
	for (size_t i = 0; i < size; i++) {
		if (mas[i])
			count++;
	}
	res->mas = (Symbol*)malloc(size_of(Symbol)*count);
	res->size = 0;
	for (size_t i = 0; i < size; i++) {
		if (mas[i]) {
			res->mas[++size - 1].ch = (unsigned char)i;
			res->mas[size - 1].freq = 0;
			res->mas[size - 1].count = mas[i];
		}
	}
	return res;
}


#endif 	