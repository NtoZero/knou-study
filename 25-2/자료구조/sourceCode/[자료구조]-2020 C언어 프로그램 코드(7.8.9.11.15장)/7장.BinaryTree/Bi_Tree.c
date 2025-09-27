#include <stdio.h> 
#include <stdlib.h>

typedef struct node{
    struct node *left;
    char data;
    struct node *right;
} node;

node* make_node(node* left, char data, node* right) {
    node* ptr = (node*) malloc(sizeof(node));
    ptr->left = left;
    ptr->data = data;
    ptr->right = right;
    return ptr;
}

//이진 트리의 노드 갯수
int get_node_num(node *root) {
	int num = 0;
	if (root==NULL) {
		return 0;
	} else {
		num = 1; 
		num += (get_node_num(root->left) + get_node_num(root->right));
		return num;
	}
}

//이진 트리의 잎 노드 갯수
int get_leaf_num(node *root) {
	int result = 0;
	if (root == NULL) {
		return 0;
	} else if (root->left == NULL && root->right == NULL) {
	 	return 1;
	}
	result += get_leaf_num(root->left) + get_leaf_num(root->right);
	return result;
}

//이진 트리의 깊이 
int get_level(node *root) {
	int left = 1, right = 1 ; //level 정의에 따라 0/1
	int cnt = 1;
	if (root == NULL) {
		return 0;
	} else {
		right = right + get_level(root->right);
		left = left + get_level(root->left);
		return right >= left ? right : left;
	}
}

// This code is contributed by rathbhupendra
void print2DUtil(node* root, int space) {
	
	int i;
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += 2;
 
    // Process right child first
    print2DUtil(root->right, space);
 
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
void print2D(node* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

void preorder(node* root) {
    if (root != NULL) {
        printf("%c ", root -> data);
        preorder(root -> left);
        preorder(root -> right);
    }   
}

void inorder(node* root) {
    if (root != NULL) {
        inorder(root -> left);
        printf("%c ", root -> data);
        inorder(root -> right);
    }
}

void postorder(node* root) {
    if (root != NULL) {
        postorder(root -> left);
        postorder(root -> right);
        printf("%c ", root -> data);
    }
}

//값을 주면 노드의 주소 반환 즉, NULL 아니면 ...
//여러개면 먼저 찾은 것 
node* search(node *root, char data) {
    
    node* ptr = NULL;;
	if (root == NULL) {
	    return NULL;
	} else if (root->data == data) {
		printf("찾음 %C\n", root->data);
		return root;
	} 
	if (root->left != NULL) {
		ptr = search(root->left, data);
	}
		if (ptr != NULL) return ptr;
		if (root->right != NULL) {
		ptr = search(root->right, data);
	} 
}

//부모 노드
//root는 부모가 없으므로 대상에서 제외
node* search_parent(node *root, node *it) {
    node* ptr = NULL;
	if (root->left != NULL) { 
		if (root->left->data == it->data) {return root;}
		else ptr = search_parent(root->left, it);
	} 
		if (ptr != NULL) return ptr;
	  	if (root->right != NULL) {
  		if (root->right->data == it->data) {return root;}
  		else ptr = search_parent(root->right, it);
  	}
}

//지정한 위치 here에 노드 it 삽입, 지정 위치를 데이터로 정하고 싶으면 search()찾은 후 ...
//빈 자리인 경우 호출시 지정하면 그만 ex) insert(x->right, it)
//기존 노드에 덮어쓰는 경우 희생자를를 반환해서 적절한 조처를 할 수 있게 한다. 희생자를 처리하는 것은 힙 등에서 다룸, 따라서 여기선 배제
node *insert(node *here, node *it) {
	if (here == NULL) { //빈 곳이면 그냥 넣는다.
		here = it;
		return NULL;
	}
 	else {	
		node* victim;
		victim = here;  //우선 희생자를 복사한다. 트리일 수 있다.
		*here = *it;    // *를 붙여서 내용을 복사한다. 
		return victim;  //희생자를 반환해서 적절한 조처를 할 수 있게 한다.
	}
}

//지정한 노드를 제거, 제거한 노드(자식 포함)를 반환해서 적절한 조처를 할 수 있게 한다.
//부모를 찾아서 제거
//root는 삭제불가 
node *delete(node *root, node *it, char direction) {
	node *parent = search_parent(root, it);
		if (parent == NULL) {
		printf("삭제 불가!\n");
		return NULL;
	} else {
	    if (direction == 'l') {parent->left = NULL; free(parent->left);  return it;}
	    else if (direction == 'r') {parent->right = NULL; free(parent->right); return it;}
	    else return NULL;
	}
}

void main() {
	
	int level;
	
    node* A = make_node(NULL, 'A', NULL);
    node* B = make_node(NULL, 'B', NULL);
    node* C = make_node(NULL, 'C', NULL);
    node* D = make_node(NULL, 'D', NULL);
    node* E = make_node(NULL, 'E', NULL);
    node* _divide = make_node(B, '/', C);    
    node* _minus = make_node(A, '-', _divide);
    node* _star = make_node(D, '*', E);
    
    node* root = make_node(_minus, '-', _star);  

    printf("%d\n", get_node_num(root)); 
    printf("%d\n", get_leaf_num(root)); 
    printf("%d\n", get_level(root)); 

/// print Tree test
    print2D(root);

///
    preorder(root);
    printf("\n");
    inorder(root);
    printf("\n");
    postorder(root);
    printf("\n");

/// search test    
    node* sub = search(root, '*');
    printf("%p\n", sub);
    print2D(sub);    printf("\n");   
/// new tree    
    node* F = make_node(NULL, 'F', NULL);
    node* G = make_node(NULL, 'G', NULL);
    node* _plus = make_node(F, '+', G);
    print2D(_plus);    printf("\n");   
/// insert test    
    node* v = insert(E, _plus);
    print2D(v);    printf("\n");      
    print2D(root);    printf("\n"); 
/// search test 4 inserted tree   
    node* _search = search(root, '+');
    print2D(_search);    printf("\n==================\n");    
/// search_parent test   
    node* plink1 = search_parent(root, A);
    print2D(plink1);    printf("\n");
/// delete test
    node* deleted = delete(root, _plus, 'r');
    print2D(root);    printf("\n");  
   
}
