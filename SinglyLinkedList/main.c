#include <stdio.h>

// Simply linked list example
// �ܹ��� ���Ḯ��Ʈ (with C���) ����
typedef struct {
	int data;
	struct Node* next;
} Node;

// ����Ʈ ��� �߰� �Լ�
void addFront(Node* root, int data) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = root->next;
	root->next = node;
}

// ����Ʈ ��� ���� �Լ�
void removeFront(Node* root) {
	Node* front = root->next;

	// ������Ȳ���� ����ó�� : ������ ���Ұ� ���µ� ���� �Ϸ��� �ϴ� ���
	if (front == NULL) {
		printf("������ ���Ұ� �����ϴ�.");
		return;
	}

	root->next = front->next;
	printf("%d(��)�� ����ִ� ��带 �����մϴ�...\n\n", front->data);
	free(front);
}

// ����Ʈ �޸� ���� �Լ�(��ü ��� ���� �Լ�)
void freeAll(Node* head) {
	Node* cur = head->next;
	int memoryFreeCount = 0; // �� ��� ��带 �������� �����ִ� �Լ�

	while (cur != NULL) {
		Node* next = cur->next;
		free(cur);
		memoryFreeCount++;
		cur = next;
	}

	printf("�޸� ������ �������ϴ�. �� %d���� ��� ���� \n\n", memoryFreeCount);
}

void showAll(Node* head) {
	Node* cur = head->next;
	while (cur != NULL) {
		printf("%d ", cur->data);
		cur = cur->next;
	}printf("\n\n");
}

int main(void) {
	Node* head;
	head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	addFront(head, 2);
	addFront(head, 1);
	addFront(head, 7);
	addFront(head, 9);
	addFront(head, 8);
	removeFront(head);
	showAll(head);
	freeAll(head);
	system("pause");

	return 0;
}