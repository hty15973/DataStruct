# 원형 연결 리스트

## 원형 연결 리스트란?

> - 원형 연결리스는 헤드에서 시작해서 헤드로 끝나는 연결리스트이다 . 즉 탈출할수 있는 방법이 없으며 무한반복한다는 특징이 있다.

> - 말그대로 원형이기 때문에
자료 탐색에 2가지 선택지가 부여된다. 즉 , prev 방향으로 자료를 탐색할것이냐 next방향으로 자료를 탐색할것이냐 두가지경우로 나뉜다. 

> - 찾고자 하는 자료의 위치에 따라 더빠른 탐색방향이 바뀌게 된다.

## 0.c

### ISSUE : 역방향 탐색을 하도록 하는 함수를 만들도록 하자

#### 코드
```
void listReverse() {
	Node* prev = head;
	Node* cur = head->next;
	Node* next;

	while (cur != tail) {
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	cur->next = prev;
}
```

> - 정방향이던 리스트의 next를 그 이전의 노드에다 연결해주자. 즉 node -> next = prev가 되는것이다.

이것을 확인하려면 출력함수도 거꾸로 찍히게 만들어야한다. 그냥 display함수와 다르게 tail에서부터 시작하여 head일때까지 반복한다.
```
void listDisplayBackwardly() {
	system("cls");
	printf("[tail]");
	for (Node* node = tail->next; node != head; node = node->next)
		printf("->[%2d]", node->data);
	printf("->[head]");
	getchar();
}
```

#### 문제점

> - reverse함수를 만들었다고 reverse용 display함수를 따로 만들어주어야 한다. 이를 일반화 시킬방법을 찾아보아야 겠다.

> - reverse 함수를 2번이상 사용하면 프로그램이 죽어버린다. 종료 조건에 대한 재정의가 필요할것 같다.

> - 자원 할당이 제대로 이루어 지지않는다.

## 1.c

### ISSUE : REVERSE를 한번실행하고 REVERSE를 시행하면 제대로 작동하지않는다.

#### 문제점 분석 

> - 정상적인 사고의 흐름이라면 reverse 함수를 1회 실행한뒤 다시한번 실행한다면 원래의 정방향으로 나올것이라고 생각하고 reverse를 두번호출하면 오류가난다. 그이유는 list 내부에서 tail에 대한 정의를 변경시키지 않은채 또다시 실행시켜서 그렇다. 

> - 자원해제가 정상적으로 이루어지지않는 오류가 있다. 

#### 해결 방안 

> - 더미 테일을 삭제한다. 그렇게 함으로써 reverse를 2번이상사용을 하여도 오류가 나지않게 된다. 또한 자원해제도 정상적으로 만들어지게 된다.

> - display 함수의 조건도 != head로 바꿈으로써 한바퀴돌린다는 컨셉을 그대로 가져갈수 있게 된다.

```
void listDisplay() {
	system("cls");
	printf("[head]");
	for (Node* node = head->next; node != head; node = node->next)
		printf("->[%2d]", node->data);
	printf("->[head]");
	getchar();
}
```


