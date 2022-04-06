#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int coef;
	int expon;
	struct List* link;
}List;

typedef struct {
	int size;
	List* head;
	List* tail;
}Type;

void error(char* message);
Type* create();
void insert_last(Type* a, int c, int e);
void poly_print(Type* a);
void add(Type* a, Type* b, Type* c);

int main(void) {
	Type* A, * B, * C;
	A = create();
	B = create();
	C = create();

	insert_last(A, 3, 6);
	insert_last(A, 7, 3);
	insert_last(A, -2, 2);
	insert_last(A, -9, 0);
	insert_last(B, -2, 6);
	insert_last(B, -4, 4);
	insert_last(B, 6, 2);
	insert_last(B, 6, 1);
	insert_last(B, 1, 0);

	poly_print(A);
	poly_print(B);

	add(A, B, C);
	poly_print(C);

	free(A);
	free(B);
	free(C);

	return 0;
}

void error(const char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

Type* create() {
	Type* a = (Type*)malloc(sizeof(Type));
	if (a == NULL) return;
	a->size = 0;
	a->head = a->tail = NULL;
	return a;
}

void insert_last(Type* a, int c, int e) {
	List* b = (List*)malloc(sizeof(List));
	if (b == NULL) error("메모리 할당 오류");
	b->coef = c;
	b->expon = e;
	b->link = NULL;

	if (a->tail == NULL) {
		a->head = a->tail = b;
	}
	else {
		a->tail->link = b;
		a->tail = b;
	}
	a->size++;
}

void poly_print(Type* a) {
	List* b = a->head;

	printf("polynomial = ");
	for (; b; b = b->link) {
		printf("%dx^%d", b->coef, b->expon);
		if (b->link != NULL) {
			printf(" + ");
		}
	}
	printf("\n");
}

void add(Type* a, Type* b, Type* c) {
	List* p = a->head;
	List* q = b->head;
	int sum;

	while (p && q) {
		if (p->expon == q->expon) {
			sum = p->coef + q->coef;
			if (sum != 0) {
				insert_last(c, sum, p->expon);
			}
			p = p->link;
			q = q->link;
		}
		else if (p->expon > q->expon) {
			insert_last(c, p->coef, p->expon);
			p = p->link;
		}
		else {
			insert_last(c, q->coef, q->expon);
			q = q->link;
		}
	}
	for (; p != NULL; p = p->link) {
		insert_last(c, p->coef, p->expon);
	}
	for (; q != NULL; q = q->link) {
		insert_last(c, q->coef, q->expon);
	}
}