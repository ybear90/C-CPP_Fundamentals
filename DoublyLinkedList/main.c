#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int data;
	struct Node* prev;
	struct Node* next;
} Node;



void insert(Node* head, Node* tail, int data) {
	// Head, Tail 노드가 없는 경우에 예외처리
	if (head == NULL || tail == NULL) {
		printf("양방향 연결리스트가 생성되지 않았습니다. \n");
		return;
	}

	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	Node* cur;
	cur = head->next;
	while (cur->data < data && cur != tail) {
		cur = cur->next;
	}

	// 실제 노드 연결 부분(위치 찾고 넣는다)
	Node* prev = cur->prev;
	prev->next = node;
	node->prev = prev;
	cur->prev = node;
	node->next = cur;
}

void removeFront(Node* head, Node* tail) {
	// 지울 노드들이 하나도 없는 경우에 예외 처리(Head, Tail 노드만 있는 경우)

	if (head->next == tail && tail->prev == head) {
		printf("삭제할 원소가 없습니다.");
	}
	
	Node* node = head->next;
	head->next = node->next;
	Node* next = node->next;
	next->prev = head;
	free(node);
}

void show(Node* head, Node* tail) {
	Node* cur = head->next;
	while (cur != tail) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
}

int main(void) {
	Node* head;
	Node* tail;

	head = (Node*)malloc(sizeof(Node));
	tail = (Node*)malloc(sizeof(Node));

	// Linked List init.
	head->next = tail;
	head->prev = head;
	tail->next = tail;
	tail->prev = head;
	
	// Inserting.
	insert(head, tail, 2);
	insert(head, tail, 1);
	insert(head, tail, 3);
	insert(head, tail, 9);
	insert(head, tail, 7);

	removeFront(head, tail);

	show(head, tail);
	printf("\n");
	
	system("pause");

	return 0;
}