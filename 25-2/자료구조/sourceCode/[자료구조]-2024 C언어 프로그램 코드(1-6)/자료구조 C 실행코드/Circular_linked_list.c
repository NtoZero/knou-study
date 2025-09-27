//#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode { //원형  연결 리스트의 노드 구조 정의
	int data;
	struct ListNode* link; 
}listNode;

typedef struct {  // 원형 연결 리스트의 헤드 노드 구조 정의
	listNode* head; 
}linkedList_h;

linkedList_h* createLinkedList_h(void){ //원형 연결 리스트의 헤드 노드  생성
	linkedList_h* H;
	H = (linkedList_h*)malloc(sizeof(linkedList_h));
	H->head = NULL;
	return H;
}

void addNode(linkedList_h* H, int x){ //원형 연결 리스트의 노드 삽입 
	//원형 리스트 첫 번째 노드 삽입 연산, x값은 100, 90, 80이라고 가정함 
	listNode* tempNode;
	listNode* NewNode;
	
	NewNode = (listNode*)malloc(sizeof(listNode));
	NewNode->data = x;
	NewNode->link = NULL;
	
	if(H->head == NULL){  //현재 리스트가 공백인 경우 
		H->head = NewNode;
		NewNode->link = NewNode;
		return;
	}
	
	tempNode = H->head;
	while(tempNode->link != H->head) tempNode=tempNode->link;
	NewNode->link = tempNode->link;
	tempNode->link = NewNode;
	H->head = NewNode;
}

void addMiddleNode(linkedList_h* H, int itdata, int adddata){
	//원형 연결 리스트 중간 노드로 삽입 연산
	//itdata : prevNode의 데이터, adddata : 삽입할 노드의 데이터 	
	listNode* prevNode;
	prevNode = H->head;
	
	while(prevNode->data != itdata){
		prevNode = prevNode->link;
	}
	
	listNode* NewNode;
	NewNode = (listNode*)malloc(sizeof(listNode));
	NewNode->data = adddata;
	NewNode->link = NULL;
	
	NewNode->link = prevNode->link;
	prevNode->link = NewNode;
	return;
}

void deleteCircularNode(linkedList_h* H, int deldata){  
	//원형 연결 리스트에서 노드를 삭제하는 연산 
	listNode* prevNode;
	listNode* delNode;
	
	prevNode = H->head;
	while(prevNode->link->data != deldata){
		prevNode = prevNode->link;
	}
	
	if(H->head == NULL)return;
	else {     // 리스트에 노드가 여러 개 있는 경우 
		delNode = prevNode->link;
		
		if(delNode == prevNode)H->head = NULL;  //노드가 한 개인 경우 
		else {
			prevNode->link = delNode->link;
			if(delNode == H->head) H->head = delNode->link; // 첫 번째 노드 삭제하는 경우
		}	 
		free(delNode);
	}
	printf("%d 데이터 값을 가진 노드가 삭제되었습니다.\n",deldata);
	return;
}

void printList(linkedList_h* L){
	//노드 순서대로 리스트를 출력하는 함수
	listNode* p;
	listNode* tmp;
	
	p = L->head;
	
	if(p == NULL){
		printf("연결 리스트가 공백입니다.\n\n");
		return;
	}
	else{
		printf("List = (");
		tmp = L->head;
		printf("%d", p->data);
		p = p->link;
		
		while(p != tmp){
			printf(" --> ");
			printf("%d", p->data);
			p = p->link;
		}	
	}

	printf(")\n\n");
} 

void main(){
	linkedList_h* L;
	L = createLinkedList_h();
	 
	printf("1. 공백 원형 연결 리스트 생성을 완료하였습니다. \n\n");
	
	printf("2. 원형 연결 리스트에 노드를 추가합니다(데이터값 : 100, 90, 80). \n");
	addNode(L,100);
	printList(L);
	 
	addNode(L,90);
	printList(L);
	
	addNode(L,80);
	printList(L);
	
	printf("3. 원형 연결 리스트 중간  노드 뒤에 노드를 추가합니다.\n" );
	printf("(데이터값이 100인 노드 뒤에 데이터값 110인 노드를 추가)\n");
	addMiddleNode(L,100,110);
	printList(L);
	
	printf("4. 원형 연결 리스트에서 노드를 삭제합니다(데이터값 : 110, 90,80).\n"); 
	deleteCircularNode(L,110);
	printList(L);
	
	deleteCircularNode(L,90);
	printList(L);
	
	deleteCircularNode(L,80);
	printList(L);
	
	deleteCircularNode(L,100);
	printList(L);
	
	printf("원형 연결 리스트 삽입, 삭제 연산이 끝났습니다. \n"); 
}
