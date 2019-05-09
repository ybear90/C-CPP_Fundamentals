
#include <stdio.h>
#define SIZE 10000
#define INF 99999999

// �迭�� �̿��� ���� ���
//int stack[SIZE];
//int top = -1;
//
//void push(int data) {
//	if (top == SIZE - 1) {
//		printf("���� �����÷ο찡 �߻��߽��ϴ�.\n");
//		return;
//	}
//	stack[++top] = data;
//}
//
//int pop() {
//	if (top == -1) {
//		printf("���� ����÷ο찡 �߻��߽��ϴ�.\n");
//		return -INF;
//	}
//
//	return stack[top--];
//}
//
//void show() {
//	printf("--- ������ �ֻ�� --- \n");
//	for (int i = top; i >= 0; i--) {
//		printf("%d\n", stack[i]);
//	}
//	printf("--- ������ ���ϴ� --- \n");
//}

// ���Ḯ��Ʈ�� �̿��� ���� ����
typedef struct {
	int data;
	struct Node* next;
} Node;

typedef struct {
	Node* top;
} Stack;

void push(Stack* stack, int data) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = stack->top;
	stack->top = node;
}

void pop(Stack* stack) {
	if (stack->top == NULL) {
		printf("���� ����÷ο찡 �߻��߽��ϴ�.\n");
		return -INF;
	}

	Node* node = stack->top;
	int data = node->data;
	stack->top = node->next;
	free(node);

	return data;
}

void show(Stack* stack) {
	Node* cur = stack->top;
	printf("--- ������ �ֻ�� ---\n");
	while (cur != NULL) {
		printf("%d\n", cur->data);
		cur = cur->next;
	}
	printf("--- ������ ���ϴ� ---\n");
}

int main() {
	/*push(7);
	push(5);
	push(4);
	pop();
	push(6);
	pop();
	show();
*/

	// ���⼭ �������� : �� Stack�� �׳� �����߰� Node�� ���� �Ҵ��� ������ ?
	// C���� �⺻������ ��ü������ ������ ���� ������, �ʿ��� �� ���� �޸𸮸� ���� ����ϴ� ��쿣 �������� ���� ���� �� ����.
	// �̹� ������ �ܼ� Stack�� ���� Stack �ڷᱸ���� ��� ������ �����ϴ��� �ܼ� Ȯ���ϴ� ���̱� ������ �� ���� ���Ϸ� �ᵵ(����ü ����ü)
	// �� �ᵵ �����ϰ� Node ����ü�� �ʿ��� ������ �������� �ϹǷ�(���Ḯ��Ʈ) ���� �Ҵ��� �ʿ��� ���̴�.

	Stack s;
	s.top = NULL;
	push(&s, 7);
	push(&s, 5);
	push(&s, 4);
	pop(&s);
	push(&s, 6);
	pop(&s);
	show(&s); // ����� ��ܺ��� : 5 7

	system("pause");
	return 0;
}