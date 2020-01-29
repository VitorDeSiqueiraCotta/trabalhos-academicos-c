#include "manipularArquivo.h"

int obter_qt_registros(const char *diretorio) {
    FILE *ARQV = fopen(diretorio, "r");
    char leitor;
    int qtRegistros = 1;

    if(!ARQV) {
        printf("[ ERROR ] - Arquivo [ %s ] nao encontrado.\n", diretorio);
        exit(1);
    }

    leitor = getc(ARQV);

    while(!feof(ARQV)) {
        if(leitor == '\n')
            ++qtRegistros;
        leitor = getc(ARQV);
    }
    fclose(ARQV);

    return qtRegistros;
}

void carregar_arquivo_enem(StructEscola *registros, const char *diretorio) {
    FILE *ARQV = fopen(diretorio, "r");

    if(!ARQV) {
        printf("[ ERROR ] - Arquivo [ %s ] nao encontrado.\n", diretorio);
        exit(1);
    }

    int i = 0;
    char leitor[256];

    while(!feof(ARQV)) {
        fgets(leitor, 256, ARQV);
        sscanf(strtok(leitor, ";"), "%d", &registros[i].ID);
        sscanf(strtok(NULL, ";"), "%s", registros[i].estado);
        strcpy(registros[i].municipio, strtok(NULL, ";"));
        sscanf(strtok(NULL, ";"), "%s", registros[i].rede);
        sscanf(strtok(NULL, ";"), "%f", &registros[i].media_ciencias_natureza);
        sscanf(strtok(NULL, ";"), "%f", &registros[i].media_ciencias_humanas);
        sscanf(strtok(NULL, ";"), "%f", &registros[i].media_linguagem);
        sscanf(strtok(NULL, ";"), "%f", &registros[i].media_matematica);
        sscanf(strtok(NULL, ";"), "%f", &registros[i].media_redacao);
        ++i;
    }
    printf("[ INFORM ] - Arquivo [ %s ] lido com sucesso.\n", diretorio);

    fclose(ARQV);
}

void carregar_arquivo_indice(StructEscola *registros, const int qtRegistros, const StructArgv argumentos) {
    FILE *ARQV = fopen(argumentos.diretorio, "r");

    if(!ARQV) {
        printf("[ ERROR ] - Arquivo [ %s ] nao encontrado.\n", argumentos.diretorio);
        exit(1);
    }

    char leitor[16];

    clock_t START = clock();

    if(!strcmp(argumentos.tipoBusca, "bs") && !strcmp(argumentos.imprimir, "-p")) {
        while(!feof(ARQV)) {
            fgets(leitor, 16, ARQV);
            imprimir_registro(busca_sequencial(registros, atoi(leitor), qtRegistros));
        }
    }
    else if(!strcmp(argumentos.tipoBusca, "bb") && !strcmp(argumentos.imprimir, "-p")) {
        while(!feof(ARQV)) {
            fgets(leitor, 16, ARQV);
            imprimir_registro(busca_binaria(registros, atoi(leitor), qtRegistros));
        }
    }
    else if(!strcmp(argumentos.tipoBusca, "bs")) {
        while(!feof(ARQV)) {
            fgets(leitor, 16, ARQV);
            busca_sequencial(registros, atoi(leitor), qtRegistros);
        }
    }
    else if(!strcmp(argumentos.tipoBusca, "bb")) {
        while(!feof(ARQV)) {
            fgets(leitor, 16, ARQV);
            busca_binaria(registros, atoi(leitor), qtRegistros);
        }
    }

    clock_t END = clock();

    double TIME = ((double) (END - START)) / CLOCKS_PER_SEC;

    printf("[ INFORM ] - Duracao da busca do indice %lfs.\n", TIME);

    fclose(ARQV);
}
