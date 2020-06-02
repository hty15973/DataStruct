
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
	int data;
	struct Node* next;
} Node;
Node* head;
Node* tail;
int count;

int listInitialize() {
	head = malloc(sizeof(Node));
	if (head == NULL) {
		perror("listInitialize");
		return -1;
	}

	tail = malloc(sizeof(Node));
	if (tail == NULL) {
		perror("listInitialize");
		free(head);
		return -1;
	}
	head->next = tail;
	tail->next = tail;
	count = 0;

	return 0;
}

int listFinalize() {
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

int listAdd(int data) {
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
	count++;
	return 0;
}

void listDisplay() {
	system("cls");
	printf("[head]");
	for (Node* node = head->next; node != tail; node = node->next)
		printf("->[%2d]", node->data);
	printf("->[tail]");
	getchar();
}

int listSet(int index, int newData, int* oldData) {
	if (count == 0) {
		fprintf(stderr, "listSet: list is empty\n");
		return -1;
	}

	if (oldData == NULL) {
		fprintf(stderr, "listSet: argument is null\n");
		return -1;
	}

	if (index < 0 || index >= count) {
		fprintf(stderr, "listSet: out of index\n");
		return -1;
	}

	Node* node = head->next;
	for (int i = 0; i < index; i++)
		node = node->next;

	*oldData = node->data;
	node->data = newData;
	return 0;
}

int listCount() {
	return count;
}

int listInsert(int index, int newData) {
	if (count == 0) {
		fprintf(stderr, "listInsert: list is empty\n");
		return -1;
	}

	if (index < 0 || index >= count) {
		fprintf(stderr, "listInsert: out of index\n");
		return -1;
	}
	
	Node* node = malloc(sizeof(Node));
	if (node == NULL) {
		perror("listInsert");
		return -1;
	}
	node->data = newData;

	Node* prev = head;
	for (int i = 0; i < index; i++)
		prev = prev->next;

	node->next = prev->next;
	prev->next = node;
	++count;
	return 0;
}

int main() {
	listInitialize();
	for (int i = 0; i < 5; i++)
		listAdd(i + 1);
	listDisplay();	// 1 2 3 4 5

	listInsert(4, 10), listDisplay();
	listInsert(2, 10), listDisplay();
	listInsert(0, 10), listDisplay();

	listFinalize();
	return 0;
}