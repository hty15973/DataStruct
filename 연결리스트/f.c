#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

// 이전 자료구조는 연결 리스트 안에 저장된 데이터의 정보를 알 수 없습니다. 때문에
// 내부적으로 동적 할당된 자원이 있을 경우, 메모리 누수가 발생할 수 있습니다.
// 이를 해결하기 위해 저장된 데이터를 사용자에게 전달하여 사용자가 자원을 해제하도록
// 코드를 변경합니다.

// 자원 해제를 위한 콜백 함수 타입을 선언합니다.
typedef void(FreeFunction)(void* ptr);

typedef struct Node {
	void* data;
	struct Node* next;
} Node;

typedef struct List {
	Node* head, * tail;
	int count;
	FreeFunction* freeFn;
} List;

int listInitialize(List* list, FreeFunction fn) {
	if (list == NULL) {
		fprintf(stderr, "listInitialize: argument is null\n");
		return -1;
	}

	Node* head = malloc(sizeof(Node));
	if (head == NULL) {
		perror("listInitialize");
		return -1;
	}

	Node* tail = malloc(sizeof(Node));
	if (tail == NULL) {
		perror("listInitialize");
		free(head);
		return -1;
	}

	head->next = tail;
	tail->next = tail;

	list->head = head;
	list->tail = tail;
	list->count = 0;
	list->freeFn = fn;

	return 0;
}

int listFinalize(List* list) {
	if (list == NULL) {
		fprintf(stderr, "listFinalize: argument is null\n");
		return -1;
	}

	Node* head = list->head;
	Node* tail = list->tail;

	if (head == NULL || tail == NULL) {
		fprintf(stderr, "listFinalize: list is wrong\n");
		return -1;
	}

	while (head->next != tail) {
		Node* target = head->next;
		head->next = target->next;

		if (list->freeFn)
			list->freeFn(target);

		free(target);
	}

	free(head);
	free(tail);
	return 0;
}

int listAdd(List* list, void* data) {
	if (list == NULL) {
		fprintf(stderr, "listAdd: argument is null\n");
		return -1;
	}

	Node* head = list->head;
	Node* tail = list->tail;

	Node* node = malloc(sizeof(Node));
	if (node == NULL) {
		perror("listAdd");
		return -1;
	}
	node->data = data;
	node->next = tail;

	Node* cur = head;
	while (cur->next != tail)
		cur = cur->next;
	cur->next = node;
	list->count++;
	return 0;
}

void listDisplay(const List* list, const char* (toString)(const void*)) {
	if (list == NULL || toString == NULL) {
		fprintf(stderr, "listDisplay: argument is null\n");
		return;
	}
	Node* head = list->head;
	Node* tail = list->tail;

	system("cls");
	printf("[head]");
	for (Node* node = head->next; node != tail; node = node->next)
		printf("->[%s]", toString(node->data));
	printf("->[tail]");
	getchar();
}

void* listSet(List* list, int index, void* newData) {
	if (list == NULL) {
		fprintf(stderr, "listSet: argument is null\n");
		return NULL;
	}

	if (list->count == 0) {
		fprintf(stderr, "listSet: list is empty\n");
		return NULL;
	}

	if (index < 0 || index >= list->count) {
		fprintf(stderr, "listSet: out of index\n");
		return NULL;
	}
	Node* head = list->head;

	Node* node = head->next;
	for (int i = 0; i < index; i++)
		node = node->next;

	void* oldData = node->data;
	node->data = newData;
	return oldData;
}

int listCount(const List* list) {
	if (list == NULL) {
		fprintf(stderr, "listCount: argument is null\n");
		return -1;
	}
	return list->count;
}

int listInsert(List* list, int index, void* newData) {
	if (list == NULL) {
		fprintf(stderr, "listInsert: argument is null\n");
		return -1;
	}

	if (list->count == 0) {
		fprintf(stderr, "listInsert: list is empty\n");
		return -1;
	}

	if (index < 0 || index >= list->count) {
		fprintf(stderr, "listInsert: out of index\n");
		return -1;
	}

	Node* node = malloc(sizeof(Node));
	if (node == NULL) {
		perror("listInsert");
		return -1;
	}
	node->data = newData;

	Node* head = list->head;
	Node* prev = head;
	for (int i = 0; i < index; i++)
		prev = prev->next;

	node->next = prev->next;
	prev->next = node;
	++list->count;
	return 0;
}

void* listGet(List* list, int index) {
	if (list == NULL) {
		fprintf(stderr, "listGet: argument is null\n");
		return NULL;
	}

	if (list->count == 0) {
		fprintf(stderr, "listGet: list is empty\n");
		return NULL;
	}

	if (index < 0 || index >= list->count) {
		fprintf(stderr, "listGet: out of index\n");
		return NULL;
	}

	Node* head = list->head;
	Node* node = head->next;
	for (int i = 0; i < index; i++)
		node = node->next;
	return node->data;
}

void* listRemove(List* list, int index) {
	if (list == NULL) {
		fprintf(stderr, "listRemove: argument is null\n");
		return NULL;
	}

	if (list->count == 0) {
		fprintf(stderr, "listRemove: list is empty\n");
		return NULL;
	}

	if (index < 0 || index >= list->count) {
		fprintf(stderr, "listRemove: out of index\n");
		return NULL;
	}

	Node* head = list->head;
	Node* prev = head;
	for (int i = 0; i < index; i++)
		prev = prev->next;

	Node* target = prev->next;
	prev->next = target->next;
	void* outData = target->data;
	free(target);
	--list->count;
	return outData;
}

// 위의 코드는 라이브러리 설계자가 제공하는 코드입니다.
//------------------------------------------------------------------
// 아래의 코드는 사용자가 구현하는 코드입니다.
typedef struct {
	char name[32];	// char *name;
	int age;
} Person;

const char* toString(const void* ptr) {
	const Person* person = ptr;

	static char buf[32];
	sprintf(buf, "%s(%d)", person->name, person->age);
	return (const char*)buf;
}

//void FreePerson(void* ptr) {
//	Person* p = ptr;
//	free(p->name);
//}

int main() {
	Person people[4] = {
		{"susan", 20}, {"eddy", 30}, {"rupy", 40}, {"petty", 50}
	};

	List list;
	listInitialize(&list, NULL);

	for (int i = 0; i < 3; i++)
		listAdd(&list, people + i);
	listDisplay(&list, toString);

	listInsert(&list, 0, people + 3), listDisplay(&list, toString);

	Person* person = listRemove(&list, 0);
	listDisplay(&list, toString);

	listFinalize(&list);
	return 0;
}