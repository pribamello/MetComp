#include<stdlib.h>
#include<stdio.h>
#include<stddef.h>
#include<math.h>


#define B_m  4.e-5
//#define B_m 0

void dsdt(double t, const double *s, double *fk);
void euler(double *y, double x0, double h, int N, void (*dydx)(double x, const double *y, double *f));

int main(){
double h = 1.e-4, t = 0;
int N = 4;
double s[4] = {0};
FILE *resultado = fopen("projetilEuler.dat","w");
//FILE *resultado = fopen("projetilEuler_Bm0.dat","w");

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
    euler(s,t,h,N,dsdt);
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


void euler(double *S, double t, double h, int N, void ((*dydx)(double t, const double *S, double *f))){
        int i;
        double * f0 = NULL;
        f0 = (double *) malloc(N * sizeof(double) );

        ////////////////////////////////
        if ( f0 == NULL ) {
                printf ("Nao foi possivel alocar memoria");
                return;
        }
        ////////////////////////////////

        dydx (t,S,f0);

        for (i=0; i<N; ++i){
                S[i] = S[i]+ h*f0[i];
        }

free(f0);
}
