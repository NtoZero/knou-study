//#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode { //이중  연결 리스트의 노드 구조 정의
	struct ListNode* Llink;
	int data;
	struct ListNode* Rlink; 
}listNode;

typedef struct {  // 이중  연결 리스트의 헤드 노드 구조 정의
	listNode* Lhead;
	listNode* Fhead; 
}linkedList_h;

linkedList_h* createLinkedList_h(void){ //이중  연결 리스트의 헤드 노드  생성
	linkedList_h* H;
	H = (linkedList_h*)malloc(sizeof(linkedList_h));
	H->Lhead = NULL;
	H->Fhead = NULL;
	return H;
}

void addDNode(linkedList_h* H, int x){ 
	//이중 연결 리스트의 마지막 노드 뒤에 삽입 

	listNode* NewNode;
	listNode* prevNode;
	
	NewNode = (listNode*)malloc(sizeof(listNode));
	NewNode->Llink = NULL;
	NewNode->data = x;
	NewNode->Rlink = NULL;
	
	if(H->Fhead == NULL){  //현재 리스트가 공백인 경우 
		H->Fhead = NewNode;
		H->Lhead = NewNode;
	}
	else{
		prevNode = H->Lhead;
		prevNode->Rlink = NewNode;
		NewNode->Llink = prevNode;
		H->Lhead = NewNode;
	}
}

void addDitNode(linkedList_h* H, int itdata, int adddata){ 
    //이중 연결 리스트의 특정 노드 뒤에 삽입 
	//itdata : prevNode의 데이터, adddata : 삽입할 노드의 데이터
	
	listNode* NewNode;
	listNode* prevNode;
	
	prevNode = H->Fhead;
	
	while(prevNode->data != itdata){
		prevNode = prevNode->Rlink;
	}
	
	NewNode = (listNode*)malloc(sizeof(listNode));
	NewNode->Llink = NULL;
	NewNode->data = adddata;
	NewNode->Rlink = NULL;
	
	NewNode->Rlink = prevNode->Rlink;
	prevNode->Rlink = NewNode;
	NewNode->Llink = prevNode;
	NewNode->Rlink->Llink = NewNode;
}

void deleteDNode(linkedList_h* H, int deldata){  //이중  연결  리스트의 특정 노드 삭제 연산 

	listNode* delNode;
	delNode = H->Fhead;
	
	if(delNode == NULL)return;
	
	while(delNode->data != deldata){
		delNode = delNode->Rlink;
	}
	
	if(delNode == H->Lhead){ //노드가 한 개인 경우 
		H->Fhead = NULL;  
		H->Lhead = NULL;
	}
	else if(delNode == H->Fhead){  // 첫 번째 노드 삭제하는 경우
		H->Fhead = delNode->Rlink;
		delNode->Rlink->Llink = NULL;
	}
	else {
		delNode->Llink->Rlink = delNode->Rlink;
		delNode->Rlink->Llink = delNode->Llink;
	}		
	free(delNode);
	printf("%d 데이터 값을 가진 노드가 삭제되었습니다.\n",deldata);
	return;
}

void printList(linkedList_h* L){
	//노드 순서대로 리스트를 출력하는 함수
	listNode* p;
	p = L->Fhead;
	
	if(p == NULL){
		printf("연결 리스트가 공백입니다.\n\n");
		return;
	}
	
	printf("List = (");
	while(p != NULL){
		printf("%d", p->data);
		p = p->Rlink;
		if(p != NULL)printf(" --> ");
	} 
	
	printf(")\n\n");
} 

void main(){
	linkedList_h* L;
	L = createLinkedList_h();
	 
	printf("1. 공백 이중 연결 리스트 생성을 완료하였습니다. \n\n");
	
	printf("2. 이중 연결 리스트에 노드를 추가합니다(데이터값 : 100, 300, 500). \n");
	addDNode(L,100);
	printList(L);
	 
	addDNode(L,300);
	printList(L);
	
	addDNode(L,500);
	printList(L);
	
	printf("3. 이중 연결 리스트 중간 노드 뒤에 노드를 추가합니다.\n" );
	printf("(데이터값이 100인 노드 뒤에 데이터값 200인 노드를 추가)\n");
	addDitNode(L,100,200);
	printList(L);
	
	printf("4. 이중 연결 리스트에서 노드를 삭제합니다(데이터값 : 200, 300, 100, 500).\n"); 
	deleteDNode(L,200);
	printList(L);
	
	deleteDNode(L,300);
	printList(L);
	
	deleteDNode(L,100);
	printList(L);
	
	deleteDNode(L,500);
	printList(L);
	
	printf("원형 연결 리스트 삽입, 삭제 연산이 끝났습니다. \n"); 
}
