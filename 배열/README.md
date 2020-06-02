# ARRAY

## 1.c

### ISSUE : 배열의 기초

```
int arr[5] = {1,2,3,4,5};
```
위의 배열의 시작주소는 100이라고 가정한다

> - 배열의 이름은 곧 그 배열의 시작주소이다 즉 배열의[0]번째 방의 시작주소와 같다는 것이다

> - 배열의 한방의 크기는 담고있는 자료의 형태의 크기와 같다.

> - n번째 방을 참조하는 방법은 arr[n]도 있지만 첨자로 참조하여 *(arr+n)으로 참조하는 방법도 있다. (주소는 'arr+n'으로 참조가능 )

> - 위의 배열에서 arr + 1을 하면 arr은 배열의 이름 = 배열주소 즉 101이라고 오해할수가 있으나 앞에 sizeof(자료형)이 생략되어있다.
```
int address = arr + sizeof(*arr) * i //주소 참조법.
```

> - 웬만하면 배열명은 시작주소로 계산되어 arr[0]번째방이 참조 되어지지만 예외의 경우가 있다.
```
int size = sizeof(arr) // 4*1 = 4 (x)      4*5 =20 (o)
```

#### 배열의 한계
> 배열은 다음과 같은 한계점을 가지고 있다.

>	> 1. 배열의 크기(길이) 정보가 없음
>	> 2. 배열의 범위를 넘어설 경우를 알 수 없음
>	> 3. 배열의 크기를 조절할 수 없음

## 2.c

### ISSUE : 정수형의 자료를 저장하는 배열 만들기

#### 기본구조 

```
int arr[5];
int size = 5;
int count;
```

> - int arr[5]는 말그대로 방크기가 5개인 배열이다.
> - int size = 5 는 배열의 크기가 5개라는뜻이 된다. size를 추가한 이유는 배열에 원소를 추가할때 현재 원소의 갯수랑 비교해서 
추가적인 원소의 유입을 막기위함이다.
> - int count 는 count는 default 값이 0이 되며 데이터가 추가될때마다 1씩 늘어난다. count는 곧 배열에 들어있는 자료의 개수가 된다.
또한 size와의 비교연산에도 사용할목적으로 사용된다. 즉
> > 1. 현재 배열에 들어있는 자료수

> > 2. size와의 비교대상 으로 정의 된다.

#### 메커니즘

```
int arrayAdd(int data) {
	// 배열이 가득 찼는지를 조사
	if (count == size)
		return -1;
	arr[count++] = data;
	return 0;
}
```
> count == size를 이용해 방이 꽉찼는지 확인후 

> count번지 방의 주소에 접근하여 데이터를 집어넣는다.

#### 문제점 

> 두개이상의 배열을 선언할시에는 같은 함수로 모든배열을 컨트롤 하지 못한다.

## 3.c

### ISSUE : 단하나의 메서드를 가지고 여러개의 배열을 컨트롤하기.

#### 문제점 분석 

> - 두개이상의 배열을 선언할 시에는 그 개수에 맞게 컨트롤할수있는 함수를 1:1로 선언해주어야 한다. 우리의 목적은 단하나의 함수로 여러개의 함수를 컨트롤할수가 있는 코드를 구현하는 것이다. 

#### 문제 해결방안

> - 이와 같은 상황이 발생한 이유는 심볼들이 모두 전역으로 선언 되었기 때문이다 . 
> - 이 심볼들을 지역심볼들로 변환한다면 문제점이 해결될 것이다.

##### 수정 전 코드
```
int arrayAdd(int data);
void arrayDisplay();
```

##### 수정 후 코드

```
int arrayAdd(int arr[], int size, int * count,int data);
void arrayDisplay(int arr[],int size,int * count)
```

그리고 전역 심볼들을 모두 날려 버렸다.

#### 문제점 

> - 지역변수로 전환함에 따라서 함수의 인자가 많아 지저분해 보인다. 이를 정리할필요가 있어보인다.


## 4.c

### ISSUE : 함수의 인자가 많아져 보기 흉하다 

#### 문제점 분석 

