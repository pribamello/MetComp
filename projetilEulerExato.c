#include<stdlib.h>
#include<stdio.h>
#include<stddef.h>
#include<math.h>


#define g 9.87

int main(){
double x,y,v0,t;
double h = 1.e-4;
FILE *resultado = fopen("projetilEulerExato.dat","w");

t = 0;
v0 = 700/sqrt(2);
x = 0;
y = 0;

while(y >=0){
    fprintf(resultado,"%.6lf    %.6lf   %.6lf\n",x,y,t);
    t += h;
    x = v0*t;
    y = v0*t - g*t*t/2;
}
return 0;
}
