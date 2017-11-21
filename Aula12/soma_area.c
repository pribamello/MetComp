#include <stdio.h>
#include <stdlib.h>

void main(){
FILE *ler = fopen("rejeicao_pol3.dat","r");
double soma = 0;
double p = 0;
int i = 1;

while(fscanf(ler,"%lf",&p) != EOF){
    if (i % 2 == 0) soma += p*3./20;
    i++;
}
printf("%lf",soma);
}
