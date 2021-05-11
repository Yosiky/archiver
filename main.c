
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
	double H = 0;
	for (size_t i = 0; i < p->size; i++) {
		H += p->mas[i].freq * log(p->mas[i].freq) / log(2);
	}
	return (-1)* H;
}

void sortTree(Tree** mas, const size_t size) {
	for (size_t i = 0; i < size - 1; ++i) {
		for (size_t j = i + 1; j < size; ++j) {
			if (mas[i]->obj.freq < mas[j]->obj.freq) {
				Tree* a = mas[i];
				mas[i] = mas[j];
				mas[j] = a;
			}
		}
	}
}

Tree* creatTree(Pair const * const  mas) {
	printf("Begin creat\n");
	Tree** mass = (Tree**)malloc(sizeof(Tree*) * mas->size);
	size_t size = mas->size;
	for (size_t i = 0; i < size; ++i) {
		mass[i] = (Tree*)malloc(sizeof(Tree));
		mass[i]->obj = mas->mas[i];
		mass[i]->next_left = 0;
		mass[i]->next_right = 0;
	}
	for (size_t i = size - 1; i > 0; --i) {
		Tree* elem = (Tree*)malloc(sizeof(Tree));
		elem->next_left = mass[i - 1];
		elem->next_right = mass[i];
		elem->obj.freq = mass[i - 1]->obj.freq + mass[i]->obj.freq;
		mass[i - 1] = elem;
		if (i > 1)
			sortTree(mass, i - 1);
	}
	printf("End creat\n");
	return mass[0];
}

void printTree(Tree* head) {
	if (!head->next_left && !head->next_right) {
		print_sym(&head->obj);
		printf("%s", head->word);
		return;
	}
	if (head->next_left && head->next_right) {
		head->next_left->word = (char*)malloc(sizeof(char)*(head->size + 2));
		head->next_right->word = (char*)malloc(sizeof(char)*(head->size + 2));
		strcpy(head->next_left->word, head->word);
		strcpy(head->next_right->word, head->word);
		head->next_left->word[head->size] = '0';
		head->next_left->word[head->size + 1] = (char)0;	
		head->next_right->word[head->size] = '1';
		head->next_right->word[head->size + 1] = (char)0;
		head->next_left->size = head->size + 1;
		head->next_right->size = head->size + 1;
	
		printTree(head->next_left);
		printTree(head->next_right);
	}
	return;
}

int main() {
	FILE* file = file_open();
	Pair* value = input(file);
	sort(value);
	printf("SORT:\n");
	print_pair(value);
	printf("Entropy = %lf\n", entropy(value));
	printf("Tree\n");
	Tree* res = creatTree(value);
	res->size = 0;
	res->next_left->word = (char*)malloc(sizeof(char));
	res->next_left->word = '0';
	res->next_left->size = 1;
	res->next_right->word = (char*)malloc(sizeof(char));
	res->next_right->size = 1;
	res->next_right->word = '1';
	printf("Print Tree\n");
	printTree(res);
	free(value->mas);
	free(value);
	fclose(file);
	return 0;
}
