//#pragma warning(disable:4996)
#define QUEUE_SIZE 5
#include <stdio.h>

typedef int element;
element queue[QUEUE_SIZE];
int rear = -1;
int front = -1;

void PrintQueue() {  //큐의 상태를 프린트 해주는 함수 
	int i;
	printf("\nQUEUE 상태: ");
	for(i=0; i<QUEUE_SIZE; i++){
		printf("[%d]=%5d   " , i, queue[i]);
	}
	printf("\n");
	printf("\n");
}

void createQueue(int n){   //큐를 생성하고  초기화하는 함수 (-1로 초기화) 
	int i;
	for(i=0; i<n; i++){
		queue[i]=-1;
	}
	printf("큐를  초기화하였습니다.\n");
	PrintQueue();
}

element Delete_q(){      //큐의 delete 연산 함수 
	int delvalue;
	printf("큐의 Delete 연산을 실행합니다.\n");
	if(front == rear) {
		printf("Error : Queue is Empty!! \n");
		return 0;
	}
	else { 
		delvalue = queue[++front];
		printf("Queue[%d] output %d delete success! \n", front, queue[front]);
		queue[front]=0;    //삭제된 곳은 0으로 초기화하여 비교 
		return delvalue;
	}
}

void Add_q(){   //큐의 add 연산 함수 

	element item;
	
	printf("큐에 저장할 값을 입력하세요 : ");
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

void main() {    //메인 함수 
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

