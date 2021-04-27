#include "symbol.h"

Pair* processing(const size_t* mas, const size_t size) {
	Pair* res = (Pair*)malloc(sizeof(Pair));
	size_t count = 0;
	for (size_t i = 0; i < size; i++) {
		if (mas[i])
			count++;
	}
	res->mas = (Symbol*)malloc(sizeof(Symbol)*count);
	res->size = 0;
	for (size_t i = 0; i < size; i++) {
		if (mas[i] && i != 10) {
			res->mas[++res->size - 1].ch = (unsigned char)i;
			res->mas[res->size - 1].freq = 0;
			res->mas[res->size - 1].count = mas[i];
		}
	}
	return res;
}

void print_sym(const Symbol* obj)
{
	printf("%c %f %d\n", (obj->ch), (obj->freq), (obj->count));
}