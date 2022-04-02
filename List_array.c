#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)
#define MAX_LIST_SIZE 45

typedef struct {
	char name[20];
	int id;
}Namecard;
typedef struct {
	Namecard list[MAX_LIST_SIZE];
	int length;
}List_Type;

List_Type L;

Namecard make_Namecard(char name[], int id);
void init(void);
void insert(int pos, Namecard item);
void l_delete(int pos);
Namecard get_entry(int pos);
int is_empty(void);
int is_full(void);
int find(Namecard item);
void replace(int pos, Namecard item);
int size(void);
void sort_list(void);
void print_list(char* msg);


int main(void) {
	init();
	print_list("Init");
	insert(0, make_Namecard("a1", 00000000));
	insert(0, make_Namecard("a2", 000000001));
	insert(1, make_Namecard("a3", 00000002));
	insert(size(), make_Namecard("a4", 00000003));
	insert(3, make_Namecard("a5", 00000004));
	insert(size(), make_Namecard("a6", 00000005));
	insert(10, make_Namecard("a7", 00000006));
	print_list("Insert");
	replace(size() - 1, make_Namecard("a8", 00000007));
	replace(4, make_Namecard("a9", 00000011));
	replace(20, make_Namecard("a10", 00000012));
	print_list("Replace");
	l_delete(3);
	l_delete(size() - 1);
	l_delete(0);
	l_delete(30);
	print_list("Delete");
	sort_list();
	print_list("Sort");
	printf("%s is found at %d\n", "a3", find(make_Namecard("a3", 00000002)));
	printf("%s is found at %d\n", "a11", find(make_Namecard("a11", 00000010)));
	printf("%s is found at %d\n", "a12", find(make_Namecard("a12", 00000011)));
	return 0;
}

Namecard make_Namecard(char name[], int id) {
	Namecard newCard;

	strcpy(newCard.name, name);
	newCard.id = id;

	return newCard;
}

void init(void) {
	L.length = 0;
}

void insert(int pos, Namecard item) {
	int i;
	if (is_full() == 0 && pos >= 0 && pos <= L.length) {
		for (i = L.length; i > pos; i--) {
			L.list[i] = L.list[i - 1];
		}
		L.list[pos] = item;
		L.length++;
	}
	else {
		printf("포화상태 오류 또는 삽입 위치 오류\n");
	}
}

void l_delete(int pos) {
	int i;
	if (is_empty() == 0 && pos >= 0 && pos < L.length) {
		for (i = pos; i < L.length - 1; i++) {
			L.list[i] = L.list[i + 1];
		}
		L.length--;
	}
	else {
		printf("공백상태 오류 또는 삭제 위치 오류\n");
	}
}

Namecard get_entry(int pos) {
	if (pos <= L.length && pos > 0) {
		return L.list[pos];
	}
	else {
		printf("에러\n");
	}
}

int is_empty(void) {
	if (L.length == 0) return 1;
	else {
		return 0;
	}
}

int is_full(void) {
	if (L.length == MAX_LIST_SIZE) return 1;
	else {
		return 0;
	}
}

int find(Namecard item) {
	for (int i = 0; i < L.length; i++) {
		if (L.list[i].id == item.id && strcmp(L.list[i].name, item.name) == 0) {
			return i;
		}
	}
	return -1;
}

void replace(int pos, Namecard item) {
	if (pos >= 0 && pos < L.length) {
		L.list[pos] = item;
	}
	else {
		printf("교체 위치 오류\n");
	}
}

int size(void) {
	return L.length;
}

void sort_list(void) {
	Namecard temp;
	for (int i = 0; i < L.length; i++) {
		for (int j = 0; j < L.length; j++) {
			if (L.list[i].id < L.list[j].id) {
				temp = L.list[i];
				L.list[i] = L.list[j];
				L.list[j] = temp;
			}
		}
	}
}

void print_list(char* msg) {
	if (msg) {
		printf("%s: ", msg);
		if (msg == "Init") printf("\n");
	}
	for (int i = 0; i < L.length; i++) {
		printf(" (%s , %d) ", L.list[i].name, L.list[i].id);
		if (i == L.length - 1) {
			printf("\n");
		}
	}
	printf("\n");
}
