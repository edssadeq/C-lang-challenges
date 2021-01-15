#include <stdio.h>
#include <stdlib.h>
void affiche_matrice(const int mat[5][5] );
int main(){
	//matrice 
	
	int iMat[5][5] = {{1,3,7,76,87},{15,32,7,76,857},{1,53,75,76,857},{15,3,75,76,87},{51,35,7,756,87}};
	affiche_matrice(iMat);
	
	return 0;
}

void affiche_matrice(const int mat[5][5] ){
	for (int i=0 ; i<5 ;i++){
		for (int j=0 ; j<5 ;j++){
			printf("%d ",mat[i][j]);
			
		}
		printf("\n");
	}
}
