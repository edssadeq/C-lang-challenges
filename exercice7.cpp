#include <stdio.h>
#include <stdlib.h>

int main(){
	int nombre ;
	printf("entrez un nombre plus de 1 pour afficher ses diviseurs :");
	scanf("%d",&nombre);
	while(nombre <= 1){
		printf("le nombre entre est moins de 1,s il vous plaiez ! entrez un nombre pour afficher ses diviseurs :");
	scanf("%d",&nombre);
	}
	printf("\n les diviseurs de votre nombre %d sont :",nombre);
	
	for (int i=1 ; i<= nombre ;i++){
		if((nombre % i) == 0){
			printf("\n\t%d",i);
		}
	}
	
	
	return 0;
}
