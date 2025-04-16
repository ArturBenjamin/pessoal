/* Achar o maior de 10 ints
   Artur
*/

#include<stdio.h>
#include<stdlib.h>

#define MAXV 3

int main(void)
{
  int m;  // maior
  int V[MAXV]; // vetor com valores do usuário
  int i;  // indice

/* Entrada de dados*/
  for(i=0; i<MAXV; i++)
  {
      V[i]=rand()%100;

/* Processamento*/
    m=V[0];
    for(i=0; i<MAXV; i++)
    {
      if(m<V[i])
        m=V[i];
    }

/* Saída de dados*/
    printf("O maior valor é %d\n", m);
    printf("O vetor é: \n");
    for(i=0; i<MAXV; i++)
    {
       printf("%d\n", V[i]);
    }
    return EXIT_SUCCESS;
  }
}
