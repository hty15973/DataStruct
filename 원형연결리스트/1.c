#include <stdlib.h>
#include <stdio.h>

// 이전 자료구조는 자원 해제가 정상적으로 되지 않는다는 문제가 있고 또 다른 문제는
// 역방향을 순방향으로 변경했을 때, 역시나 정상적으로 동작하지 않는다는 문제가 있습니다.

// 이를 해결하기 위해 플래그와 같은 기법을 사용할 수도 있지만 이는 자료구조의 사용을
// 매우 지저분하게 만든다는 단점이 있습니다.

// 이를 해결하기 위해 더미 테일을 삭제합니다.

typedef struct Node {
	int data;
	struct Node* next;
} Node;
Node* head;
//Node* tail;

int listInitialize() {
	head = malloc(sizeof(Node));
	if (head == NULL) {
		perror("listInitialize");
		return -1;
	}
	head->next = head;
	return 0;
}

int listFinalize() {
	if (head == NULL) {
		fprintf(stderr, "listFinalize: list is wrong\n");
		return -1;
	}

	while (head->next != head) {
		Node* target = head->next;
		head->next = target->next;
		free(target);
	}

	free(head);
	return 0;
}

int listAdd(int data) {
	Node* node = malloc(sizeof(Node));
	if (node == NULL) {
		perror("listAdd");
		return -1;
	}
	node->data = data;
	node->next = head;

	Node* cur = head;
	while (cur->next != head)
		cur = cur->next;
	cur->next = node;
	return 0;
}

void listDisplay() {
	system("cls");
	printf("[head]");
	for (Node* node = head->next; node != head; node = node->next)
		printf("->[%2d]", node->data);
	printf("->[head]");
	getchar();
}

void listReverse() {
	Node* prev = head;
	Node* cur = head->next;
	Node* next;

	while (cur != head) {
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	cur->next = prev;
}

int main() {
	listInitialize();

	listDisplay();
	for (int i = 0; i < 5; i++) {
		listAdd(i + 1);
		listDisplay();
	}

	listReverse();
	listDisplay();

	listReverse();
	listDisplay();

	listFinalize();
	return 0;
}