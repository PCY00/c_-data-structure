#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int bomb; 
	struct node* llink;
	struct node* rlink;
} Node;

Node* DL = NULL;

void print_list() {
	Node* p;
	p = DL;
	printf("( ");
	while (p != NULL) {
		printf("%d ", p->bomb);
		p = p->rlink;
	}
	printf(")\n\n");
}

int main() {
	Node* p, * New;
	New = (Node*)malloc(sizeof(Node));
	New->bomb = rand() % 2;;
	New->llink = NULL;
	New->rlink = NULL;

	DL = New;

	New = (Node*)malloc(sizeof(Node));
	New->bomb = rand() % 2;;
	New->llink = NULL;
	New->rlink = NULL;

	
	p = DL; 
	p->rlink = New;
	p->rlink->llink = p;


	New = (Node*)malloc(sizeof(Node));
	New->bomb = rand() % 2;;
	New->llink = NULL;
	New->rlink = NULL;
	p = DL; 
	New->rlink = p;
	New->rlink->llink = New;
	DL = New;
	p = DL;

	
	New = (Node*)malloc(sizeof(Node));
	New->bomb = rand() % 2;;
	New->llink = NULL;
	New->rlink = NULL;
	p = p->rlink->rlink;
	p->rlink = New;
	p->rlink->llink = p;
	p = DL;

	print_list();

	p = DL;
	while (p->rlink != NULL) { 
		p = p->rlink;
	}
	int bombCount = 0;
	while (p != NULL) { 
		if (p->bomb == 1) {
			bombCount++;
		}
		p = p->llink;
	}
	printf("Bomb Count is %d!!!\n\n", bombCount);
}