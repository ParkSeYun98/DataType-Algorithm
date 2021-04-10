#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

typedef struct
{
	int *queue; // 저장할 배열
	int size; 
	int front; 
	int rear; 
}Queue;

Queue *CreateQueue(int size)
{
	Queue *pQueue = (Queue *)malloc(sizeof(Queue)); // 헤드노드 메모리 동적할당
	if (pQueue == NULL)
		return NULL;

	pQueue->queue = (int *)malloc(size * sizeof(int)); // 데이터노드 메모리 동적할당
	if (pQueue->queue == NULL)
	{
		free(pQueue);
		return NULL;
	}
	pQueue->size = size;
	pQueue->front = pQueue->rear = 0;

	return pQueue; // 헤드노드 시작주소
}

void Enqueue(Queue *q, int item);
int Dequeue(Queue *q);
int IsFullQueue(Queue *q);
int IsEmptyQueue(Queue *q);
int CheckTwoQueues(Queue *q1, Queue *q2);
void PrintCheckResult(Queue *q1, Queue *q2);

int main(void)
{
	int size1, size2; // 입력받을 큐의 사이즈
	int arr1[MAX_SIZE], arr2[MAX_SIZE]; // 입력값을 잠시 저장할 배열

	printf("두 큐 비교 프로그램 ...\n\n\n");
	printf("Input Queue1's Size : ");
	scanf("%d", &size1);
	printf("Input Queue2's Size : ");
	scanf("%d", &size2);
	
	Queue *queue1 = CreateQueue(size1+1); 
	Queue *queue2 = CreateQueue(size2+1); 

	for (int i = 0;i < size1;i++)
	{
		printf("Enter Queue1's Input %d: ", i + 1);
		scanf("%d", &arr1[i]);
		Enqueue(queue1, arr1[i]);
	}

	for (int i = 0;i < size2;i++)
	{
		printf("Enter Queue2's Input %d : ", i + 1);
		scanf("%d", &arr2[i]);
		Enqueue(queue2, arr2[i]);
	}

	PrintCheckResult(queue1, queue2);

	return 0;
}

void Enqueue(Queue *q, int item) // 삽입 함수
{
	if (IsFullQueue(q))
	{
		return;
	}
	else
	{
		q->rear = (q->rear + 1) % q->size; // rear 이동
		q->queue[q->rear] = item; // 삽입
	}
}

int Dequeue(Queue *q) // 삭제 함수
{
	if (IsEmptyQueue(q))
	{
		return 0;
	}
	else
	{
		q->front = (q->front + 1) % q->size; // front 이동
		return q->queue[q->front]; // 삭제
	}
}

int IsFullQueue(Queue *q) // 큐가 가득 찼음을 알리는 함수
{
	if ((q->rear + 1) % q->size == q->front)
		return 1;
	else
		return 0;
}

int IsEmptyQueue(Queue *q) // 큐가 비어있음을 알리는 함수
{
	if (q->front == q->rear)
		return 1;
	else
		return 0;
}

int CheckTwoQueues(Queue *q1, Queue *q2) // 두 큐 비교 함수
{
	int dequeue_item1 = 0, dequeue_item2 = 0;

	if (q1->size != q2->size) // 사이즈가 다르면 0 리턴
		return 0;
	else
	{
		for (int i = 0;i <= q1->rear;i++) 
		{
			dequeue_item1 = Dequeue(q1); // dequeue의 리턴 값 int형 변수에 저장
			dequeue_item2 = Dequeue(q2);

			if (dequeue_item1 != dequeue_item2) // 같은 위치에서 두 큐의 내용이 다르면 0 리턴
			{
				return 0;
			}
		}
		return 1; // 위의 검사를 모두 통과했으면 1 리턴
	}
}

void PrintCheckResult(Queue *q1, Queue *q2) // 결과 출력 함수
{
	if (CheckTwoQueues(q1, q2) == 0) // 체크 함수에서 0을 리턴했으면 FALSE 리턴
	{
		printf("\n FALSE :: They are different Queues\n\n");
	}
	else // 체크 함수에서 1을 리턴했으면 TRUE 리턴
	{
		printf("\n TRUE :: They ar e same Queues\n\n");
	}
}