//#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode { //����  ���� ����Ʈ�� ��� ���� ����
	struct ListNode* Llink;
	int data;
	struct ListNode* Rlink; 
}listNode;

typedef struct {  // ����  ���� ����Ʈ�� ��� ��� ���� ����
	listNode* Lhead;
	listNode* Fhead; 
}linkedList_h;

linkedList_h* createLinkedList_h(void){ //����  ���� ����Ʈ�� ��� ���  ����
	linkedList_h* H;
	H = (linkedList_h*)malloc(sizeof(linkedList_h));
	H->Lhead = NULL;
	H->Fhead = NULL;
	return H;
}

void addDNode(linkedList_h* H, int x){ 
	//���� ���� ����Ʈ�� ������ ��� �ڿ� ���� 

	listNode* NewNode;
	listNode* prevNode;
	
	NewNode = (listNode*)malloc(sizeof(listNode));
	NewNode->Llink = NULL;
	NewNode->data = x;
	NewNode->Rlink = NULL;
	
	if(H->Fhead == NULL){  //���� ����Ʈ�� ������ ��� 
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
    //���� ���� ����Ʈ�� Ư�� ��� �ڿ� ���� 
	//itdata : prevNode�� ������, adddata : ������ ����� ������
	
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

void deleteDNode(linkedList_h* H, int deldata){  //����  ����  ����Ʈ�� Ư�� ��� ���� ���� 

	listNode* delNode;
	delNode = H->Fhead;
	
	if(delNode == NULL)return;
	
	while(delNode->data != deldata){
		delNode = delNode->Rlink;
	}
	
	if(delNode == H->Lhead){ //��尡 �� ���� ��� 
		H->Fhead = NULL;  
		H->Lhead = NULL;
	}
	else if(delNode == H->Fhead){  // ù ��° ��� �����ϴ� ���
		H->Fhead = delNode->Rlink;
		delNode->Rlink->Llink = NULL;
	}
	else {
		delNode->Llink->Rlink = delNode->Rlink;
		delNode->Rlink->Llink = delNode->Llink;
	}		
	free(delNode);
	printf("%d ������ ���� ���� ��尡 �����Ǿ����ϴ�.\n",deldata);
	return;
}

void printList(linkedList_h* L){
	//��� ������� ����Ʈ�� ����ϴ� �Լ�
	listNode* p;
	p = L->Fhead;
	
	if(p == NULL){
		printf("���� ����Ʈ�� �����Դϴ�.\n\n");
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
	 
	printf("1. ���� ���� ���� ����Ʈ ������ �Ϸ��Ͽ����ϴ�. \n\n");
	
	printf("2. ���� ���� ����Ʈ�� ��带 �߰��մϴ�(�����Ͱ� : 100, 300, 500). \n");
	addDNode(L,100);
	printList(L);
	 
	addDNode(L,300);
	printList(L);
	
	addDNode(L,500);
	printList(L);
	
	printf("3. ���� ���� ����Ʈ �߰� ��� �ڿ� ��带 �߰��մϴ�.\n" );
	printf("(�����Ͱ��� 100�� ��� �ڿ� �����Ͱ� 200�� ��带 �߰�)\n");
	addDitNode(L,100,200);
	printList(L);
	
	printf("4. ���� ���� ����Ʈ���� ��带 �����մϴ�(�����Ͱ� : 200, 300, 100, 500).\n"); 
	deleteDNode(L,200);
	printList(L);
	
	deleteDNode(L,300);
	printList(L);
	
	deleteDNode(L,100);
	printList(L);
	
	deleteDNode(L,500);
	printList(L);
	
	printf("���� ���� ����Ʈ ����, ���� ������ �������ϴ�. \n"); 
}
