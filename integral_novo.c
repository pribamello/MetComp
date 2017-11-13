#include <stdio.h>
#include <math.h>

#define eps 1.e-6
#define kmax 50
#define xmin -2
#define xmax 2

double trapezio(double (*f)(double x), double a, double b, int *n);
double simpson(double (*f)(double x), double a, double b, int *n);
double f(double x);

int main(){
    double I;
    int n = 0;
    int *pn = NULL;

    pn = &n;
    I = trapezio(f,xmin,xmax,pn)/sqrt(2*M_PI);
    printf("Pelo metodo dos trapezios a integral vale aproximadamente %lf\n", I);
    printf("O numero de iteracoes usadas foi %d\n\n",*pn);

    *pn = 0;
    I = simpson(f,xmin,xmax,pn)/sqrt(2*M_PI);
    printf("Pelo metodo de simpson a integral vale aproximadamente %lf\n", I);
    printf("O numero de iteracoes usadas foi %d\n",*pn);

    return 0;
}

double f(double x){
    return exp(-0.5*x*x); // Funcao que sera integrada
}



double simpson(double (*f)(double x), double a, double b, int *n){
    double So, Sk = 0;
    double somaimp, somapar;
    int i, k = 1;

   while (fabs((Sk-So)/So) > eps && k < kmax){
        somaimp = 0;
        somapar = 0;
        So = Sk; // So e' S(k - 1)
        for (i = 1; i <= (pow(2,k)-1); i += 2) somaimp += f(a + i*(b - a)/pow(2.,k));
        for (i = 2; i <= (pow(2,k)-2); i += 2) somapar += f(a + i*(b - a)/pow(2.,k));
        Sk = (b - a)*(f(a) + 4*somaimp + 2*somapar + f(b))/(3*pow(2.,k));
        k++;
        *n += 1;
    }

    return Sk;
}


double trapezio(double (*f)(double x), double a, double b, int *n){
    double To, Tk;
    double soma;
    int i, k = 1;
    Tk = 0.5*(f(a) - f(b))*(b - a);

    while (fabs((Tk-To)/To) > eps && k < kmax){
        soma = 0; // Resetando variavel soma
        To = Tk; // To e' T(k - 1), caso o loop se repita o ultimo Tk vira To
        for (i = 1 ; i <= (pow(2,k)-1) ; i += 2) soma += f(a + i*(b - a)/pow(2.,k));
        Tk = 0.5*To + soma*(b - a)/pow(2.,k);
        k++;
        *n += 1;
    }

    return Tk;
}
