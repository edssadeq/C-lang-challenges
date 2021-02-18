/*************************************************************/
/*********************** TP 2 Partie 1 ***********************/
/*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DERGRE_MAX 1000

typedef struct polynome{
	int degre;
	float *coefficients;
} Poly; 


Poly saisirPoly();
void affichercoefficients(Poly poly);
void afficherPolynome(Poly poly);
void evaluerX(Poly poly);
float evaluerXReturn(Poly poly, float x);
float Eval_iterative(Poly p, float x );
Poly addition(Poly poly1, Poly poly2);
void changerSigne(Poly *poly1);
Poly soustraction(Poly poly1, Poly poly2);
void comparer(Poly poly1, Poly poly2);
//Poly direvePolynom(Poly poly1);
void direvePolynom(Poly *polyDer, Poly poly1);
void plotPolynom(Poly poly, float a, float b);

//partie 2
float racinePoly(Poly poly1, float x0, float testDarret);
float absFloat(float N);

//**********************************| start Main App |**********************************
int main(){
	Poly poly1, poly2, polyRes;
	poly1= saisirPoly();
	afficherPolynome(poly1);
	printf("\n\n");
	//affichercoefficients(poly1);
	//changerSigne(&poly1);
	afficherPolynome(poly1);
	printf("\n\n");
	
	//direvePolynom(&polyRes, poly1);
	afficherPolynome(poly1);
	
	racinePoly(poly1, 1.2, 0.001);
	
	//printf("\n\n");
	//printf("%.2f \n", Eval_iterative(poly1,2));
	//evaluerX(poly1);
	//printf("\n\n");
	//printf("%.2f \n", evaluerXReturn(poly1,2));
	//afficherPolynome(polyRes);
	//plotPolynom(poly1,1,10);
	
	//plotPolynom(poly1,1.0,10.0);
	
	
	
	//printf("\n----------\nracine  = %f\n\n", racinePoly(poly1, 1, 0.0001));

	
	
	return 0;
}
//**********************************| end Main App |**********************************
// fonctions 

Poly saisirPoly(){
	Poly poly1 = {0, NULL};
	int i = 0, coefficientsNuls=0;
	printf("donnez le degre de polynome :");
	scanf("%d", &poly1.degre);
	poly1.coefficients = (float*)malloc(sizeof(float) * poly1.degre+1);// memoiry allocation
	
	for(; i<= poly1.degre ; i++){
		printf("\n coefficient(%d)= ", i);
		scanf("%f", &poly1.coefficients[i]);
		if(poly1.coefficients[i] == 0){
			printf("\n \t enterz le nombre des coefficients nuls [tappez 0 si non](rest %d):",(poly1.degre - i));
			scanf("%d", &coefficientsNuls);
			
			//j=i;
			for(int j=i; j<= (i+coefficientsNuls) && j< poly1.degre ; j++){
				poly1.coefficients[j] = 0;
			}
			i = i+coefficientsNuls;
		}
	}
	return poly1;
}

void affichercoefficients(Poly poly){
	int i;
	printf("\t degre : %d \n",poly.degre);
	printf("\t coefficients : [");
	for(i=0 ; i<=poly.degre; i++){
		if(i % 4 == 0)
			printf("\n");
		printf("\t \t %.2f ,",poly.coefficients[i]);
	}
	printf("]\n\n");
}

void afficherPolynome(Poly poly){
	int i;
	printf("\n\t_________________________________\n\n");
	printf("\t P(x)=");
	for(i=0 ; i<=poly.degre; i++){
		if(poly.coefficients[i] != 0){
			if(poly.coefficients[i]> 0)
				printf("+");
			printf("%.2f*(X^%d)",poly.coefficients[i], i);
		}
			
	}
	printf("\n\n\t_________________________________\n");
}

void evaluerX(Poly poly){
	int i=0;
	double x;
	double Px = 0;
	printf("\n\n_____________________________\n");
	printf("\n enter la valeur de X =");
	scanf("%lf", &x);
	
	for(i ; i<=poly.degre; i++){
		Px += 	poly.coefficients[i]*(pow(x, i));
	}
	
	printf("P(%.2f) = %.2f\n", x, Px);		
}

float evaluerXReturn(Poly poly, float x){
	int i=0;
	double Px = 0;
	for(i ; i<=poly.degre; i++){
		Px += 	poly.coefficients[i]*(pow(x, i));
	}
	
	return Px;		
}

float Eval_iterative(Poly p, float x ){
	float res = p.coefficients[0];
	for (int i=1; i<= p.degre; i++){
		res = (res*x) + p.coefficients[i];
	}
	printf("| %f | %f |\n", x, res);
	return res;
}


Poly addition(Poly poly1, Poly poly2){
	Poly polyRes;
	if(poly1.degre == poly2.degre){
		int i=0;
		polyRes.degre = poly2.degre;
		polyRes.coefficients = (float*)malloc(sizeof(float)*poly2.degre);
		for(i ; i<=polyRes.degre; i++){
			polyRes.coefficients[i] = 	poly1.coefficients[i]+ poly2.coefficients[i];
		}
	}
	else if(poly1.degre > poly2.degre){
		int i=0, j;
		int restCoefficients = poly1.degre - poly2.degre;
		polyRes.degre = poly1.degre;
		polyRes.coefficients = (float*)malloc(sizeof(float)*poly1.degre);
		for(i ; i<=poly2.degre; i++){
			polyRes.coefficients[i] = 	poly1.coefficients[i]+ poly2.coefficients[i];
		}
		for(j=poly2.degre+1; j<= poly1.degre; j++){
			polyRes.coefficients[j] = poly1.coefficients[j];
		}
		
	}
	else{
		int i=0, j;
		int restCoefficients = poly2.degre - poly1.degre;
		polyRes.degre = poly2.degre;
		polyRes.coefficients = (float*)malloc(sizeof(float)*poly2.degre);
		for(i ; i<=polyRes.degre; i++){
			polyRes.coefficients[i] = 	poly1.coefficients[i]+ poly2.coefficients[i];
		}
		for(j=poly1.degre+1; j<= poly2.degre; j++){
			polyRes.coefficients[j] = poly2.coefficients[j];
		}
	}
	//printf(" le polynome resultant :\n");
	//afficherPolynome(polyRes);
	return polyRes;
}



void changerSigne(Poly *poly1){
	int i=0;
	for(i ; i<= poly1->degre ; i++){
		poly1->coefficients[i] *= (-1);
	}
}


Poly soustraction(Poly poly1, Poly poly2){
	Poly polyRes;
	changerSigne(&poly2);
	polyRes = addition(poly1, poly2);
	//printf(" le polynome resultant :\n");
	//afficherPolynome(polyRes);
	return polyRes;
}



/*
void comparer(Poly poly1, Poly poly2){
	int i=0;
	int sumCoefficients;
	Poly polyRes;
	polyRes = soustraction(poly1, poly2);
	for(i ; i<= polyRes.degre ; i++){
		sumCoefficients= polyRes.coefficients[i] += 0;
		
	}
	if(sumCoefficients == 0)
	{
		printf("poly1 et poly2 sont egaux.");
	}
	else{
		printf("poly1 et poly2 ne sont pas egaux.");
	}
}
*/
void comparer(Poly poly1, Poly poly2){
	int i=0;
	Poly polyRes;
	polyRes = soustraction(poly1, poly2);
	for(i ; i<= polyRes.degre ; i++){
		if(polyRes.coefficients[i] !=0){
			printf("poly1 et poly2 ne sont pas egaux.");
			return;
		}
	}
	printf("poly1 et poly2 sont egaux.");
}

