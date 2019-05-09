#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char data[100]; // �ϳ��� ���ڿ��� ��� char�� �迭
	struct Node* next;

} Node;

typedef struct Stack {
	Node* top;
} Stack;

// ����ǥ�� ����� �����ϴ� ���� ���ڿ� ����(���ڹ迭)
char res[100] = "";

// Stack function �κ�
void push(Stack* stack, char* data) {
	// ���ڿ��� ���ϴ� �κ��� �����ϰ� ���� SimplyStack �ڵ�� �����ϴ�.
	Node* node = (Node*)malloc(sizeof(Node));
	strcpy(node->data, data); // ���ڿ� ī��
	node->next = stack->top;
	stack->top = node;
}

char* getTop(Stack* stack) {
	// Pop���� �ٸ��� �� ���� ������ �����͸� '�ܼ��� ���' �Լ�
	Node* top = stack->top;
	return top->data;
}

// �� �� ��带 �����ϸ鼭 ����ϴ� �Լ�
char* pop(Stack* stack) {
	if (stack->top == NULL) {
		printf("���� ����÷ο찡 �߻��߽��ϴ�.\n");
		return NULL;
	}

	Node* node = stack->top;
	char* data = (char*)malloc(sizeof(char) * 100); // ���ڿ��� ���� ����(�����Ҵ����� ����)
	strcpy(data, node->data);
	stack->top = node->next;
	free(node);

	return data;
}

// ���� ǥ����� ���� ǥ������� �ٲٱ� ���� �켱���� ȹ�� �Լ�
int getPriority(char* i) {
	if (!strcmp(i, "(")) return 0;
	if (!strcmp(i, "+") || !strcmp(i, "-")) return 1;
	if (!strcmp(i, "*") || !strcmp(i, "/")) return 2;

	return 3;
}

// 37 + 5
// "37", "+", "5" : char** s �� ����...(���ڿ� ���� �����ϴ� �迭)
// ���� ǥ����� ���� ǥ������� ��ȯ�ϴ� ���� ��ȯ�Լ�
char* transition(Stack* stack, char** s, int size) {
	// �Լ� ȣ�� ���� ���� ������ �ױ� ������ �� �κ��� �������� �����ؾ�
	// ���� ���α׷��� ������ �Ǿ��� �� ������ �ּҰ��� �� �����ϰ� �۵��ϴ� ���� ���´�.
	//char res[100] = "";
	for (int i = 0; i < size; i++) {
		// 3 + 5
		// 3 5 +
		if (!strcmp(s[i], "+") || !strcmp(s[i], "-") || !strcmp(s[i], "*") || !strcmp(s[i], "/")) {
			while (stack->top != NULL && getPriority(getTop(stack)) >= getPriority(s[i])) {
				strcat(res, pop(stack));
				strcat(res, " ");
			}
			push(stack, s[i]);
		}
		else if (!strcmp(s[i], "(")) push(stack, s[i]);
		else if (!strcmp(s[i], ")")) {
			while (strcmp(getTop(stack), "(")) {
				strcat(res, pop(stack));
				strcat(res, " ");
			}
			pop(stack);
		}
		// �Ϲ� ������ ���
		else {
			strcat(res, s[i]);
			strcat(res, " ");
		}
	}

	// ���Ŀ� ���ÿ� �����ִ� ���Ұ� �ִٸ� ? �� �κ� ó��
	while (stack->top != NULL) {
		strcat(res, pop(stack));
		strcat(res, " ");
	}

	// return�� ���� ���� ǥ��� ��ȯ�� ���ڿ�(��곻�빰)
	return res;
}

// ���� ǥ�� ��� ����Լ�
void calculate(Stack* stack, char** s, int size) {
	int x, y, z;
	for (int i = 0; i < size; i++) {
		if (!strcmp(s[i], "+") || !strcmp(s[i], "-") || !strcmp(s[i], "*") || !strcmp(s[i], "/")) {
			x = atoi(pop(stack));
			y = atoi(pop(stack));
			
			if (!strcmp(s[i], "+")) z = y + x;
			if (!strcmp(s[i], "-")) z = y - x;
			if (!strcmp(s[i], "*")) z = y * x;
			if (!strcmp(s[i], "/")) z = y / x;

			char buffer[100];
			sprintf(buffer, "%d", z);
			push(stack, buffer);
		}
		else {
			push(stack, s[i]);
		}
	}
	printf("%s\n", pop(stack));
}

int main(void) {
	// �׽�Ʈ�� ���� �ڵ� �ۼ� �ʿ�
	system("pause");
	return 0;
}