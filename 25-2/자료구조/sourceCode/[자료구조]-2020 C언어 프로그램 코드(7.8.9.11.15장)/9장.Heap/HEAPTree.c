#include <stdio.h> 
#include <stdlib.h>
#define MAX_SIZE 100
 
typedef struct heap{ 
    int heap[MAX_SIZE];     
    int size;
}heap;
 
 
void min_heapInsert(heap* h, int data){
    int i;
    i = ++(h->size);
    
    //������ ��ġ�� ã�� ������ �ݺ�  
    while( (i != 1) && (data < h->heap[i/2]) ){
        h->heap[i] = h->heap[i/2]; 
        i /= 2;
    }
    
    h->heap[i] = data; 
}
 
int min_heapDelete(heap* h){
    int parent, child;
    int data, temp;
    
    data = h->heap[1];
    temp = h->heap[(h->size)--];
    parent = 1;     
    child = 2; 
    
    while(child <= h->size){
        //�ڽ� ��� ����
        if( (child < h->size) && ((h->heap[child]) > h->heap[child+1])){
            child++;
        }
        
         if(temp <= h->heap[child]){
            break;
        } 
        
        //��� ��ȯ
        h->heap[parent] = h->heap[child];
        
        parent = child;
        child *= 2;
    }
    
    h->heap[parent] = temp;
    
    return data;    
    
} 
 
 
int main(){
	int data;
    heap min_heap;

    min_heapInsert(&min_heap, 1);
    min_heapInsert(&min_heap, 15);
    min_heapInsert(&min_heap, 5);
    min_heapInsert(&min_heap, 20);
    min_heapInsert(&min_heap, 16);
    min_heapInsert(&min_heap, 10);
    min_heapInsert(&min_heap, 19);
    min_heapInsert(&min_heap, 25);
    min_heapInsert(&min_heap, 30);
    min_heapInsert(&min_heap, 17);
    min_heapInsert(&min_heap, 18);
    min_heapInsert(&min_heap, 12);
    min_heapInsert(&min_heap, 23);
    
    //���ʷ� �����ϸ� �ڵ� ����! 
    while(min_heap.size > 0){
        data = min_heapDelete(&min_heap);
        printf("%d ", data);
    }
        
    return 0;
} 
