# 개요

> - 메모리풀은 비록 메모리의 동적할당을 줄이지만 재사용성이 매우 떨어지게 된다.
따라서 결국은 bucket 형식으로 회귀하게 되었고 그에따라 list형식으로 추가하게 된다.

> - 여기서 해쉬 개념을 사용할것이다. 현존하는 알고리즘중에서는 해쉬값이 충돌되지않게 할수있는
알고리즘은 존재하지않는다 따라서 데이터 비교를 위해 함수 equals를 만들어주도록 한다.

## 1.c

### 구성

> - 노드의 구성은 다음과 같이한다.

```
typedef struct Node {
	void* key;
	void* value;
	int hash;	// 키에 대한 해시 값, key의 타입을 알 수 없으므로
				// 사용자로부터 정보를 얻어 해시 값을 계산하여 저장합니다.
	struct Node* next;
} Node;
```
> - 비록 우리가 리스트형식을 채택했다곤 하지만 이중연결리스트 처럼 prev를 두는것은 코드도 복잡해질뿐더러 굳이 그럴필요도없고 오버스펙이 되게된다.

해쉬맵의 형식은 다음과 같이 정의 된다.

```
typedef struct Hashmap {
	Node** buckets;
	size_t bucketSize;
	size_t count;

	HashFn hash;					// 키를 정수, 즉 해시로 변환하는 함수
	EqualsFn equals;	// 데이터 비교를 위한 함수
} Hashmap;
```

> - HashFn과 EqaulsFn은 함수포인터이다.
```
typedef int(*HashFn)(void* key); //함수포인터
typedef int(*EqualsFn)(void* key1, void* key2);//함수포인터
```

제일처음의 형식과 크게 달라진 부분은 없다.
제일처음의 형식을 제대로 공부했다면 설명이 필요없는 코드이다.

## 2.c

### 변경점 

#### myHash 함수의 추가

> - 키의 길이값을 반환하는 함수이다.

#### myEquals 함수의 추가

> - 문자열의 비교값을 반환한다.

## 3.c

#### createNode 함수의 추가

> - 우선 해쉬맵에는 노드가 있어야 한다. 따라서 해당함수를 만들었다.

### 변경점



#### hashkey 함수의 추가

#### calculateIndex 함수의 추가



#### equalsKey 함수의 추가

#### hashmapPut 함수의 추가

#### hashmapDispaly함수의 추가
