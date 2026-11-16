
#include <stdio.h>
#include <stdlib.h>

#define NF 10
#define NC 12

/* Apresenta uma mensagem de erro e encerra o programa. */
void encerra(char *msg) {
    printf("%s", msg);
    printf("\nPrograma encerrado sem sucesso...");
    /* O valor 1 indica encerramento por erro. */
    exit(1);
}

/* Grava uma plateia vazia no arquivo já aberto.
   Não recebe a matriz porque escreve diretamente o caractere '-'. */
void iniPlateia(FILE *fp) {
    for (int i = 0; i < NF; i++) {
        for (int j = 0; j < NC; j++)
            fprintf(fp, "%c", '-');

        /* Separa as fileiras no arquivo. */
        fprintf(fp, "\n");
    }
}

/* Carrega a matriz com os dados do arquivo.
   Se o arquivo não existir, cria uma plateia com todas as posições livres. */
void carregaPlateia(char *nomeArq, char plateia[][NC]) {
    int i, j;
    FILE *fp;

    /* Tenta abrir o arquivo existente para leitura. */
    if ((fp = fopen(nomeArq, "r")) == NULL) {

        /* Cria o arquivo quando a abertura para leitura falha. */
        if ((fp = fopen(nomeArq, "w")) == NULL)
            encerra("Falha na criacao do arquivo de plateia!");

        /* Grava NF linhas com NC poltronas livres em cada linha. */
        iniPlateia(fp);

        /* Fecha o arquivo antes de reabri-lo para leitura. */
        fclose(fp);

        if ((fp = fopen(nomeArq, "r")) == NULL)
            encerra("Falha na abertura do arquivo de plateia!");

        printf("Primeiro acesso ao programa: arquivo de plateia criado\n");
    }

    /* Cada caractere do arquivo corresponde a uma posição da matriz. */
    for (i = 0; i < NF; i++) {
        for (j = 0; j < NC; j++) {
            if (fscanf(fp, "%c", &plateia[i][j]) != 1)
                encerra("Erro na leitura do arquivo de plateia!");
        }

        /* Descarta a quebra de linha após as NC posições. */
        if (i < NF - 1) {
            if (fgetc(fp) != '\n')
                encerra("Formato invalido do arquivo de plateia!");
        }
    }

    fclose(fp);
}

/* Salva a matriz no arquivo. */
void salvaPlateia(char *nomeArq, char plateia[][NC]) {
    int i, j;
    FILE *fp = NULL;

    fp = fopen(nomeArq, "w");

    if (fp == NULL) {
        encerra("Falha na abertura do arquivo de plateia!");
    }

    for (i = 0; i < NF; i++) {
        for (j = 0; j < NC; j++) {
            fprintf(fp, "%c", plateia[i][j]);
        }

        fprintf(fp, "\n");
    }

    fclose(fp);
}

/* Limpa os caracteres restantes no buffer do teclado. */
void limpaEntradaTeclado() {
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

/* Solicita um numero inteiro ao usuario. */
int inputInt(char *mensagem) {
    char entrada[21];
    int i, valido;

    do {
        printf("%s", mensagem);

        if (scanf("%20s", entrada) != 1) {
            encerra("Erro na leitura!");
        }

        limpaEntradaTeclado();

        valido = 1;

        if (entrada[0] == '-' && entrada[1] == '\0') {
            valido = 0;
        }

        for (i = 0; entrada[i] != '\0'; i++) {

            if (entrada[i] < '0' || entrada[i] > '9') {
                if (entrada[i] != '-' || i != 0) {
                    valido = 0;
                }
            }
        }

        /* Muda a mensagem quando o valor nao e inteiro. */
        if (valido == 0) {
            mensagem = "Nao e um inteiro! Digite um numero inteiro: ";
        }

    } while (valido == 0);

    return atoi(entrada);
}

int main(void) {
    char plateia[NF][NC];

    carregaPlateia("plateia.txt", plateia);

    return 0;
}