> -함수의 인자가많아짐으로 인해 간단한 함수를 호출하는데 신경쓸것도 많아질뿐더러 실수할 위험성이 높
아져 있다. 

#### 해결 방안 

> - 배열과 관련된 것들을 가리키는 성질들을 모두 하나의 구조체로 묶어서 선언한다. 그렇게 하면 하나의 인자만 함수에 던져주어도 여러개를 던져주는것과 같은 성질을 가질것이다.
또한 추상화가 이루어 짐에 따라 자료를 관리하기 더 쉬워질것이다.
그 형태는 아래와 같다.
```
typedef struct Array {
	int contents[5];	// int arr[5];
	int size;
	int count;
} Array;
````

또한 프로그램을 시작할때 초기화 함수를 
#### 문제점 
> - 구조체로 모든 요소를 한군데로 모은것은 좋았다. 하지만 배열의 기본상태설정, 즉 초기화를 사용자에게 전가하는것은 부적절하다. 따라서 프로그래머가 라이브러리에서 초기화 하는것이 좋아 보인다.

## 5.c

### ISSUE : 초기화의 의무를 사용자에서부터 라이브러리로 옮기기.

#### 문제점 분석 

> - 메인함수에서 사용자가 배열의 크기및 count를 설정해주어야만 배열을 사용할수가 있다. 
이는 라이브러리의 생성목적에 어긋나는 행동이며 따라서 그 의무를 라이브러리로 가져와야한다.

#### 해결 방안

> - c++에서의 생성자와 같은 역활을 맡길 배열 성질 초기화 함수를 선언해주도록 한다.
따라서 메인함수에서 초기화 코드를 없애고 arrayInitiate함수를 호출해준다.
```
int arrayInitiate(Array* array) {
	if (array == NULL) {
		fprintf(stderr, "arrayAdd: argument is null\n");
		return -1;
	}
	array->count = 0;
	array->size = 5;
	return 0;
}
```

#### 문제점 

> - 자료구조의 컨텍스트가 스택에 사용되고 있다. 이를 힙영역에 옮겨주는것이 추후 기능확장에 용이하지않을까 ??

## 6.c

### ISSUE : 배열의 구조를 이루는 요소들을 스택영역에서 힙영역으로 끌어올리기

#### 문제점 분석

> -  구조체의 컨텍스트가 스택영역에 선언되어있다. 이는 추후 배열의 관리및 상태변경에 불편함을 초래하게 된다. 따라서 힙영역에 할당함으로써 프로그래머와 사용자가 용이하게 사용할수 있도록 하는게 좋아보인다.

#### 해결 방안

> - 기존 메인함수에서 자료구조 컨텍스트들은 다음과 같이 선언되어 사용되어져 왔다.
```
Array arr1;
	arrayInitiate(&arr1);

	arrayDisplay(&arr1);
	for (int i = 0; i < 10; i++) {
		arrayAdd(&arr1, i + 1);
		arrayDisplay(&arr1);
	}
```
하지만 힙영역에다가 Array를 할당함에 따라
```
	Array* arr;// Array arr;
	arrayCreate(&arr); //arrayInitiate(&arr);
	//----------------------------
	arrayDisplay(arr);
	for (int i = 0; i < 10; i++) {
		arrayAdd(arr, i + 1);
		arrayDisplay(arr);
	}
	//----------------------------
	arrayDestroy(arr);
