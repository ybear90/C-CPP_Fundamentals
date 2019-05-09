#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 99999999

typedef struct Node {
	char data[100]; // 하나의 문자열을 담는 char형 배열
	struct Node* next;

} Node;

typedef struct Stack {
	Node* top;
} Stack;

// 후위표기 결과를 저장하는 전역 문자열 변수(문자배열)
//char res[100] = "";

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
		return -INF;
	}

	Node* node = stack->top;
	char* data = (char*)malloc(sizeof(char) * 100); // 문자열을 받을 변수(동적할당으로 선언)
	strcpy(data, node->data);
	stack->top = node->next;
	free(node);

	return data;
}

/*
	중위 표기법을 후위 표기법으로 바꾸는 방법

	1) 피연산자가 들어오면 바로 출력합니다.
	2) 연산자가 들어오면 자기보다 우선순위가 높거나 같은 것들을 빼고 자신을 스택에 담습니다.
	3) 여는 괄호 '('를 만나면 무조건 스택에 담습니다.
	4) 닫는 괄호 ')'를 만나면 '('를 만날 때까지 스택에서 출력합니다.
*/


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
		// 일반 숫자인 경우
		else {
			if (strcmp(s[i], " ")) strcat(res, s[i]); strcat(res, " ");
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

/*
	후위 표기법을 계산하는 방법

	1) 피연산자가 들어오면 스택에 담습니다.
	2) 연산자를 만나면 스택에서 두 개의 연산자를 꺼내서 연산한 뒤에 그 결과를 스택에 담습니다.
	3) 연산을 마친 뒤에 스택에 남아있는 하나의 피연산자가 연산 수행 결과입니다.
*/

// 후위 표기 결과 계산함수
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
	// 결과적으로 calculate 함수를 통해 계산이 끝나게 되면 결과물 하나만 남으므로(숫자로된 문자열 데이터) 이걸 그냥 출력한다 보면 된다 
	// Stack에 담겨져 있으므로 pop 함수로 끄집어 내면 사실상 끝!
	printf("계산결과는 : %s\n", pop(stack));
}

int main(void) {
	// 만들어진 계산기 사용을 위한 테스트 코드

	// 1) 스택 초기화
	Stack stack;
	stack.top = NULL;

	// 2) 문자열(수식) 삽입
	// 입력할 계산식을 문자열의 형태로 넣어줍니다
	// 단위 문자 옆에 항상 공백을 넣어주어 일정 패턴을 준 문자열로 된 수식입니다
	char a[100] = "( ( 3 + 4 ) * 5 ) - 5 * 7 * 5 - 5 * 10";
	int size = 1;

	// 공백이 없다 가정할때(스택엔 공백을 제외하고 넣을 예정이라) 실제 수식의 길이를 세는 부분
	for (int i = 0; i < strlen(a); i++) {
		if (a[i] == ' ') size++;
	}

	// ptr 변수에는 공백을 구분자로 하여 문자열을 저장할 예정입니다.
	char* ptr = strtok(a, " ");
	// 문자열을 저장할 char* 형 배열을 만드느라 이중 포인터형으로 동적할당이 됩니다.
	char** input = (char**)malloc(sizeof(char*) * size); 
	for (int i = 0; i < size; i++) {
		// 문자열을 저장하는 배열 각 칸당 100 사이즈의 문자열을 저장할 수 있도록 동적할당 해 줍니다.
		input[i] = (char*)malloc(sizeof(char) * 100);
	}
	for (int i = 0; i < size; i++) {
		strcpy(input[i], ptr);
		ptr = strtok(NULL, " "); 
	}

	// 후위 표기법 작동 테스트
	char b[1000] = "";
	strcpy(b, transition(&stack, input, size));
	printf("후위 표기법: %s\n", b);

	// 실제 계산기 테스트
	size = 1;
	for (int i = 0; i < strlen(b) - 1; i++) {
		// 마지막은 항상 공백이 들어가므로 1을 빼기
		if (b[i] == " ") size++;
	}
	char* ptr2 = strtok(b, " ");
	for (int i = 0; i < size; i++) {
		strcpy(input[i], ptr2);
		ptr2 = strtok(NULL, " ");
	}
	// 실제 계산하여 결과 출력
	// 현재 중간에 쓰레기 값이 들어가서 정상적으로 계산이 안됨(추후 디버깅 필요)
	calculate(&stack, input, size);
	system("pause");
	return 0;
}