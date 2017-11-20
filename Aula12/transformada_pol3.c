#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int main()
{
    int fseed=-75364;
    double a = 0., b = 3;
    double x, y, dy;
    int n, i, j, Ndiv=20, Nevt = 5000;
    int *bin=NULL;
    double base;
    double Nmomento1 = 0, Nmomento2 = 0, media = 0, media2 = 0, var = 0;
    base=b-a;
    dy = (base/Ndiv);

    FILE *saida = fopen("transformada_pol3.dat","w"); //Cria arquivo de saida

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

    for ( n=1;n<=Nevt;n++)
    {
	x = a + (1 - a )*((double)rand())/RAND_MAX;
	y=3*sqrt(sqrt(x)); //Raiz quarta
	j=(int) ( (y-a)/dy );

	//atualiza os momentos para o cálculo da média e da vari^ancia
	Nmomento1 = Nmomento1 + y;
	Nmomento2 = Nmomento2 + y*y;


    //Para evitar bugs
    if(j>=Ndiv) {
		printf("Atencao: Overflow: Indice j = %d maior ou igual Ndiv = %d. Descartando.",j,Ndiv);
		continue;
	}


	/*  printf ("%f %f %d\n", x, y, j); */
	bin[j]++;
    }
    for (j=0;j<Ndiv;j++)
    {
	y=a+j*dy + dy/2;
	fprintf(saida,"%g     %f\n",y, (double)bin[j]/(Nevt*dy) );
    }
    free( bin );

    //Calcula a media e a variancia
    media  = Nmomento1/Nevt;
    media2 = Nmomento2/Nevt;
    var = media2 - media*media;

    printf("M'edia: %lf\nVari^ancia: %lf\n",media, var);
    return 0;
}
