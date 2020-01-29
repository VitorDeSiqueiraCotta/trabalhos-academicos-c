#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#define TAM_MAX 50

struct T_Produto {
    int tipo;
    int tempoDeteoriacao;
    int tempoEmpacotamento;
    int instanteEntrada;
    float custoProducao;
    float precoAtacado;
};

typedef struct T_Produto T_Produto;

struct structMaquina {
    int qtCoxinha;
    int qtPeixe;
    int qtAlmondega;
    int embalado;
    int qtDescarteCoxinha;
    int qtDescartePeixe;
    int qtDescarteAlmondega;
    int descartado;
    int tempoFuncionando;
    int tempoOcioso;
    int horaFuncionamento;
    int qtProduto;
    int entrada;
    int saida;
    T_Produto filaProdutos[TAM_MAX];
};

typedef struct structMaquina structMaquina;

struct T_Maquina {
    structMaquina campo;
    struct T_Maquina *prox;
};

typedef struct T_Maquina T_Maquina;

struct T_ListaMaquina {
    T_Maquina *primeiro;
    T_Maquina *ultimo;
    int qtMaquina;
};

typedef struct T_ListaMaquina T_ListaMaquina;

T_Maquina instanciarMaquina(void);
T_Produto instanciarCoxinha(const int instanteEntrada);
T_Produto instanciarPeixe(const int instanteEntrada);
T_Produto instanciarAlmondega(const int instanteEntrada);
void instanciarListaMaquina(T_ListaMaquina *listaMaquina);
void inserirMaquina(T_ListaMaquina *listaMaquina);
T_Produto probabilidade(const int instanteEntrada);
void inserirProduto(const T_Produto produto, T_Maquina *m);
int empacotar(T_Maquina *m, const int tempo);
void retirarProduto(T_Maquina *m);
void printEstatisticaMaquina(const T_Maquina m, const int contador);
void printEstatisticaDiaria(const T_Maquina m, const float saldo, const float energia, const float lucroDiario, const float prejuizoDiario, const int tempo);
void atualizarEstatistica(T_Maquina *m, const int OP);
void resultadoFinal(const T_Maquina estatisticaFinal, const T_ListaMaquina listaMaquina, const int tempo);

#endif
