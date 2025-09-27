//#pragma warning(disable:4996)
#define QUEUE_SIZE 5
#include <stdio.h>

typedef int element;
element queue[QUEUE_SIZE];
int rear = -1;
int front = -1;

void PrintQueue() {  //ť�� ���¸� ����Ʈ ���ִ� �Լ� 
	int i;
	printf("\nQUEUE ����: ");
	for(i=0; i<QUEUE_SIZE; i++){
		printf("[%d]=%5d   " , i, queue[i]);
	}
	printf("\n");
	printf("\n");
}

void createQueue(int n){   //ť�� �����ϰ�  �ʱ�ȭ�ϴ� �Լ� (-1�� �ʱ�ȭ) 
	int i;
	for(i=0; i<n; i++){
		queue[i]=-1;
	}
	printf("ť��  �ʱ�ȭ�Ͽ����ϴ�.\n");
	PrintQueue();
}

element Delete_q(){      //ť�� delete ���� �Լ� 
	int delvalue;
	printf("ť�� Delete ������ �����մϴ�.\n");
	if(front == rear) {
		printf("Error : Queue is Empty!! \n");
		return 0;
	}
	else { 
		delvalue = queue[++front];
		printf("Queue[%d] output %d delete success! \n", front, queue[front]);
		queue[front]=0;    //������ ���� 0���� �ʱ�ȭ�Ͽ� �� 
		return delvalue;
	}
}

void Add_q(){   //ť�� add ���� �Լ� 

	element item;
	
	printf("ť�� ������ ���� �Է��ϼ��� : ");
	scanf("%d",&item); 
	
	if(rear >= QUEUE_SIZE-1){
		printf("Error : Queue is Full!! \n");
		return;
	}
	else {
		queue[++rear] = item;
		printf("queue[%d] input %d : add success! \n", rear, queue[rear]);
	}
}

void main() {    //���� �Լ� 
	createQueue(QUEUE_SIZE);
	Add_q();
	PrintQueue();
	Add_q();
	PrintQueue();
	Delete_q();
	PrintQueue();
	Delete_q();
	PrintQueue();
	Delete_q();
	PrintQueue();
	Add_q();
	PrintQueue();
	printf("The End. \n");
}

