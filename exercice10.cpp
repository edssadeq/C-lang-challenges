#include <stdio.h>
#include <stdlib.h>

int main(){
	int op1 , op2,resultat;
	char operateur ;
	printf("entrez votre operation (exp:1+5) : ");
	scanf("%d %c %d",&op1,&operateur,&op2);
	if(operateur == '+'){
		resultat = op1+op2;
	}
	else if(operateur == '-'){
		resultat = op1-op2;
	}
	else if(operateur == '/'){
		resultat = op1/op2;
	}
	else if(operateur == '*'){
		resultat = op1*op2;
	}
	else if(operateur == '%'){
		resultat = op1%op2;
	}
	else{
		printf("invalide");
	}
	printf("resultat : %d",resultat);
	return 0;
}
