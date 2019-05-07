#include <stdio.h>

// Simply linked list example
// 단방향 연결리스트 (with C언어) 예제
typedef struct {
	int data;
	struct Node* next;
} Node;

// 리스트 노드 추가 함수
void addFront(Node* root, int data) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = root->next;
	root->next = node;
}

// 리스트 노드 삭제 함수
void removeFront(Node* root) {
	Node* front = root->next;

	// 삭제상황에서 예외처리 : 삭제할 원소가 없는데 삭제 하려고 하는 경우
	if (front == NULL) {
		printf("삭제할 원소가 없습니다.");
		return;
	}

	root->next = front->next;
	printf("%d(이)가 들어있는 노드를 삭제합니다...\n\n", front->data);
	free(front);
}

// 리스트 메모리 해제 함수(전체 노드 삭제 함수)
void freeAll(Node* head) {
	Node* cur = head->next;
	int memoryFreeCount = 0; // 총 몇개의 노드를 지웠는지 세어주는 함수

	while (cur != NULL) {
		Node* next = cur->next;
		free(cur);
		memoryFreeCount++;
		cur = next;
	}

	printf("메모리 해제가 끝났습니다. 총 %d개의 노드 삭제 \n\n", memoryFreeCount);
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