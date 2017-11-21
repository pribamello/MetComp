#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double funcao(double x);

int main(){
    int fseed = -424242;
    double max = 4./3, a = 0, b = 3;
    double z, y, dy;
    int i, j, Ndiv=20, Nevt = 5000;
    int n = 1;
    int *bin = NULL;
    double base;
    double Nmomento1 = 0, Nmomento2 = 0, media = 0, media2 = 0, var = 0;
    base=b-a;
    dy = (base/Ndiv);
    FILE *saida = fopen("rejeicao_pol3.dat","w"); //Cria arquivo de saida

    //Aloca memória para o histograma
    bin = (int *) malloc( (Ndiv)*sizeof(int));
    if ( bin == NULL ){
      printf ("nao foi possivel alocar a memoria");
      return 1;
    }

    //Garante que os bins estao zerados
    for (i=0;i<Ndiv;i++) bin[i]=0;
    //inicia a semente
    srand(fseed);

    while (n<=Nevt)
    {
	//Sorteia y e z, tal que z 'e o limite superior
	z = a + (max - a )*((double)rand())/RAND_MAX; // z esta entre 0  e fmax
	y = a + (3. - a)*((double)rand())/RAND_MAX; //pode ser usado 2.99 como limite ao invés de 3 para evita que o programa sorteie y = 3 e cause overflow

	//Se f(y) é maior do que z  o valor de y é aceito
	if(funcao(y)>z){
        j=(int) ( (y-a)/dy );
        Nmomento1 = Nmomento1 + y;
        Nmomento2 = Nmomento2 + y*y;


        //Para evitar bugs
        if(j>=Ndiv) {
            printf("Atencao: Overflow: Indice j = %d maior ou igual Ndiv = %d. Descartando.\n",j,Ndiv);
            continue;
        }


        bin[j]++;
        n++;
	}
	//se f(y) é menor que z o valor de y é rejeitado e o loop volta a sortear um novo z
}

//imprime os valores obtidos em um arquivo.dat
for (j=0;j<Ndiv;j++)
    {
	y=a+j*dy + dy/2;
	fprintf(saida,"%g     %f\n",y, (double)bin[j]/(Nevt*dy) );
    }

    //libera o ponteiro bin
    free( bin );

//Calcula a media e a variancia
    media  = Nmomento1/Nevt;
    media2 = Nmomento2/Nevt;
    var = media2 - media*media;

    printf("M'edia: %lf\nVari^ancia: %lf\n",media, var);
    return 0;
}

double funcao(double x){
    return (4./81)*x*x*x;
}
