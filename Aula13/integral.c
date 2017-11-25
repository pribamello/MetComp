#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define kmax 100

double hitmiss(int ptsort, double min, double max, double H, double (*f)(double x));
double f(double x);
double media(int ptsort, double min, double max, double (*f)(double x), double *eps);
double trapezio(double (*f)(double x), double a, double b, double *eps);

int main(){

int ptsort; //Número de pontos sorteados, é lido do teclado
double a = 0, b = 1., H = 1., n = 0 ;
double areamedia = 0, areahitmiss = 0, areatrapezio = 0;
double *eps = NULL;
eps = &n;

printf("Escolha o n'umero de pontos sorteados: ");
scanf("%d",&ptsort);

areahitmiss = hitmiss(ptsort,a,b,H,f);
printf("Pelo m'etodo hitmiss: %lf\n",areahitmiss);
areamedia = media(ptsort,a,b,f,eps);
printf("Pelo m'etodo das m'edias a 'area 'e %lf e o seu erro associado 'e %lf\n",areamedia,*eps);
areatrapezio = trapezio(f,a,b,eps);
printf("Pelo m'etodo dos trap'ezios 'e: %lf\n",areatrapezio);
//printf("'Area obtida: %lf\n Diferen'ca entre areas: %lf\n", area, 0.25 - area);
return 0;
}


double hitmiss(int ptsort, double min_x, double max_x, double H_y, double (*f)(double x))
{
	long fseed = -424242;
	int total = 0, acertos = 0;
	double areatotal = 0;
	double x=0, y=0;

	areatotal = (max_x-min_x)*H_y;
	srand(fseed);

	while(total < ptsort)
		{
		y = H_y*rand()/RAND_MAX;
		x = min_x + (max_x-min_x)*((double)rand())/RAND_MAX;
		if(y <= f(x)) acertos++;
		total++;
		//printf("%d			%d",acertos,total);
		}
	//printf("Número de sorteios = %d\n",total);
	return ((double) acertos/total ) * areatotal;
}

double media(int ptsort, double min, double max, double (*f)(double x), double *eps)
{
	long fseed = -424242;
	double sum1 = 0, sum2 = 0;
	double x = 0;
	int i = 0;

	srand(fseed);
	while(i<ptsort){
		x = min + (max-min)*((double)rand()/RAND_MAX);
		sum1 += f(x);
		sum2 += f(x)*f(x);
		i++;
	}

	*eps = (max - min)*sqrt(sum2/ptsort - sum1*sum1/(ptsort*ptsort))/sqrt(ptsort);
	//printf("O erro obtido é pelo método das médias é: %lf\n", *eps);
	return ((max - min)/ptsort)*sum1;
}

double trapezio(double (*f)(double x), double a, double b, double *eps){
    double To, Tk;
    double soma;
    int i, k = 1;
    Tk = 0.5*(f(a) - f(b))*(b - a);

    while (fabs((Tk-To)/To) > *eps && k < kmax){
        soma = 0; // Resetando variavel soma
        To = Tk; // To e' T(k - 1), caso o loop se repita o ultimo Tk vira To
        for (i = 1 ; i <= (pow(2,k)-1) ; i += 2) soma += f(a + i*(b - a)/pow(2.,k));
        Tk = 0.5*To + soma*(b - a)/pow(2.,k);
        k++;
    }

	 printf("Foram realizadas %d iterac~oes no m'etodo dos trap'ezios\n 	", k);
    return Tk;
}


double f(double x){
	return x*x*x;
}
