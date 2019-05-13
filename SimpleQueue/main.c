#include <stdio.h>
//#define SIZE 10000
#define INF 99999999
/* FILO 방식의 큐 구현 */
//int queue[SIZE];
//int front = 0;
//int rear = 0;
//
//void push(int data) {
//	if (rear >= SIZE) {
//		printf("큐 오버플로우가 발생했습니다.\n");
//		return;
//	}
//	queue[rear++] = data;
//}
//
//int pop() {
//	if (front == rear) {
//		printf("큐 언더플로우가 발생했습니다.\n");
//		return -INF;
//	}
//	return queue[front++];
//}
//
//void show() {
//	printf("--- 큐의 앞 ---\n");
//	for (int i = front; i < rear; i++) {
//		printf("%d\n", queue[i]);
//	}
//	printf("--- 큐의 뒤 ---\n");
//}
//
//int main(void) {
//	push(7);
//	push(5);
//	push(4);
//	pop();
//	push(6);
//	pop();
//	show();
//
//	system("pause");
//
//	return 0;
//}
// 연결리스트 기반 큐 구현
typedef struct {
	int data;
	struct Node* next;
} Node;

typedef struct {
	Node* front;
	Node* rear;
	int count;
} Queue;

void push(Queue* queue, int data) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	
	if (queue->count == 0) {
		// 큐에 아무 원소도 없다면
		// 새롭게 만든 원소를 front로 가리킨다
		queue->front = node;
	}
	else {
		queue->rear->next = node;
	}
	queue->rear = node;
	queue->count++;
}

int pop(Queue* queue) {
	if (queue->count == 0) {
		printf("큐 언더플로우가 발생했습니다. \n");
		return -INF;
	}
	Node* node = queue->front;
	int data = node->data;
	queue->front = node->next;
	free(node);
	queue->count--;

	return data;
}

void show(Queue* queue) {
	Node* cur = queue->front;
	printf("--- 큐의 앞 ---\n");
	while (cur != NULL) {
		printf("%d\n", cur->data);
		cur = cur->next;
	}
	printf("--- 큐의 뒤 ---\n");
}

int main(void) {
	Queue queue;
	queue.front = queue.rear = NULL;
	queue.count = 0;
	push(&queue, 7);
	push(&queue, 5);
	push(&queue, 4);
	pop(&queue);
	push(&queue, 6);
	show(&queue);

	system("pause");

	return 0;
}