```

```
int arrayCreate(Array **array)
void arrayDestroy(Array* array)
int arrayAdd(Array* array, int data)
void arrayDisplay(const Array* array)
```
다음과 같이 함수의 인자가 변경되었다.


#### 문제점
> - 스택영역에서 힙영역으로 모든걸 끌어올린건 좋았다 하지만 메인함수에서 보듯이
arrayCreate 함수는 다른함수들과 다르게 &arr을 인수로 받고 있다. 이는 사용자로 하여금 
생각을 하게 함으로써 불편함을 초래하고 있다. 이러한 점때문에 
모든 함수의 인자들을 통일해야할 필요가 있어 보인다.

## 7.c

### ISSUE : 함수의 인자의 차수가 다르다. 인자의 차수를 통일시키자.

#### 문제점 분석

> - 기존의 ArrayCreate 함수는 &array 형을 입력받아 그 역참조값에 할당한 array* 를 넣고 있다. 굳이 선언후 리턴값을 역참조로주어 2번일할 필요가 있을까??

#### 해결 방안
> - 비효율적인 이 일련의 과정을 메인함수에서 2줄로 하기보다 어차피 arrayCreate함수의 return값은 array* 형인 셈이므로 return 형식도 Array* 로바꾸어주고 메인함수에서 다음과같이 바꾸어준다.
```
Array* arr = arrayCreate();
```
다음 한줄로 최적화 시킬수 있으며 또한 코드의 일관성을 완성시킨다.

#### 문제점

> - 이와 같이 최적화 시킨 코드를 언제까지고 5개의 자료만 추가할수는 없다. 사용자로부터 원하는 배열의 길이를 입력 받은후에 그에맞는 배열을 할당할수가 있다면 좋겠다.

## 8.c

### ISSUE : 배열의 길이를 동적으로 할당하기

#### 문제 분석

> - 기존의 구조체에서는 배열의 길이를 5개로 고정시켜놓아서 배열의 크기를 변경시킬 수단이 존재하지 않는다.

#### 해결 방안 

> - 스택영역에서 선언해주는것 보다 힙 영역에서 선언을 해준다면 사용자가 원하는 길이대로 동적으로 할당을 할수가 있지 않을까??

> - 수정 전 코드
```
typedef struct Array {
	int contents[5];
	int size;
	int count;
} Array;
```
> - 수정 후 코드
```
typedef struct Array {
	int *contents;	
	int size;
	int count;
} Array;
```

> - 이렇게 되면 배열의 크기를 어떻게 정의하느냐에 대한 문제가 생긴다. 이에 대한 문제점을 해결하기 위해 배열을 생성할때에 size_t형의 인자를 받아서 해당크기만큼 배열을 만들어준다.
```
int* contents =  malloc(sizeof(int)*size);
```
와 같이 정의해준다.
#### 변경사항 
> - arrayCreate함수의 array 선언에서 malloc으로 할당하다가 calloc으로 할당함수가 바뀌었다. 바뀐이유는 별게 아니고 Array 인자중에 count라는 인자가 있는데 처음 배열이 만들어 졌을때에는 그 갯수가 0개이므로 모든 요소들을 0으로 만들어 주는 calloc을 사용하여 count를 0으로 초기화 하는 코드를 줄였다.

## 9.c

### ISSUE : 이미 추가된 데이터의 값 변경하기.

## a.c

### ISSUE : 배열 값 사이에 새로운 배열 값을 삽입하기.

#### 특이점

> - 최초의 코드
```
for (int i = array->count;i >index;i--) { 
		array->contents[i] = array->contents[i - 1];
	}
```
> - 변경 코드
```
memmove(array->contents+index+1,array->contents+index,sizeof(int)*(array->count-index));
	array->contents[index] = data;
	array->count++;
