
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct name_card {
	char name[20];
	int id;
	struct name_card* link;
}Namecard;

Namecard* head = NULL;

void init(void);
int is_emtpy(void);
void insert(int pos, Namecard item);
void l_delete(int pos);
Namecard* getNode(int pos);
Namecard get_entry(int pos);
int find(Namecard item);
Namecard make_Namecard(char name[], int id);
void replace(int pos, Namecard item);
int size(void);
void print_list(char* msg);

int main(void) {
	init();
	print_list("Init");

	insert(0, make_Namecard("������", 20191546));// ���� �̸�, �й� �ֱ�
	insert(0, make_Namecard("���翬", 20211521));
	insert(1, make_Namecard("������", 20211516));
	insert(size(), make_Namecard("������", 20211506));
	insert(3, make_Namecard("�ż���", 20211501));
	insert(size(), make_Namecard("������", 20211530));
	insert(10, make_Namecard("������", 20211522));
	print_list("Insert");

	replace(size() - 1, make_Namecard("����", 20211504));
	replace(4, make_Namecard("ä����", 20211498));
	replace(20, make_Namecard("������", 20211490));
	print_list("Replace");

	l_delete(3);
	l_delete(size() - 1);
	l_delete(0);
	l_delete(30);
	print_list("Delete");

	printf("%s is found at %d\n", "������", find(make_Namecard("������", 20211516)));
	printf("%s is found at %d\n", "������", find(make_Namecard("������", 20211526)));
	printf("%s is found at %d\n", "ä����", find(make_Namecard("ä����", 20211234)));

	Namecard temp = get_entry(1);
	if (temp.id != -1) {
		printf("\nEntry 1: (%s, %d)\n", temp.name, temp.id);
	}
	/*else {
		printf("\nEntry 4: (%d)\n", temp.id);											//��ũ�� ���� ��� ����ü id�� -1�� �־ ��������
	}*/
	return 0;
}

void init(void) {
	Namecard* p, * removed;
	for (p = head; p != NULL;) {														//p�� NULL���� ��� ���Ḯ��Ʈ�� �ݳ�
		removed = p;
		p = p->link;
		free(removed);
	}
	head = NULL;																		//�ʱ�ȭ, head�� NULL�� ����Ű����.
}

int is_emtpy(void) {
	if (head == NULL) return 1;															//���� �˻�
	else {
		return 0;
	}
}

void insert(int pos, Namecard item) {
	if (pos < 0 || pos > size()) {														//���� ���.
		printf("���� ��ġ ����\n");
		return;
	}
	Namecard* p = (Namecard*)malloc(sizeof(Namecard));
	if (p == NULL) return;																//NULL ������ �ذ�����.
	strcpy(p->name, item.name);
	p->id = item.id;
	p->link = NULL;
	if (head == NULL || pos == 0) {														//ó�� �����Ҷ� 
		p->link = head;																	//p��ũ�� head�� ����Ŵ.
		head = p;																		//head�� p�� ����.
	}
	else {
		Namecard* pre;																	//��ũ�� �������� ������ ����.
		pre = head;																		//pre�� head�� ����Ŵ.
		int i = 1;																		//i�� 1���� �����ϴ� ������ ������ �̹� ó�� ������ �ذ� ���־��� ������ 
		while (i < pos) {																//�̰��� pos�� 1���� �� �� �ۿ� ����.
			pre = pre->link;															//i�� pos ���� ��ġ ���� pre�� �̵���Ŵ.
			i++;
		}
		p->link = pre->link;															//pre�� ��ũ�� p��ũ�� ����Ŵ.
		pre->link = p;																	//p�� pre��ũ�� ����Ŵ. 
	}
}

void l_delete(int pos) {
	if (pos < 0 || pos > size() || head == NULL) {										//���� ���.
		printf("���� ��ġ ����\n");
		return;
	}
	Namecard* remove;																	//���� ������ ����.
	if (pos == 0) {																		//ù��° ��ġ ������ ������ ��
		remove = head;
		head = remove->link;
		free(remove);
	}
	else {
		Namecard* real;																	//���������� ������ ����.
		int i = 1;
		remove = head;																	//���⼭ remove�� ���� ������ �ٷ� �ڸ� �������ִ� ������.
		while (i < pos) {
			remove = remove->link;
			i++;
		}
		real = remove->link;															//������ ��ġ��  real�� ����.
		remove->link = real->link;														//remove��ũ�� real��ũ�� ����.
		free(real);																		//real�� ��Ȱ ��, ��ȯ.
	}
}

Namecard* getNode(int pos) {
	Namecard* p;
	p = head;
	for (int i = 0; i < pos; i++) {
		if (p == NULL) // ��ġ ����(�ش� �Ǵ� ��ġ�� ��尡 ����)
			return NULL; // ȣ���Լ��� ���� ��ġ�̹Ƿ�, ���� ó���Ͽ��� ��
		p = p->link;
	}
	return p;
}

Namecard get_entry(int pos) {
	Namecard* p;
	Namecard re;
	if (pos > size() || pos < 0) {														//pos��ġ�� ��尡 ���� ��� id�� -1�ְ� ��ȯ.
		re.id = -1;
		return re;

	}
	p = head;
	for (int i = 0; i < pos; i++) {														//pos��ġ���� p�� �̵���Ų ��
		p = p->link;
	}
	re.id = p->id;
	strcpy(re.name, p->name);
	return re;																			//���� �� ����
}

int find(Namecard item) {
	Namecard* p;
	for (p = head; p != NULL; p = p->link) {											//p�� �̿��Ͽ� ��� ��忡 �湮�ϸ鼭
		if (strcmp(p->name, item.name) == 0 && p->id == item.id) {						//�̸�, id������ ã���� ���� 0;
			return 0;
		}
	}
	return -1;																			//��ã���� -1;
}

Namecard make_Namecard(char name[], int id) {
	Namecard newCard;

	strcpy(newCard.name, name);
	newCard.id = id;
	newCard.link = NULL;

	return newCard;
}

void replace(int pos, Namecard item) {
	if (pos < 0 || pos > size()) {
		printf("��ü ��ġ ����\n");
		return;
	}
	Namecard* p;
	p = head;
	int i = 1;
	while (i <= pos) {																	//p�� �湮�ϸ鼭 pos ��ġ���� ��
		p = p->link;
		i++;
	}
	strcpy(p->name, item.name);															//pos��ġ���� �̸�, id�� �ٲپ� �ָ� ��.
	p->id = item.id;
}

int size(void) {
	Namecard* p;
	int i = 0;																			// i�� ��� ������ �ǹ�.
	p = head;
	while (p != NULL) {																	//NULL�� �������� ���ϸ� i ����, NULL�� �����ϸ� �׸� ��
		p = p->link;
		i++;
	}
	return i;																			//���� ����
}

void print_list(char* msg) {															//����Ʈ �Լ�
	Namecard* p = (Namecard*)malloc(sizeof(Namecard));
	if (msg) {
		printf("%s: ", msg);
		if (msg == "Init") printf("\n");
	}
	for (p = head; p != NULL; p = p->link) {
		printf(" (%s , %d) ", p->name, p->id);
		if (p->link == NULL) {
			printf("\n");
		}
	}
	printf("\n");
}