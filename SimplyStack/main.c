
#include <stdio.h>
#define SIZE 10000
#define INF 99999999

// 배열을 이용한 구현 방법
//int stack[SIZE];
//int top = -1;
//
//void push(int data) {
//	if (top == SIZE - 1) {
//		printf("스택 오버플로우가 발생했습니다.\n");
//		return;
//	}
//	stack[++top] = data;
//}
//
//int pop() {
//	if (top == -1) {
//		printf("스택 언더플로우가 발생했습니다.\n");
//		return -INF;
//	}
//
//	return stack[top--];
//}
//
//void show() {
//	printf("--- 스택의 최상단 --- \n");
//	for (int i = top; i >= 0; i--) {
//		printf("%d\n", stack[i]);
//	}
//	printf("--- 스택의 최하단 --- \n");
//}

// 연결리스트를 이용한 스택 구현
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
		printf("스택 언더플로우가 발생했습니다.\n");
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
	printf("--- 스택의 최상단 ---\n");
	while (cur != NULL) {
		printf("%d\n", cur->data);
		cur = cur->next;
	}
	printf("--- 스택의 최하단 ---\n");
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

	// 여기서 주의할점 : 왜 Stack은 그냥 선언했고 Node는 동적 할당을 했을까 ?
	// C언어는 기본적으로 객체지향적 개념이 없기 때문에, 필요할 때 마다 메모리를 갖다 써야하는 경우엔 불편함이 없지 않을 수 없다.
	// 이번 예제는 단순 Stack을 만들어서 Stack 자료구조가 배운 개념대로 동작하는지 단순 확인하는 것이기 때문에 이 놈은 단일로 써도(구조체 그자체)
	// 로 써도 무방하고 Node 구조체는 필요할 때마다 만들어줘야 하므로(연결리스트) 동적 할당이 필요한 것이다.

	Stack s;
	s.top = NULL;
	push(&s, 7);
	push(&s, 5);
	push(&s, 4);
	pop(&s);
	push(&s, 6);
	pop(&s);
	show(&s); // 결과는 상단부터 : 5 7

	system("pause");
	return 0;
}