
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
	int data;
	struct Node* next;
} Node;
//Node* head;
//Node* tail;
//int count;

typedef struct List {
	Node* head, * tail;
	int count;
} List;

int listInitialize(List *list) {
	if (list == NULL) {
		fprintf(stderr, "listInitialize: argument is null\n");
		return -1;
	}

	Node *head = malloc(sizeof(Node));
	if (head == NULL) {
		perror("listInitialize");
		return -1;
	}

	Node *tail = malloc(sizeof(Node));
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

	return 0;
}

int listFinalize(List *list) {
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
		free(target);
	}

	free(head);
	free(tail);
	return 0;
}

int listAdd(List *list, int data) {
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

void listDisplay(const List *list) {
	if (list == NULL) {
		fprintf(stderr, "listDisplay: argument is null\n");
		return;
	}
	Node* head = list->head;
	Node* tail = list->tail;

	system("cls");
	printf("[head]");
	for (Node* node = head->next; node != tail; node = node->next)
		printf("->[%2d]", node->data);
	printf("->[tail]");
	getchar();
}

int listSet(List *list, int index, int newData, int* oldData) {
	if (list == NULL) {
		fprintf(stderr, "listSet: argument is null\n");
		return -1;
	}

	if (list->count == 0) {
		fprintf(stderr, "listSet: list is empty\n");
		return -1;
	}

	if (oldData == NULL) {
		fprintf(stderr, "listSet: argument is null\n");
		return -1;
	}

	if (index < 0 || index >= list->count) {
		fprintf(stderr, "listSet: out of index\n");
		return -1;
	}
	Node* head = list->head;

	Node* node = head->next;
	for (int i = 0; i < index; i++)
		node = node->next;

	*oldData = node->data;
	node->data = newData;
	return 0;
}

int listCount(const List *list) {
	if (list == NULL) {
		fprintf(stderr, "listCount: argument is null\n");
		return -1;
	}
	return list->count;
}

int listInsert(List *list, int index, int newData) {
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

int listGet(List *list, int index, int* outData) {
	if (list == NULL) {
		fprintf(stderr, "listGet: argument is null\n");
		return -1;
	}

	if (list->count == 0) {
		fprintf(stderr, "listGet: list is empty\n");
		return -1;
	}

	if (outData == NULL) {
		fprintf(stderr, "listGet: argument is null\n");
		return -1;
	}

	if (index < 0 || index >= list->count) {
		fprintf(stderr, "listGet: out of index\n");
		return -1;
	}

	Node* head = list->head;
	Node* node = head->next;
	for (int i = 0; i < index; i++)
		node = node->next;
	*outData = node->data;
	return 0;
}

int listRemove(List *list, int index, int* outData) {
	if (list == NULL) {
		fprintf(stderr, "listRemove: argument is null\n");
		return -1;
	}

	if (list->count == 0) {
		fprintf(stderr, "listRemove: list is empty\n");
		return -1;
	}

	if (outData == NULL) {
		fprintf(stderr, "listRemove: argument is null\n");
		return -1;
	}

	if (index < 0 || index >= list->count) {
		fprintf(stderr, "listRemove: out of index\n");
		return -1;
	}

	Node* head = list->head;
	Node* prev = head;
	for (int i = 0; i < index; i++)
		prev = prev->next;

	Node* target = prev->next;
	prev->next = target->next;
	*outData = target->data;
	free(target);
	--list->count;
	return 0;
}

int main() {
	List list;
	listInitialize(&list);

	for (int i = 0; i < 5; i++)
		listAdd(&list, i + 1);
	listDisplay(&list);

	int data;
	listRemove(&list, 4, &data), listDisplay(&list);
	listRemove(&list, 2, &data), listDisplay(&list);
	listRemove(&list, 0, &data), listDisplay(&list);


	listFinalize(&list);
	return 0;
}