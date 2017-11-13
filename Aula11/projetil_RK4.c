#include<stdlib.h>
#include<stdio.h>
#include<stddef.h>
#include<math.h>


//#define B_m  4.e-3
#define B_m 0

void dsdt(double t, const double *s, double *fk);
void euler(double *y, double x0, double h, int N, void (*dydx)(double x, const double *y, double *f));

int main(){
double h = 1.e-4, t = 0;
int N = 4;
double s[4] = {0};
//FILE *resultado = fopen("projetil_RK4.dat","w");
FILE *resultado = fopen("projetil_RK4_Bm0.dat","w");

/*     s[0] = x
	   s[1] = Vx
	   s[2] = y
	   s[3] = Vy */
//Condi'c~oes iniciais:
s[0] = 0;
s[1] = 700./sqrt(2);
s[2] = 0;
s[3] = 700./sqrt(2);


while (s[2] >= 0){
    fprintf(resultado,"%.6lf  %.6lf     %.6lf\n", s[0], s[2], t);
    RungeKutta4(s,t,h,N,dsdt);
    t = t + h;

}

}


void dsdt(double t, const double *s, double *fk){
    double g = 9.87;

    //atualiza dx/dt = vx, dy/dt = vy
    fk[0] = s[1]; //Atualiza x
    fk[2] = s[3]; //Atualiza y

    //atualiza d(vx)/dt, d(vy)/dt
    fk[1] =  -B_m*sqrt(s[0]*s[0] + s[2]*s[2])*s[1];
    fk[3] =  -B_m*sqrt(s[0]*s[0] + s[2]*s[2])*s[3] - g;

}


void RungeKutta4(double *y, double x0, double h, int N,
	void (*dydx)(double x, const double *y, double *f)  )
{
    int i;

    double * f0 = NULL;
    double * f1 = NULL;
    double * f2 = NULL;
    double * f3 = NULL;

    double * yTemp = NULL;

    f0 = (double *) malloc( N * sizeof(double) );
    f1 = (double *) malloc( N * sizeof(double) );
    f2 = (double *) malloc( N * sizeof(double) );
    f3 = (double *) malloc( N * sizeof(double) );

    yTemp = (double *) malloc( N * sizeof(double) );

    if ( f0 == NULL || f1 == NULL || f2 == NULL ||
	 f3 == NULL || yTemp == NULL ) {
      printf ("Nao foi possivel alocar memoria");
      return;
    }

    dydx( x0, y, f0);

    for (i=0;i<N;++i) yTemp[i] = y[i] + h*f0[i]/2;
    dydx( x0+h/2, yTemp, f1);

    for (i=0;i<N;++i) yTemp[i] = y[i] + h*f1[i]/2;
    dydx( x0+h/2, yTemp, f2);

    for (i=0;i<N;++i) yTemp[i] = y[i] + h*f2[i];
    dydx( x0+h, yTemp, f3);

    for (i=0;i<N;++i) y[i] = y[i] + h*(f0[i]+2*f1[i]+2*f2[i]+f3[i])/6;

    free(f0);
    free(f1);
    free(f2);
    free(f3);
    free(yTemp);
    return;
}


