//#pragma warning(disable:4996)
#define STACK_SIZE 50
#include <stdio.h>

typedef int element;
element stack[STACK_SIZE];
int top = -1;

void createStack(int n){    //스택 초기화 함수 
	int i;
	for(i=0; i<n; i++){
		stack[i]=-1;
	}
}

element pop(){     //스택 pop 연산 함수 
	int popvalue;
	if(top == -1) {
		printf("Stack is Empty!! \n");
		return 0;
	}
	else { 
		popvalue = stack[top];
		stack[top--]=0;
		return popvalue;
	}
}

void push(element item){      //스택 push 연산 함수 
	if(top >= STACK_SIZE-1){
		printf("Stack is Full!! \n");
		return;
	}
	else {
		stack[++top] = item;
	}
}

element evalPostfix(char *exp) {    //후위 연산 함수 
	int oper1, oper2, value, i=0;
	int length = strlen(exp);
	char symbol;
	
	for(i=0; i<length; i++){
		symbol = exp[i];
		if(symbol != '+' && symbol != '-' && symbol != '*' && symbol != '/') {
			value = symbol - '0';
			push(value);
		}
		else {
			oper2 = pop();
			oper1 = pop();
			switch(symbol) {
				case '+' : push(oper1 + oper2); break;
				case '-' : push(oper1 - oper2); break;
				case '*' : push(oper1 * oper2); break;
				case '/' : push(oper1 / oper2); break;
			}
		}
	}
	return pop();
}

void main() {   //메인 함수 
	createStack(STACK_SIZE);
	int result;
	char exp[50];
	printf("계산할 후위 표기식을 입력해 주세요: ");
	gets(exp);
	result = evalPostfix(&exp);
	
	printf("result = %d\n", result); 
	printf("The End. \n");
}
