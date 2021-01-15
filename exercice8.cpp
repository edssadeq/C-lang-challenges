#include <stdio.h>
#include <stdlib.h>

int main(){
	int a,b,max,min,quotient,rest ;
	int min1;
	printf("entrez a , b :");
	scanf("%d%d",&a,&b);
	//test positive ?
	while( a<=0 || b <=0){
		printf("a ou b n\'est pas positif ! entrez a , b :");
		scanf("%d%d",&a,&b);
	}
	
	if(b>a){
		max = b;
		min = a;
	}
	else{
		max = a;
		min = b;
	}
	min1 = min;
	printf("\n %d > %d",max,min1);
	
	
	
	for (min1 ; min1 <= max ;min1+=min){
		quotient++;
		rest = max - min1 ;
	}
	
	printf("\n %d / %d ==> \n\t quotient :%d \n\t rest :%d",max,min,quotient,rest);
	return 0;
}
