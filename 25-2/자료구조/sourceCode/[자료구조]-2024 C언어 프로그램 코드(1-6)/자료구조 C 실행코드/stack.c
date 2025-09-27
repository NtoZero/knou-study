//#pragma warning(disable:4996)
#define STACK_SIZE 5
#include <stdio.h>

typedef int element;
element stack[STACK_SIZE];
int top = -1;

void PrintStack() {   //스택값 출력 
	int i;
	printf("\nSTACK 상태: \n");
	for(i=STACK_SIZE-1; i>=0; i--){
		printf("[%d]=%5d\n" , i, stack[i]);
	}
	printf("\n");
	printf("\n");
}

void createStack(int n){  //스택 초기값 설정 
	int i;
	for(i=0; i<n; i++){
		stack[i]=-1;
	}
	printf("스택을 초기화하였습니다.\n");
	PrintStack();
}

element pop(){    //스택 pop 연산 
	int popvalue;
	printf("스택의 POP 연산을 실행합니다.\n");
	if(top == -1) { 
		printf("Stack is Empty!! \n");
		return 0;
	}
	else { 
		printf("stack[%d] output %d pop success! \n", top, stack[top]);
		popvalue = stack[top];
		stack[top--]=-1;
		return popvalue;
	}
}

void push(){  //스택 push 연산 
	element item;
	
	printf("스택에 저장할 값을 입력하세요 : ");
	scanf("%d",&item); 
	
	if(top >= STACK_SIZE-1){
		printf("Stack is Full!! \n");
		return;
	}
	else {
		stack[++top] = item;
		printf("stack[%d] input %d : push success! \n", top, stack[top]);
	}
}

void main() {   //메인 함수  
	createStack(STACK_SIZE);
	push();
	PrintStack();
	push();
	PrintStack();
	pop();
	PrintStack(); 
	push();
	PrintStack();
	pop();
	PrintStack();
	pop();
	PrintStack();
	printf("The End. \n");
}
