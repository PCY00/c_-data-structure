
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

	insert(0, make_Namecard("박찬영", 20191546));// 본인 이름, 학번 넣기
	insert(0, make_Namecard("서재연", 20211521));
	insert(1, make_Namecard("김준형", 20211516));
	insert(size(), make_Namecard("서승진", 20211506));
	insert(3, make_Namecard("신서연", 20211501));
	insert(size(), make_Namecard("김지연", 20211530));
	insert(10, make_Namecard("김현수", 20211522));
	print_list("Insert");

	replace(size() - 1, make_Namecard("정현", 20211504));
	replace(4, make_Namecard("채경훈", 20211498));
	replace(20, make_Namecard("허정인", 20211490));
	print_list("Replace");

	l_delete(3);
	l_delete(size() - 1);
	l_delete(0);
	l_delete(30);
	print_list("Delete");

	printf("%s is found at %d\n", "김준형", find(make_Namecard("김준형", 20211516)));
	printf("%s is found at %d\n", "김정우", find(make_Namecard("김정우", 20211526)));
	printf("%s is found at %d\n", "채경훈", find(make_Namecard("채경훈", 20211234)));

	Namecard temp = get_entry(1);
	if (temp.id != -1) {
		printf("\nEntry 1: (%s, %d)\n", temp.name, temp.id);
	}
	/*else {
		printf("\nEntry 4: (%d)\n", temp.id);											//링크에 없을 경우 구조체 id에 -1만 넣어서 리턴해줌
	}*/
	return 0;
}

void init(void) {
	Namecard* p, * removed;
	for (p = head; p != NULL;) {														//p가 NULL까지 모든 연결리스트을 반납
		removed = p;
		p = p->link;
		free(removed);
	}
	head = NULL;																		//초기화, head를 NULL을 가리키게함.
}

int is_emtpy(void) {
	if (head == NULL) return 1;															//공백 검사
	else {
		return 0;
	}
}

void insert(int pos, Namecard item) {
	if (pos < 0 || pos > size()) {														//오류 잡기.
		printf("삽입 위치 오류\n");
		return;
	}
	Namecard* p = (Namecard*)malloc(sizeof(Namecard));
	if (p == NULL) return;																//NULL 역참조 해결해줌.
	strcpy(p->name, item.name);
	p->id = item.id;
	p->link = NULL;
	if (head == NULL || pos == 0) {														//처음 삽입할때 
		p->link = head;																	//p링크가 head를 가리킴.
		head = p;																		//head를 p로 변경.
	}
	else {
		Namecard* pre;																	//링크를 가리켜줄 포인터 생성.
		pre = head;																		//pre이 head를 가리킴.
		int i = 1;																		//i가 1부터 시작하는 이유는 위에서 이미 처음 삽입을 해결 해주었기 때문에 
		while (i < pos) {																//이곳은 pos가 1부터 올 수 밖에 없다.
			pre = pre->link;															//i가 pos 이전 위치 까지 pre를 이동시킴.
			i++;
		}
		p->link = pre->link;															//pre의 링크를 p링크가 가리킴.
		pre->link = p;																	//p를 pre링크가 가리킴. 
	}
}

void l_delete(int pos) {
	if (pos < 0 || pos > size() || head == NULL) {										//오류 잡기.
		printf("삭제 위치 오류\n");
		return;
	}
	Namecard* remove;																	//삭제 포인터 생성.
	if (pos == 0) {																		//첫번째 위치 데이터 삭제할 때
		remove = head;
		head = remove->link;
		free(remove);
	}
	else {
		Namecard* real;																	//삭제시켜줄 포인터 생성.
		int i = 1;
		remove = head;																	//여기서 remove는 삭제 포인터 바로 뒤를 가리켜주는 포인터.
		while (i < pos) {
			remove = remove->link;
			i++;
		}
		real = remove->link;															//삭제할 위치를  real에 저장.
		remove->link = real->link;														//remove링크를 real링크에 연결.
		free(real);																		//real의 역활 끝, 반환.
	}
}

Namecard* getNode(int pos) {
	Namecard* p;
	p = head;
	for (int i = 0; i < pos; i++) {
		if (p == NULL) // 위치 오류(해당 되는 위치의 노드가 없음)
			return NULL; // 호출함수는 없는 위치이므로, 에러 처리하여야 함
		p = p->link;
	}
	return p;
}

Namecard get_entry(int pos) {
	Namecard* p;
	Namecard re;
	if (pos > size() || pos < 0) {														//pos위치에 노드가 없는 경우 id에 -1넣고 반환.
		re.id = -1;
		return re;

	}
	p = head;
	for (int i = 0; i < pos; i++) {														//pos위치까지 p를 이동시킨 후
		p = p->link;
	}
	re.id = p->id;
	strcpy(re.name, p->name);
	return re;																			//복사 후 리턴
}

int find(Namecard item) {
	Namecard* p;
	for (p = head; p != NULL; p = p->link) {											//p를 이용하여 모든 노드에 방문하면서
		if (strcmp(p->name, item.name) == 0 && p->id == item.id) {						//이름, id같은거 찾으면 리턴 0;
			return 0;
		}
	}
	return -1;																			//못찾으면 -1;
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
		printf("교체 위치 오류\n");
		return;
	}
	Namecard* p;
	p = head;
	int i = 1;
	while (i <= pos) {																	//p로 방문하면서 pos 위치까지 감
		p = p->link;
		i++;
	}
	strcpy(p->name, item.name);															//pos위치에서 이름, id만 바꾸어 주면 됨.
	p->id = item.id;
}

int size(void) {
	Namecard* p;
	int i = 0;																			// i가 노드 갯수를 의미.
	p = head;
	while (p != NULL) {																	//NULL에 도착하지 못하면 i 증가, NULL에 도착하면 그만 둠
		p = p->link;
		i++;
	}
	return i;																			//갯수 리턴
}

void print_list(char* msg) {															//프린트 함수
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