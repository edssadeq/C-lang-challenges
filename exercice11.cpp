#include <stdio.h>
#include <stdlib.h>

int main(){
	int i;
	int *p;
	
	i= 3;
	p = &i;
	
	printf(" i = %d ",i);
	
	*p = 1344;
	
	printf("\n i = %d ",i);
	return 0;
}
