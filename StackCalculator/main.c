#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 99999999

typedef struct Node {
	char data[100]; // �ϳ��� ���ڿ��� ��� char�� �迭
	struct Node* next;

} Node;

typedef struct Stack {
	Node* top;
} Stack;

// ����ǥ�� ����� �����ϴ� ���� ���ڿ� ����(���ڹ迭)
//char res[100] = "";

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
		return -INF;
	}

	Node* node = stack->top;
	char* data = (char*)malloc(sizeof(char) * 100); // ���ڿ��� ���� ����(�����Ҵ����� ����)
	strcpy(data, node->data);
	stack->top = node->next;
	free(node);

	return data;
}

/*
	���� ǥ����� ���� ǥ������� �ٲٴ� ���

	1) �ǿ����ڰ� ������ �ٷ� ����մϴ�.
	2) �����ڰ� ������ �ڱ⺸�� �켱������ ���ų� ���� �͵��� ���� �ڽ��� ���ÿ� ����ϴ�.
	3) ���� ��ȣ '('�� ������ ������ ���ÿ� ����ϴ�.
	4) �ݴ� ��ȣ ')'�� ������ '('�� ���� ������ ���ÿ��� ����մϴ�.
*/


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
	char res[100] = "";
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
			if (strcmp(s[i], " ")) strcat(res, s[i]); strcat(res, " ");
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

/*
	���� ǥ����� ����ϴ� ���

	1) �ǿ����ڰ� ������ ���ÿ� ����ϴ�.
	2) �����ڸ� ������ ���ÿ��� �� ���� �����ڸ� ������ ������ �ڿ� �� ����� ���ÿ� ����ϴ�.
	3) ������ ��ģ �ڿ� ���ÿ� �����ִ� �ϳ��� �ǿ����ڰ� ���� ���� ����Դϴ�.
*/

// ���� ǥ�� ��� ����Լ�
void calculate(Stack* stack, char** s, int size) {
	int x, y, z;
	for (int i = 0; i < size; i++) {
		if (!strcmp(s[i], "+") || !strcmp(s[i], "-") || !strcmp(s[i], "*") || !strcmp(s[i], "/")) {
			// atoi function : to change char to interger data.
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
	// ��������� calculate �Լ��� ���� ����� ������ �Ǹ� ����� �ϳ��� �����Ƿ�(���ڷε� ���ڿ� ������) �̰� �׳� ����Ѵ� ���� �ȴ� 
	// Stack�� ����� �����Ƿ� pop �Լ��� ������ ���� ��ǻ� ��!
	printf("������� : %s\n", pop(stack));
}

int main(void) {
	// ������� ���� ����� ���� �׽�Ʈ �ڵ�

	// 1) ���� �ʱ�ȭ
	Stack stack;
	stack.top = NULL;

	// 2) ���ڿ�(����) ����
	// �Է��� ������ ���ڿ��� ���·� �־��ݴϴ�
	// ���� ���� ���� �׻� ������ �־��־� ���� ������ �� ���ڿ��� �� �����Դϴ�
	char a[100] = "( ( 3 + 4 ) * 5 ) - 5 * 7 * 5 - 5 * 10";
	int size = 1;

	// ������ ���� �����Ҷ�(���ÿ� ������ �����ϰ� ���� �����̶�) ���� ������ ���̸� ���� �κ�
	for (int i = 0; i < strlen(a); i++) {
		if (a[i] == ' ') size++;
	}

	// ptr �������� ������ �����ڷ� �Ͽ� ���ڿ��� ������ �����Դϴ�.
	char* ptr = strtok(a, " ");
	// ���ڿ��� ������ char* �� �迭�� ������� ���� ������������ �����Ҵ��� �˴ϴ�.
	char** input = (char**)malloc(sizeof(char*) * size); 
	for (int i = 0; i < size; i++) {
		// ���ڿ��� �����ϴ� �迭 �� ĭ�� 100 �������� ���ڿ��� ������ �� �ֵ��� �����Ҵ� �� �ݴϴ�.
		input[i] = (char*)malloc(sizeof(char) * 100);
	}
	for (int i = 0; i < size; i++) {
		strcpy(input[i], ptr);
		ptr = strtok(NULL, " "); 
	}

	// ���� ǥ��� �۵� �׽�Ʈ
	char b[1000] = "";
	strcpy(b, transition(&stack, input, size));
	printf("���� ǥ���: %s\n", b);

	// ���� ���� �׽�Ʈ
	size = 1;
	for (int i = 0; i < strlen(b) - 1; i++) {
		// �������� �׻� ������ ���Ƿ� 1�� ����
		if (b[i] == " ") size++;
	}
	char* ptr2 = strtok(b, " ");
	for (int i = 0; i < size; i++) {
		strcpy(input[i], ptr2);
		ptr2 = strtok(NULL, " ");
	}
	// ���� ����Ͽ� ��� ���
	// ���� �߰��� ������ ���� ���� ���������� ����� �ȵ�(���� ����� �ʿ�)
	calculate(&stack, input, size);
	system("pause");
	return 0;
}