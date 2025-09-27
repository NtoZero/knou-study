#include <stdio.h>
#include <stdlib.h>
 
typedef struct BSTnode{
	struct BSTnode* left;
	char key;			//탐색용 키 
	char content[10];	//긴 문장이나 그림... 
	struct BSTnode* right;
} BSTnode;

/*학생이 직접 작성하도록... 
void preorderBST(BSTnode* root) {

}
*/

void inorderBST(BSTnode* root) {
    if (root != NULL) {
        inorderBST(root->left);
        printf("%c ", root->key);
        inorderBST(root->right);
    }
}

/*학생이 직접 작성하도록... 
void postorderBST(BSTnode* root) {

}
*/

BSTnode* searchBST(BSTnode* root, char key) {
    if(root == NULL){  
        printf("Error : 값을 찾을 수 없습니다\n");
        return root;
    }
    
    if(key == root->key) {
        return root;
    }
    else if(key < root->key) {
        searchBST(root->left, key);
    }
    else if(key > root->key) {
        searchBST(root->right, key);
    }
    
}
 
BSTnode* insertBST(BSTnode* root, char key) {
    BSTnode* ptr;
    BSTnode* newNode = (BSTnode*)malloc(sizeof(BSTnode));
    newNode->key = key;
    newNode->left = newNode->right = NULL; 
    
    if(root == NULL) { 
        root = newNode;
        return root;
    }
    
    ptr = root; 
    
    while(ptr){
        if(key == ptr->key){ 
            printf("Error : 중복값은 허용되지 않습니다!\n");
            return root;
        }else if(key < ptr->key){
            if(ptr->left == NULL){ 
                ptr->left = newNode;
                return root;
            }else{ 
                ptr= ptr->left;
            }
        }else{ 
            if(ptr->right == NULL){
                ptr->right = newNode;
                return root;
            }else{ 
                ptr = ptr->right;
            }
        }
    }
    
}
 
BSTnode* deleteBST(BSTnode* root, int key){
    BSTnode* del = NULL;    
    BSTnode* parent = NULL;
    BSTnode* successor = NULL; 
    BSTnode* predecessor = NULL; 
    BSTnode* child = NULL; 
    
    del= root;
    while(del != NULL){//삭제할 노드 탐색 
        if(key == del->key){
            break;
        }
        parent = del;
        if(key < del->key){
            del = del->left;
        }else{
            del = del->right;
        }
    }
    
    if(del == NULL){
        printf("Error : 존재하지 않는 키\n");
        return root;
    }
    
    if(del->left == NULL && del->right == NULL){//자식 노드가 없는 경우 
        if(parent != NULL){//부모노드가 있는 경우 
            if(parent->left == del){ 
                parent->left = NULL;
            }else{ 
                parent->right = NULL;
            }
        }else{ 
            root = NULL;
        } 
    }else if(del->left != NULL && del->right != NULL){//자식 노드가 2개인 경우 
        predecessor = del;
        successor = del->left;
        
        while(successor->right != NULL){
            predecessor = successor;
            successor = successor->right;
        }
        
        if(predecessor->left == successor){
            predecessor->left = successor->left;
        }else{
            predecessor->right = successor->left;
        }
         
        
        del->key = successor->key;
        del = successor;
 
    }else{//자식 노드가 1개인 경우 
        if(del->left != NULL){
            child = del->left;
        }else{
            child = del->right;
        }
        
        if(parent != NULL){//부모가 있는 경우 
            if(parent->left == del){
                parent->left = child;
            }else{
                parent->right = child;
            }
        }else{
            root = child;
        }
    }
    
    free(del); 
    return root; 
}
 
// This code is contributed by rathbhupendra
void print2DUtil(BSTnode* root, int space) {
	
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
    printf("%c\n",root->key);
 
    // Process left child
    print2DUtil(root->left, space);
}

// This code is contributed by rathbhupendra 
// Wrapper over print2DUtil()
void print2D(BSTnode* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}
 
int main(){
	
	//교재 1.3절 예제  
    BSTnode* root = NULL;
    BSTnode* ptr = NULL;
    root = insertBST(root, 'C');
    root = insertBST(root, 'B');
    root = insertBST(root, 'E');
    root = insertBST(root, 'D');

    print2D(root);
    printf("\n");
    
    inorderBST(root);
    printf("\n");
	    
    root = insertBST(root, 'A');
    root = insertBST(root, 'F');

    print2D(root);
    printf("\n");
    
    ptr = searchBST(root, 'E');
    printf("%c\n", ptr->key);
    
    root = deleteBST(root,'E');
    ptr = searchBST(root, 'E');

    print2D(root);
    printf("\n");
	
	return 0;
} 