/*
Poly direvePolynom(Poly poly1){
	int i=0;
	int j=0;
	Poly polyRes = {0, NULL};
	polyRes.degre = poly1.degre-1;
	polyRes.coefficients = (float*)malloc(sizeof(float) * polyRes.degre);// memoiry allocation
	
	for(i ; i<= polyRes.degre ; i++){
		j=i+1;
		polyRes.coefficients[i] = (poly1.coefficients[j]*(float)(j));
	}
	return polyRes;
}
*/


void direvePolynom(Poly *polyDer, Poly poly1){
	int i=0;
	int j=0;
	(*polyDer).degre = poly1.degre-1;
	(*polyDer).coefficients = (float*)malloc(sizeof(float) * ((*polyDer).degre+1));// memoiry allocation
	
	for(i ; i<= (*polyDer).degre ; i++){
		j=i+1;
		(*polyDer).coefficients[i] = (poly1.coefficients[j]*(float)(j));
	}
}


void plotPolynom(Poly poly, float a, float b){
	//writing values to text file
	FILE *fp=NULL;
	fp=fopen("curvePoly.txt","w");

  	for(float i=a; i<= b; i=i+(i/3)){
  		fprintf(fp,"%lf\t %lf\n", i, evaluerXReturn(poly, i));
	}
	
	printf("\n\nCalculation termenated!\nLoad the file to GNUPLOT to see the curve .\n\n");
  	/*
  	this code generats a txt file contians X and Evaluation of X with polynomial passed.
  	tape "plot 'path\to\curbePoly.txt' w l" into the GNUPLOT app to see the curve.
  	*/
}



/*************************************************************/
/***************  TP 2 Partie 2 header ***********************/
/*************************************************************/


float racinePoly(Poly poly1, float x0, float testDarret){
	//calcul de racine par la méthode de Newton-Raphson
	Poly polyDerive;
	direvePolynom(&polyDerive, poly1);
	float racine = 0;
	float xk=0; //xk
	float xj=0; //xk-1
	int iterationsCounter = 0;
	printf("POL : ");
	afficherPolynome(poly1);
	printf("RACINE : ");
	afficherPolynome(polyDerive);
	do{
		xk = x0 - (evaluerXReturn(poly1, x0)/evaluerXReturn(polyDerive, x0));
		xj = x0;
		x0 = xk;
		
		printf("\n\n k = %d \t xk = %f \t f(xk) = %f \n", iterationsCounter, xk , evaluerXReturn(poly1, xk));
		
		iterationsCounter++;
	}while(absFloat(absFloat(xk) - absFloat(xj)) > testDarret);  
	racine = xj;
	return racine;
}


float absFloat(float N){
	if( N <0 ){
		return (-1)*N;
	}
	return N;
}

