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

//���� Ʈ���� ��� ����
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

//���� Ʈ���� �� ��� ����
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

//���� Ʈ���� ���� 
int get_level(node *root) {
	int left = 1, right = 1 ; //level ���ǿ� ���� 0/1
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

//���� �ָ� ����� �ּ� ��ȯ ��, NULL �ƴϸ� ...
//�������� ���� ã�� �� 
node* search(node *root, char data) {
    
    node* ptr = NULL;;
	if (root == NULL) {
	    return NULL;
	} else if (root->data == data) {
		printf("ã�� %C\n", root->data);
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

//�θ� ���
//root�� �θ� �����Ƿ� ��󿡼� ����
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

//������ ��ġ here�� ��� it ����, ���� ��ġ�� �����ͷ� ���ϰ� ������ search()ã�� �� ...
//�� �ڸ��� ��� ȣ��� �����ϸ� �׸� ex) insert(x->right, it)
//���� ��忡 ����� ��� ����ڸ��� ��ȯ�ؼ� ������ ��ó�� �� �� �ְ� �Ѵ�. ����ڸ� ó���ϴ� ���� �� ��� �ٷ�, ���� ���⼱ ����
node *insert(node *here, node *it) {
	if (here == NULL) { //�� ���̸� �׳� �ִ´�.
		here = it;
		return NULL;
	}
 	else {	
		node* victim;
		victim = here;  //�켱 ����ڸ� �����Ѵ�. Ʈ���� �� �ִ�.
		*here = *it;    // *�� �ٿ��� ������ �����Ѵ�. 
		return victim;  //����ڸ� ��ȯ�ؼ� ������ ��ó�� �� �� �ְ� �Ѵ�.
	}
}

//������ ��带 ����, ������ ���(�ڽ� ����)�� ��ȯ�ؼ� ������ ��ó�� �� �� �ְ� �Ѵ�.
//�θ� ã�Ƽ� ����
//root�� �����Ұ� 
node *delete(node *root, node *it, char direction) {
	node *parent = search_parent(root, it);
		if (parent == NULL) {
		printf("���� �Ұ�!\n");
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
