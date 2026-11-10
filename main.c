#include <stdio.h>
#include <stdlib.h>
int main(void) {
    FILE *arquivo = fopen("historico.txt", "w");
    if (arquivo == NULL){
        printf("Erro no Arquivo!!!");
        return 0;
    }
    int matriz[12][10];
    for (i = 0 ; i <12;i++ ){
        for (j = 0 ; j <10;j++ ){
            matriz[i][l] = "-"
        }
    }






     fclose(arquivo);
}