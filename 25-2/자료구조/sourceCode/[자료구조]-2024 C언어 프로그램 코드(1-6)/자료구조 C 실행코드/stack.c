//#pragma warning(disable:4996)
#define STACK_SIZE 5
#include <stdio.h>

typedef int element;
element stack[STACK_SIZE];
int top = -1;

void PrintStack() {   //���ð� ��� 
	int i;
	printf("\nSTACK ����: \n");
	for(i=STACK_SIZE-1; i>=0; i--){
		printf("[%d]=%5d\n" , i, stack[i]);
	}
	printf("\n");
	printf("\n");
}

void createStack(int n){  //���� �ʱⰪ ���� 
	int i;
	for(i=0; i<n; i++){
		stack[i]=-1;
	}
	printf("������ �ʱ�ȭ�Ͽ����ϴ�.\n");
	PrintStack();
}

element pop(){    //���� pop ���� 
	int popvalue;
	printf("������ POP ������ �����մϴ�.\n");
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

void push(){  //���� push ���� 
	element item;
	
	printf("���ÿ� ������ ���� �Է��ϼ��� : ");
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

void main() {   //���� �Լ�  
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
