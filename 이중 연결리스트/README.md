# 이중 연결 리스트

## 이중 연결 리스트란??

> - 이중 연결 리스트는 기존의 단방향으로 진행되던 연결리스트를 양방향으로 탐색 할수 있게 노드의 구조를 next만두는것이 아니라 prev또한 두어서 
이전의 것도 탐색할 수 있도록 하는것이다. 

> - 이렇게 함으로써 사용자는 찾길원하는 방의 인덱스를 현재 리스트에 존재하는 데이터의 개수와 비교하여 더빠른 방향을 선택하여 탐색할수 있게
되었다.

> - 기존 노드

```
typedef struct Node {
	int data;
	struct Node* next;
} Node;
```

> - 변경 노드

```
typedef struct Node {
	int data;
	struct Node* next;
	struct Node* prev;
} Node;
```

다음과 같이 변경하였다.

> - 더미테일은 원형리스트에서 죽였지만 다시 살려내도록 한다. 

> - 초기 헤드와 테일의 next와 prev는 다음과 같다.
```
head->prev = head;
	head->next = tail;

	tail->prev = head;
	tail->next = tail;
```

## 0.c

### ISSUE : 이중연결리스트의 기초 구조 잡기

## 1.c