```
> - 원하는 번지의 방에 자료를 넣기전에 그 해당방번호부터 한칸씩 뒤로 밀어준다.그리고 빈공간에 자료를 꽂아준다.

> - 코드의 변경이유는 최적화 때문이다. 반복문의 남용은 프로그램 속도 저하의 주 원인이 된다. 따라서 메모리를 그대로 복사해서 옮겨주는 함수를 찾게 되었다. 

#### memcpy? memmove?

> - memcpy 와 memmove는 둘다 메모리를 복사해주는 함수이다.  둘의 차이는 memcpy는 임시버퍼를 두고 memmove는 두지않는다는 것이다. memcpy는 더빠르고 memmove는 더 안정적이다. 

> - 그렇다면 왜 memmove를 사용하였느냐? 이다. memcpy는 복제할때 곧바로 그 영향이 적용된다. 이게 평소에는 괜찮지만 자기자신을 복사한다고 가정하면 

```
int* arr[5] ={1,2,3,4,5};
memcpy(arr,arr+1;sizeof(arr));
```
우리는 11234를 기대했으나 11111이 나올것이다. 따라서 memcpy는 자기자신을 복사할수가 없으며 불안정하다. 그래서 조금느리지만 안정적인 memmove를 앞으로 사용할것이다.

## b.c

### ISSUE : 데이터를 읽어오는 함수를 만들자 
> - 

## c.c

### ISSUE : 데이터를 삭제하는 함수를 만들자

## d.c(변경사항 x)

#### 문제점 
> - 배열의 크기가 처음선언한 크기 그대로 고정되어있다

## e.c

### ISSUE : 배열의 크기를 유연하게 하자

#### 문제점 분석 
> - 우리는 데이터를 추가할때 예정된 배열의 크기를 초과하면 오류를 리턴하는등 배열의 크기가 유연하지않다. 자료의 개수에 따라 

#### 해결방안 
>- 

배열의 최소 크기는 4, 최대 크기는 4096으로한다.

```
#define MAX_SIZE	(4096)
static int increaseSize(Array* array, int size) {
	if (array == NULL) {
		return -1;
	}
	if (array->size == NULL) {
		return -1;
	}
	if (array->size == array->count) {
		int len = (sizeof(array->contents) / (sizeof(array->contents[0])));
		int newLen = len * size;
		if (newLen >= MAX_SIZE || newLen < 0) {
			newLen = MAX_SIZE;
		}

		array->contents = realloc(array->contents, sizeof(int)*newLen);

		array->size = (array->size)*size;
	}
	
	
	return 0;
}

```
```
if (count == array->size) {
		int newSize = count * 2;
		if (newSize > MAX_SIZE || newSize < count)
			newSize = MAX_SIZE;
```

#### 문제점 : 자원할당정책이 여러곳에 분산되어있다. 이는 이후 유지보수와 버그픽스에 어려움을준다 


## f.c

### ISSUE : 자원할당 정책을 한곳에 모으자

#### 해결방안

```
#define INITIAL_SIZE	(4)
Array* arrayCreate() {
	Array* array = calloc(1, sizeof(Array));
	if (array == NULL) {
		perror("arrayCreate");
		return NULL;
	}

	int* contents = malloc(sizeof(int) * INITIAL_SIZE);	// * size);
	if (contents == NULL) {
		perror("arrayCreate");
		free(array);
		return NULL;
	}

	array->contents = contents;
	array->size = INITIAL_SIZE;
	return array;
}
```

### 문제점 

> - 위의코드는 유연하게 배열의 길이를 늘리는 것은 좋으나 사용자가 선언만 하고 사용을 하지않았을때 메모리의 누수가 발생한다.

## g.c (변경없음)

## h.c

### ISSUE :  배열선언후 미사용시에 지연된 초기화가 발생한다. 

#### 해결 방안

> - 배열 선언시에는 배열 객체만 만들어주고 반환하고 그 길이를 정해주지않는다. 삽입이나 추가와 같은 유효한 동작이 발생할시에 비로소 그 배열의 INITIAL_SIZE만큼 그 배열의 길이를 잡아주도록 한다. 
이러한 초기화법을 지연된 초기화 법이라고 한다.

## i.c

### ISSUE : 제네릭 기법을 사용하자.

#### 특이점

> - 출력함수에 함수포인터를 인자로 삽입해 표현하고 싶은 함수의 형식대로 출력하도록 한다.
```
const char* toPerson(const void* data) {
	static char buf[32];
	const Person* person = (const Person*)data;
	sprintf(buf, "%s(%d)", person->name, person->age);
	return (const char*)buf;
}
```
> - 와 같은 표현하고자하는 형식의 함수를 만들고

```
void arrayDisplay(const Array* array, const char*(*display)(const void*)) {
	if (array == NULL || display == NULL) {
		fprintf(stderr, "arrayDisplay: argument is null\n");
		return;
	}

	system("cls");
	for (int i = 0; i < array->size; i++) {
		if (i < array->count)
			printf("[%s]", display(array->contents[i]));
		else
			printf("[%2c]", ' ');
	}
	getchar();
}
```
> - 다음과 같이 display 함수의 인자에 함수포인터를 삽입한다.

```
		arrayDisplay(arr, toPerson); 
```

그리고 사용은 위와 같이 호출한다.
