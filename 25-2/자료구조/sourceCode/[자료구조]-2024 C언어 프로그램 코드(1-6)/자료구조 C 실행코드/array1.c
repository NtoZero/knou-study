//#pragma warning(disable:4996)

#include <stdio.h>
#define array_size 5     // 배열의 사이즈를 미리 정함 

int a[array_size];   //배열을 전역변수로 정의 

void arrayCreate( ){  // 배열의 초기값 입력 함수 
	int i;
	for(i=0; i<array_size; i++){
		printf("배열의 초기값을 입력하세요. a[%d] : ",i);
		scanf("%d",&a[i]);
	}
	printf("배열의 초기값이 설정되었습니다.\n\n");
}

void retrieve() {  // 사용자가 입력한 배열 위치값을 알려주는 함수 
	int s;
	
	printf("값을 알고자 하는 배열 위치값을 입력하세요(0~4) : ");
	scanf("%d", &s);
	
	if(s>=0 && s<array_size) {
		printf("a[%d] 번째 위치에 있는 값은 %d 입니다.\n\n", s,a[s]);

	}
	else { 
		printf("Error \n");
	}
}

void arraySearch(){  // 사용자가 찾고자 하는 값을 검색해주는 함수 
	int i;
	int result=0;
	int value=0;
	printf("입력한 값 중에서 검색하고자 하는 값을 입력하세요 :  ");
	
	scanf("%d", &value);
	
	for(i=0; i<array_size; i++){
		if(a[i]==value) {
			printf("배열 a[%d]번째에 %d 값이 검색되었습니다.\n", i, value);
			result=1;
		}
	}
	if(result==0)printf("찾고자 하는 값이 없습니다.\n");
}

void main() {  // 메인 함수 
	
	printf("이 프로그램에서 배열의 크기는 %d 입니다. \n",array_size);
    
	arrayCreate(); 
	retrieve();
	arraySearch();
	
	printf("The End.\n");	
}	

