#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char data[100]; // 하나의 문자열을 담는 char형 배열
	struct Node* next;

} Node;

typedef struct Stack {
	Node* top;
} Stack;

// 후위표기 결과를 저장하는 전역 문자열 변수(문자배열)
char res[100] = "";

// Stack function 부분
void push(Stack* stack, char* data) {
	// 문자열을 더하는 부분을 제외하곤 기존 SimplyStack 코드와 유사하다.
	Node* node = (Node*)malloc(sizeof(Node));
	strcpy(node->data, data); // 문자열 카피
	node->next = stack->top;
	stack->top = node;
}

char* getTop(Stack* stack) {
	// Pop과는 다르게 맨 위에 누적된 데이터를 '단순히 얻는' 함수
	Node* top = stack->top;
	return top->data;
}

// 맨 윗 노드를 삭제하면서 출력하는 함수
char* pop(Stack* stack) {
	if (stack->top == NULL) {
		printf("스택 언더플로우가 발생했습니다.\n");
		return NULL;
	}

	Node* node = stack->top;
	char* data = (char*)malloc(sizeof(char) * 100); // 문자열을 받을 변수(동적할당으로 선언)
	strcpy(data, node->data);
	stack->top = node->next;
	free(node);

	return data;
}

// 중위 표기법을 후위 표기법으로 바꾸기 위한 우선순위 획득 함수
int getPriority(char* i) {
	if (!strcmp(i, "(")) return 0;
	if (!strcmp(i, "+") || !strcmp(i, "-")) return 1;
	if (!strcmp(i, "*") || !strcmp(i, "/")) return 2;

	return 3;
}

// 37 + 5
// "37", "+", "5" : char** s 인 이유...(문자열 들을 보관하는 배열)
// 중위 표기법을 후위 표기법으로 변환하는 실제 변환함수
char* transition(Stack* stack, char** s, int size) {
	// 함수 호출 이후 리턴 변수가 죽기 때문에 이 부분을 전역으로 선언해야
	// 추후 프로그램이 실행이 되었을 때 엉뚱한 주소값이 들어가 엉뚱하게 작동하는 것을 막는다.
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
		// 일반 숫자인 경우
		else {
			strcat(res, s[i]);
			strcat(res, " ");
		}
	}

	// 이후에 스택에 남아있는 원소가 있다면 ? 그 부분 처리
	while (stack->top != NULL) {
		strcat(res, pop(stack));
		strcat(res, " ");
	}

	// return할 실제 후위 표기로 변환된 문자열(계산내용물)
	return res;
}

// 후위 표기 결과 계산함수
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
	// 테스트를 위한 코드 작성 필요
	system("pause");
	return 0;
}