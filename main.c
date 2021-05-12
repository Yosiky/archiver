#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "test.h"
#include "file_work.h"
#include "math.h"
#include "string.h"

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
			if (p->mas[i].freq == p->mas[j].freq && p->mas[i].ch > p->mas[j].ch) {
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

double cost_past(const Pair* p) {
	double R = 0;
	for (size_t i = 0; i < p->size; i++) {
		R += p->mas[i].freq * 8;
	}
	return R;
}

double cost_new(const Pair* p) {
	double R = 0;
	for (size_t i = 0; i < p->size; i++) {
		R += p->mas[i].freq * p->mas[i].size;
	}
	return R;
}

void sortTree(Tree** mas, const size_t size) {
	for (size_t i = 0; i < size - 1; ++i) {
		for (size_t j = i + 1; j < size; ++j) {
			if (mas[i]->obj->freq < mas[j]->obj->freq) {
				Tree* a = mas[i];
				mas[i] = mas[j];
				mas[j] = a;
			}
			if (mas[i]->obj->freq == mas[j]->obj->freq && strcmp(mas[i]->obj->ch, mas[j]->obj->ch) > 0) {
				Tree* a = mas[i];
				mas[i] = mas[j];
				mas[j] = a;
			}
		}
	}
}

void print_tree(Tree** mas, const size_t size) {
	printf("Size : %d\n", size);
	for (size_t i = 0; i < size; i++) {
		print_sym(mas[i]->obj);
	}
	printf("\n");
}

Tree* creatTree(Pair const * const  mas) {
	printf("Begin creat\n");
	Tree** mass = (Tree**)malloc(sizeof(Tree*) * mas->size);
	size_t size = mas->size;
	for (size_t i = 0; i < size; ++i) {
		mass[i] = (Tree*)malloc(sizeof(Tree));
		mass[i]->obj = mas->mas + i;
		mass[i]->next_left = 0;
		mass[i]->next_right = 0;
	}
	for (size_t i = size - 1; i > 0; --i) {
		Tree* elem = (Tree*)malloc(sizeof(Tree));
		elem->obj = (Symbol*)malloc(sizeof(Symbol));
		elem->obj->ch = (char*)malloc(sizeof(char)*(strlen(mass[i - 1]->obj->ch) + strlen(mass[i]->obj->ch) + 1));
		strcpy(elem->obj->ch, mass[i - 1]->obj->ch);
		strcpy(elem->obj->ch + strlen(mass[i - 1]->obj->ch), mass[i]->obj->ch);
		elem->obj->ch[strlen(mass[i - 1]->obj->ch) + strlen(mass[i]->obj->ch)] = '\0';
		elem->next_left = mass[i - 1];
		elem->next_right = mass[i];
		elem->obj->freq = mass[i - 1]->obj->freq + mass[i]->obj->freq;
		mass[i - 1] = elem;
		if (i > 1)
			sortTree(mass, i);
	}
	printf("End creat\n");
	return mass[0];
}



void printTree(Tree* head) {
	if (head->next_left && head->next_right) {
		head->next_left->obj->word = (char*)malloc(sizeof(char)*(head->obj->size + 2));
		head->next_right->obj->word = (char*)malloc(sizeof(char)*(head->obj->size + 2));
		strcpy(head->next_left->obj->word, head->obj->word);
		strcpy(head->next_right->obj->word, head->obj->word);
		head->next_left->obj->word[head->obj->size] = '0';
		head->next_left->obj->word[head->obj->size + 1] = (char)0;	
		head->next_right->obj->word[head->obj->size] = '1';
		head->next_right->obj->word[head->obj->size + 1] = (char)0;
		head->next_left->obj->size = head->obj->size + 1;
		head->next_right->obj->size = head->obj->size + 1;
		//printf("left : %s\nright : %s\n", head->next_left->word, head->next_right->word);
		printTree(head->next_left);
		printTree(head->next_right);
	}	
}

int main() {
	FILE* file = file_open();
	Pair* value = input(file);
	sort(value);
	printf("SORT:\n");
	print_pair(value);
	printf("Entropy = %lf\n", entropy(value));
	printf("Cost past = %lf\n", cost_past(value));
	printf("Tree\n");
	Tree* res = creatTree(value);
	res->obj->size = 0;
	res->obj->word = (char*)malloc(sizeof(char));
	*res->obj->word = '\0';
	printTree(res);
	printf("Cost new = %lf\n", cost_new(value));
	printf("Print Pair :\n");
	print_pair(value);
	free(value->mas);
	free(value);
	fclose(file);
	return 0;
}
