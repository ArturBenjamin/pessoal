#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    float GLI; /* Glicose */
    float METGLI; /* Meta */
    float FS; /* Fator de sensibilidade */
    float CCHO; /* Contagem de carboidratos */
    float RICHO; /* Relação insulina/carboidrato */
    float QIGLI = 0; /* Qtd de insulina para glicose */
    float QICHO = 0; /* Qtd de insulina para carboidrato */
    float QIT = 0; /* Qtd de insulina total */

    printf("Glicose: \n");
    scanf( "%f", &GLI);
    printf("Meta: \n");
    scanf( "%f", &METGLI);
    printf("Fator de sensibilidade: \n");
    scanf( "%f", &FS);
    printf("Quantidade de CHO: \n");
    scanf( "%f", &CCHO);
    printf("Relação I/R: \n");
    scanf( "%f", &RICHO);

    if(GLI <= METGLI)
    {
        if(GLI < 80)
        {
            QIGLI = (-1);
        }
        else
        {
            QIGLI = 0;
        }
    }
    else
    {
        QIGLI = (GLI - 80)/FS;
    }
    if(CCHO > 0)
    {
        QICHO = CCHO/RICHO;
    }
    QIT = QIGLI + QICHO;

    printf("A quantidade de insulina em unidades será: %.2f\n", QIT);

    return 0;
}
