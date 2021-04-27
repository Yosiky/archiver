#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "test.h"
#include "file_work.h"
#include "math.h"
Pair* input(FILE* file)
{
	size_t* mas = file_read(file);
	/*
	printf("Massive: \n");
	for (size_t i = 0; i < MAX_SIZE_STR; i++)
		printf("%c = %ld\n", (char)i, mas[i]);
	printf("End massive\n");
	*/	
	Pair* res = processing(mas, MAX_SIZE_STR);
	free(mas);
	return res;
}

void print_pair(const Pair* obj) 
{
	printf("%ld\n", obj->count);
	for (size_t i = 0; i < obj->size; i++) {
		print_sym(&(obj->mas[i]));
	}
}

void sort(Pair* p) {
	for (size_t i = 0; i < p->size - 1; i++) {
		for (size_t j = i + 1; j < p->size; j++) {
			if (p->mas[i].freq < p->mas[j].freq) {
				Symbol v = p->mas[i];
				p->mas[i] = p->mas[j];
				p->mas[j] = v;
			}
		}
	}

}

double entropy(Pair* p) {
	double R = 0;
	for (size_t i = 0; i < p->size; i++) {
		R += p->mas[i].freq * log(p->mas[i].freq, 2);
	}
	return (-1)* R;
}

int main() 
{
	FILE* file = file_open();
	Pair* value = input(file);
	print_pair(value);
	sort(value);
	printf("SORT:\n");
	print_pair(value);
	printf("Entropy = %f\n", entropy(value));
	free(value->mas);
	free(value);
	fclose(file);
	return 0;
}
