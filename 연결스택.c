#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct StackNode {
	element data;
	struct StackNode* link;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedStackType;

// 초기화 함수
void init_stack(LinkedStackType* s) {
	s->top = NULL;
}

// 공백 상태 검출 함수
int is_empty(LinkedStackType* s) {
	return (s->top == NULL);
}

// 삽입 함수 (제일 앞에 노드 삽입)
void push(LinkedStackType* s, element item) {
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}

// 삭제 함수 (첫 번째 노드 삭제하고 데이터를 반환)
element pop(LinkedStackType* s) {
	if(is_empty(s)) {
		fprintf(stderr,"스택이 비어있음\n");
			exit(1);
	}
	else{
		StackNode* temp = s->top;
		int data = temp->data;
		s->top = s->top->link;
		free(temp);
		return data;
	}
}

// 피크 함수
element peek(LinkedStackType* s) {
	if(is_empty(s)) {
		fprintf(stderr,"스택이 비어있음\n");
			exit(1);
	}
	else{
		return s->top->data;
	}
}

void printStack(LinkedStackType* s) {
	for (StackNode* p = s->top; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL \n");
}
int main() {
	LinkedStackType s;
	init_stack(&s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);
	printStack(&s);
	printf("pop\t=> %d\t", pop(&s));
	printStack(&s);
	printf("peek\t=> %d\t", peek(&s));
	printStack(&s);
	printf("pop\t=> %d\t", pop(&s));
	printStack(&s);
	printf("pop\t=> %d\t", pop(&s));
	printStack(&s);
}