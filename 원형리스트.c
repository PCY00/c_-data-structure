#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_list();

typedef struct node {
	int bomb;
	struct node* link;
}Node;

Node* CL = NULL;

int main(void) {
	Node* p, * New, * mid;

	New = (Node*)malloc(sizeof(Node));
	New->bomb = rand() % 2;
	New->link = NULL;
	CL = New;

	New = (Node*)malloc(sizeof(Node));
	New->bomb = rand() % 2;
	New->link = NULL;
	p = CL;
	p->link = New;

	New = (Node*)malloc(sizeof(Node));
	New->bomb = rand() % 2;
	New->link = NULL;
	p = p->link;
	p->link = New;
	New->link = CL;

	print_list();

	New = (Node*)malloc(sizeof(Node));
	New->bomb = rand() % 2;
	New->link = NULL;
	p = p->link;
	p->link = New;

	New = (Node*)malloc(sizeof(Node));
	New->bomb = rand() % 2;
	New->link = NULL;
	p = p->link;
	p->link = New;
	New->link = CL;
	CL = New;

	print_list();

	mid = p;

	int bombCount = 0;
	do {
		if (p->bomb == 1) {
			bombCount++;
		}
		p = p->link;
	} while (p != mid);
	printf("Bomb Count is %d!!!\n\n", bombCount);

	Node* del;
	p = CL;
	while (p != CL) {
		p = p->link;
	}
	del = p->link;
	p->link = del->link;
	CL = p;
	free(del);

	print_list();
}

void print_list() {
	Node* p;
	p = CL;
	printf("( ");
	if (CL != NULL) {
		do {
			printf("%d ", p->bomb); 
			p = p->link; 
		} while (p != CL); 
	}
	printf(")\n\n");
}