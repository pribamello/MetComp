#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double media(int ptsort, double min, double max, double (*f)(double x), double *eps);
double f(double x);

int main(){
int ptsort;
double min=0, max = 1./3, resposta;
double n = 0; //Local a ser guardado valor do ponteiro
double *eps = NULL;
eps = &n;

printf("Escolha o n'umero de pontos sorteados: ");
scanf("%d",&ptsort);

resposta =  media(ptsort,min,max,f,eps);
printf("Utilizando o m'etodo de amostragem por relevancia obtemos:\n Integral = %lf\nErro associado = %lf\n",resposta,*eps);
return 0;
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

double f(double x){
    return pow(3*x,1./3);//Retorna a ra'iz c'ubica de 3*x
}
