#include<stdio.h>
#include<Math.h>

//calculer l'integrale de sqrt(x) dans [0,1] avec n le nombre des rectangles.
double f_racine(double);
double f_carre(double);
double f_exp(double );
double f_2deg(double);
//(x^2+sqrt(x))^2
double f_f1(double);
double integrer(double (*)(double), double , double , int);


int main(){
	
	//**************************** Tests ********************
	//calculer l'integrale de sqrt(x) dans [0,1] avec 4 le nombre des rectangles.
	double surface = integrer(f_racine,0,1,4); //wait for : 0.656526264792571
	printf("%f\n", surface);
	
	//calculer l'integrale de x^2 dans [-1,1] avec 4 le nombre des rectangles.
	double surface3 = integrer(f_carre,-1,1,4); //wait for :0.666666666666667
	printf("%f\n", surface3);
	
	//calculer l'integrale de exp(x) dans [0,1] avec 4 le nombre des rectangles.
	double surface4 = integrer(f_exp,0,1,4); // wait for :1.71831884192175
	printf("%f\n", surface4);
	
	/*
	//calculer l'integrale de sqrt(x) dans [0,8] avec 4 le nombre des rectangles.
	double surface2 = integrer(f_racine,0,8,4); //wait for : 14.8554935635809
	printf("%f\n", surface2);
	
	//calculer l'integrale de x^2 dans [0,1] avec 4 le nombre des rectangles.
	double surface3 = integrer(f_carre,-1,1,4); //wait for :0.333333333333333
	printf("%f\n", surface3);
	
	//calculer l'integrale de x^2 dans [-1,3] avec 4 le nombre des rectangles.
	double surface31 = integrer(f_carre,-1,3,4); //wait for :9.33333333333333
	printf("%f\n", surface31);
	
	//calculer l'integrale de exp(x) dans [0,1] avec 4 le nombre des rectangles.
	double surface4 = integrer(f_exp,0,1,4); // wait for :1.71831884192175
	printf("%f\n", surface4);
	
	//calculer l'integrale de x^2 +2x +1 dans [0,1] avec 4 le nombre des rectangles.
	double surface5 = integrer(f_2deg,0,1,4); // wait for :2.33333333333333
	printf("%f\n", surface5);
	
	//calculer l'integrale de x^2 +2x +1 dans [0,2] avec 6 le nombre des rectangles.
	double surface6 = integrer(f_2deg,0,2,6); // wait for :8.66666666666667
	printf("%f\n", surface6);
	
	//calculer l'integrale de (x^2+sqrt(x))^2 dans [0,1] avec 40 le nombre des rectangles.
	double surface7 = integrer(f_f1,0,1,80); // wait for :1.27142852905607
	printf("%f\n", surface7);
	
	
	//calculer l'integrale de x^2 dans [-1,3] avec 4 le nombre des rectangles.
	double surface32 = integrer(f_racine,1,5,6); //wait for : 6.78659375442496
	printf("%f\n", surface32);
	*/
	
	return 0;
}


double integrer(double (*f)(double), double a, double b, int n){
	if(n%2 != 0){
		printf("\n !!!!! le nombres des intervales doit etre pair .\n");
		return 0;
	}
	/*
	integral f(x) ~= ((b-a/n))/3 *(f(a)+4f(x1)+2f(x2)+.....+2f(xn-2)+4f(xn-1)+f(b)) 
	*/
	double h = ((b-a)/n);
	const int N = n+1; //nombres des x
	double intervales[N];
	
	double h_temp = a;
	for(int i=0; i< N; i++){
		intervales[i]= h_temp;
		h_temp = h_temp+h;	
	}
	
	/*
	printf("\n--------\n");
	for(int i=0; i< N; i++){
		printf("\n%f => %f \n ",	intervales[i], 2*((*f)(intervales[i])));
	}
	printf("\n--------\n");
	*/
	
	double temp = 0;
	temp = (*f)(intervales[0]) + (*f)(intervales[N-1]);
	
	for(int i=1; i< N-1; i++){
		if(i%2 == 0){
			temp = temp + (2*((*f)(intervales[i])));
		}
		else{
			temp = temp + (4*((*f)(intervales[i])));
		}

	}
	
	double surface = (h/3)*temp;

	return surface;
}


// les fonctions 

double f_racine(double x){
	return sqrt(x);
}

double f_carre(double x){
	return x*x;
}

double f_exp(double x){
	return exp(x);
}

//x^2 + 2x +1
double f_2deg(double x){
	return f_carre(x)+2*x+1;
}

//(x^2+sqrt(x))^2
double f_f1(double x){
	return (f_carre(x)+f_racine(x))*(f_carre(x)+f_racine(x));
}
