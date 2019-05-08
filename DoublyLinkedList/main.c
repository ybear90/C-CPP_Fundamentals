#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int data;
	struct Node* prev;
	struct Node* next;
} Node;



void insert(Node* head, Node* tail, int data) {
	// Head, Tail ��尡 ���� ��쿡 ����ó��
	if (head == NULL || tail == NULL) {
		printf("����� ���Ḯ��Ʈ�� �������� �ʾҽ��ϴ�. \n");
		return;
	}

	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	Node* cur;
	cur = head->next;
	while (cur->data < data && cur != tail) {
		cur = cur->next;
	}

	// ���� ��� ���� �κ�(��ġ ã�� �ִ´�)
	Node* prev = cur->prev;
	prev->next = node;
	node->prev = prev;
	cur->prev = node;
	node->next = cur;
}

void removeFront(Node* head, Node* tail) {
	// ���� ������ �ϳ��� ���� ��쿡 ���� ó��(Head, Tail ��常 �ִ� ���)

	if (head->next == tail && tail->prev == head) {
		printf("������ ���Ұ� �����ϴ�.");
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