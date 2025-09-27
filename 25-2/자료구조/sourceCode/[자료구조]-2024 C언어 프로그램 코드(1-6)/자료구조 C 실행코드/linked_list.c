//#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode { //단순 연결 리스트의 노드 구조 정의
	int data;
	struct ListNode* link; 
}listNode;

typedef struct {  //리스트의 헤드 노드 구조 정의
	listNode* head; 
}linkedList_h;

linkedList_h* createLinkedList_h(void){ //연결리스트 생성
	linkedList_h* H;
	H = (linkedList_h*)malloc(sizeof(linkedList_h));
	H->head = NULL;
	return H;
}

void addNode(linkedList_h* H, int x){ //연결 리스트의 노드 삽입 
	//리스트 마지막 노드에 삽입 연산하며, x값은 100,200, 300 가정함 
	listNode* NewNode;
	listNode* LastNode;
	NewNode = (listNode*)malloc(sizeof(listNode));
	
	NewNode->data = x;
	NewNode->link = NULL;
	
	if(H->head == NULL){  //현재 리스트가 공백인 경우 
		H->head = NewNode;
		return;
	}
	
	LastNode = H->head;
	while(LastNode->link!=NULL) LastNode = LastNode->link;
	LastNode->link = NewNode;
}

void deleteNode(linkedList_h* H){  //리스트의 마지막 노드 삭제 연산 
	listNode* prevNode;
	listNode* delNode;
	
	if(H->head == NULL)return; //공백 리스트인 경우, 삭제 연산 중단 
	if(H->head->link == NULL){ //리스트에 노드가 한 개인 경우 
		free(H->head);        // 첫 번째 노드의 메모리를 해제 
		H->head = NULL;
		return;
	}
	else {     // 리스트에 노드가 여러 개 있는 경우 
		prevNode = H->head;
		delNode = H->head->link;
		while(delNode->link != NULL) {
			prevNode = delNode;
			delNode = delNode->link;
		}
		
		free(delNode);
		prevNode->link = NULL;
	}
}

void deleteitNode(linkedList_h* H, int deldata) {
	//연결 리스트에서 데이터의 값(deldata)을 가진 노드(delNode)를 삭제하는 연산 
	listNode* delNode;
	listNode* prevNode;
	prevNode = H->head;
	
	while(prevNode->link->data != deldata){
		prevNode = prevNode->link;
	}
	
	delNode = prevNode->link;
	prevNode->link = delNode->link;
	free(delNode);
	
	printf("%d 데이터 값을 가진 노드가 삭제되었습니다.\n",deldata);
	return;
}

void additNode(linkedList_h* H, int itdata, int adddata){
	//연결 리스트에서 특정 노드 뒤에 노드를 삽입하는  연산
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

void searchNode(linkedList_h* H, int itdata){ 
    // 연결 리스트에서 특정 노드를 검색하여 반환하고자 하는 연산 
	listNode* tempNode;
	tempNode = H->head;
	
	while(tempNode->data != itdata){
		tempNode = tempNode->link;
	}
	printf("%d 데이터 값을 가진 노드를 검색하는데 성공하였습니다.\n\n ");
}

void printList(linkedList_h* L){
	//노드 순서대로 리스트를 출력하는 함수
	listNode* p;
	printf("List = (");
	p = L->head;
	
	while(p != NULL){
		printf("%d", p->data);
		p = p->link;
		if(p != NULL)printf(" --> ");
	} 
	
	printf(")\n\n");
} 

void main(){
	linkedList_h* L;
	L = createLinkedList_h();
	 
	printf("1. 공백 연결 리스트 생성을 완료하였습니다. \n\n");
	
	printf("2. 연결 리스트에 노드를 추가합니다(데이터값 : 100, 200, 300). \n");
	addNode(L,100);
	printList(L);
	 
	addNode(L,200);
	printList(L);
	
	addNode(L,300);
	printList(L);
	
	printf("3. 특정 노드를 탐색합니다(데이터값 : 200).\n");
	searchNode(L,200);
	
	printf("4. 리스트 특정 노드 뒤에 노드를 추가합니다.\n" );
	printf("(데이터값이 100인 노드 뒤에 데이터값 150인 노드를 추가)\n");
	additNode(L,100,150);
	printList(L);
	
	printf("5. 특정 노드를 삭제합니다(데이터값 : 200).\n"); 
	deleteitNode(L,200);
	printList(L);
	
	printf("6. 마지막 노드를 삭제합니다.\n");
	deleteNode(L);
	printList(L);
	
	printf("연결리스트 삽입, 삭제 연산이 끝났습니다. \n");  
}

