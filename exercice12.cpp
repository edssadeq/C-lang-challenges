#include <stdio.h>
#include <stdlib.h>

int main(){
	int t[] = {1,6,9,0,5,8,6,0};
	printf("les index des nombres nulles : ");
	for (int i=0 ;  i< 8 ; i++){
		if(t[i] == 0){
			printf("%d , ",i);
		}
	}
	
	return 0;
}
