//�Ϲ� ���� Ʈ��, ���Ŀ� ���� ���� ��ȸ Ȯ�ο�. flag �ϳ� ���  
#include <stdio.h> 
#include <stdlib.h>

typedef struct tfNode {
    struct tfNode *left;
    char data;
    struct tfNode *right;
    int threadFlag;
} tfNode;

tfNode* makeNode(tfNode* left, char data, tfNode* right, int flag) {
    tfNode* ptr = (tfNode*) malloc(sizeof(tfNode));
    ptr->left = left;
    ptr->data = data;
    ptr->right = right;
    ptr->threadFlag = flag; 
    return ptr;
}

//Ʈ���� ���� ���� ����ϴ� �Լ�  
// This code is contributed by rathbhupendra
void print2DUtil(tfNode* root, int space) {
	
	int i;
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += 2;
 
    // Process right child first
    //print2DUtil(root->right, space);
    // thread Tree �� ��� 
    if (root->threadFlag !=1) print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    //KTW printf("\n");
    for (i = 2; i < space; i++)
        printf(" ");
    printf("%c\n",root->data);
 
    // Process left child
    print2DUtil(root->left, space);
}

// This code is contributed by rathbhupendra 
// Wrapper over print2DUtil()
void print2D(tfNode* root) {
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

tfNode* inorderStart(tfNode* ptr) {
    if (ptr == NULL)
        return NULL;
 
    while (ptr->left != NULL)
        ptr = ptr->left;
 
    return ptr;
}
 
//������ Ʈ���� ���� ��ȸ  
void inorder(tfNode* root) {
    tfNode* ptr = inorderStart(root);
    while (ptr != NULL) {
        printf("%c ", ptr->data);
 
        if (ptr->threadFlag)
            ptr = ptr->right;
        else
            ptr = inorderStart(ptr->right);
    }
}

//thread Tree�� ��� loop�� �����Ƿ� ������ 
int get_nodeNum(tfNode *root) {
	int num = 0;
	if (root==NULL) {
		return 0;
	} else {
		num = 1;
		if (root->threadFlag==1) return num; //thread Ʈ���� ��� ��� 
		num += (get_nodeNum(root->left) + get_nodeNum(root->right));
		return num;
	}
}

void main() {
	
//���� 3.1�� ����	
//Ʈ�� ���� 
    tfNode* A = makeNode(NULL, 'A', NULL, 0);
    tfNode* B = makeNode(NULL, 'B', NULL, 0);
    tfNode* C = makeNode(NULL, 'C', NULL, 0);
    tfNode* D = makeNode(NULL, 'D', NULL, 0);
    tfNode* E = makeNode(NULL, 'E', NULL, 0);
    tfNode* F = makeNode(NULL, 'F', NULL, 0);
    tfNode* G = makeNode(NULL, 'G', NULL, 0);

print2D(G);
	    
    tfNode* _p1 = makeNode(A, '+', B, 0); 
//print2D(_p1);	   
    tfNode* _sl1 = makeNode(C, '/', D, 0);
    tfNode* _as1 = makeNode(_p1, '*', _sl1, 0);
    tfNode* _am1 = makeNode(E, '%', F, 0);	    
    tfNode* _p2 = makeNode(_as1, '+', _am1, 0);
//print2D(_p2);   
    tfNode* root = makeNode(_p2, '/', G, 0);

print2D(root);
//����ڰ� ������ ����, �׷��� Ʈ�� ������ �ջ�Ǿ
//get_node_num ��"->right" ȣ���ϴ� binary tree�� �Ϲ� �Լ��� ���� ��� ���Ѵ�
//flag�� �̿��ؼ� �׷� �Լ��� �����ؾ� �Ѵ�.
    
    A->right = _p1; A->threadFlag = 1;
    B->right = _as1; B->threadFlag = 1;
    C->right = _sl1; C->threadFlag = 1;
    D->right = _p2; D->threadFlag = 1;		
    E->right = _am1; E->threadFlag = 1;
    F->right = root; F->threadFlag = 1;
    
    printf("%d\n", get_nodeNum(root));    
    print2D(root);
    inorder(root); 
    
}

