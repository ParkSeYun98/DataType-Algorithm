#include <stdio.h>
#include <stdlib.h>    // malloc, free 함수가 선언된 헤더 파일

// 노드 구조체 (linked list 이용)
typedef struct tStackNode
{
	int data;
	struct tStackNode *next;
}StackNode;

// 헤드 구조체 (linked list 이용)
typedef struct
{
	int count;
	StackNode *top;
}Stack;

Stack* CreateStack(int size);
void Push(Stack *pStack, int item);
int Pop(Stack *pStack);
void DestroyStack(Stack *pStack);
int IsEmptyStack(Stack *pStack);

int main(void)
{
	Stack *pStack = CreateStack(1000);
	int dec_num;
	int rel = 0;

	printf("Enter an integer : ");  // 10진수 입력 
	scanf("%d", &dec_num);

	while (dec_num != 0) // Push를 이용하여 2진수로 변환 한 것을 stack에 저장
	{
		rel = dec_num % 2;
		Push(pStack, rel);
		dec_num = dec_num / 2;
	}

	while (!IsEmptyStack(pStack)) // Pop을 이용하여 2진수 출력
	{
		printf("%d", Pop(pStack));
	}
	printf("\n");

	DestroyStack(pStack);
	pStack = NULL;
	return 0;
}

// 헤드 구조체 생성 (메모리 동적 할당)
Stack* CreateStack(int size)
{
	Stack *pStack = (Stack *)malloc(sizeof(Stack));
	if (pStack == NULL) // 헤드 구조체 생성 오류
	{
		return NULL;
	}
	pStack->count = 0;      // count, top 초기화
	pStack->top = NULL;

	return pStack;
}

void Push(Stack *pStack, int item)
{
	StackNode *pNewNode = (StackNode *)malloc(sizeof(StackNode)); // 새 노드 구조체 생성 (동적 메모리 할당)
	if (pNewNode == NULL) // 노드 구조체 생성 오류
	{
		return; // void 함수이므로 return은 없음 -> 할당된 노드 구조체의 메모리 해제됨
	}

	pNewNode->data = item; // 새 노드구조체의 data에 push할 숫자 채움
	pNewNode->next = pStack->top; // 새 노드 구조체를 다음 노드 구조체로 링크
	pStack->top = pNewNode; // push (헤드구조체가 새 노드 구조체를 가리키게 함)
	pStack->count++; // stack에 몇개의 수가 있는지 나타냄
}

int Pop(Stack *pStack)
{
	if (pStack->top == NULL) // stack이 비어있는 경우 
	{
		return 0;
	}
	else
	{
		int item = pStack->top->data; // 헤드 구조체의 top이 가리키는 수(가장 앞단의 노드 구조체의 data)를 item에 저장
		StackNode *pOldTop = pStack->top; //  가장 앞단의 노드 구조체에 헤드 구조체의 top 저장 
		pStack->top = pOldTop->next; // 없어질 노드가 링크된 다음 노드 구조체를 헤드 구조체가 가리킴
		free(pOldTop); // pop 될 data를 가진 노드 구조체 메모리 해제
		pStack->count--; // stack에 몇개의 수가 있는지 나타냄
		return item; // pop 할 수 return 
	}
}

void DestroyStack(Stack *pStack) // 헤드구조체 메모리 해제
{
	free(pStack);
}

int IsEmptyStack(Stack *pStack) // Stack이 비었는지 확인
{
	if (pStack->count == 0)
	{
		return 1;
	}
	return 0;
}
