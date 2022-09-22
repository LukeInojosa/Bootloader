#include <iostream>
#include <vector>
#include <utility>
#include <pthread.h>
using namespace std;

typedef struct {
    int **m;
    int l, c;
} Matriz;

typedef struct { //Struct para pegar os valores das entradas
    int linha_matriz_esparsa1, linha_matriz_esparsa2;
    int coluna_matriz_esparsa1, coluna_matriz_esparsa2;
    int linha_matriz, coluna_matriz;
    int tam_vetor;
} Parametros;

typedef struct { //Struct para passar os parametros das funções na thread
    int l, c;
} Params;

//Definindo variáveis globais
vector<pair<int,float>> *matriz_esparsa1;
vector<pair<int,float>> *matriz_esparsa2;
vector<int> vetor_coluna;
Matriz matriz_densa; 
Matriz matriz_res;
int boolean = 1; //Verifica se ocorreu a multiplicação das matrizes

void print_matriz_esparsa(vector<pair<int,float>> *matriz_esparsa, int qtd_linhas) {
    int i, j, tam;
    for (i=0; i<qtd_linhas; i++) {
        tam = matriz_esparsa[i].size();
        for (j=0; j<tam; j++) {
            printf("(%d, %.2f) ", matriz_esparsa[i][j].first, matriz_esparsa[i][j].second);
        }
        printf("\n");
    }
}

void print_matriz(Matriz matriz) {
    int i, j;
    for (i=0; i<matriz.l; i++) {
        for (j=0; j<matriz.c; j++) {
            printf("%d ", matriz.m[i][j]);
        }
        printf("\n");
    }

}

void* multi_esparsa_vetor(void *params) {
    Params p = *(Params*) params;
    int soma_linha = 0, tam, pos, i;
    tam = matriz_esparsa1[p.l].size();
    for (i=0; i<tam; i++) {
        pos = matriz_esparsa1[p.l][i].first;
        soma_linha += matriz_esparsa1[p.l][i].second * vetor_coluna[pos]; 
    }
    matriz_res.m[p.l][0] = soma_linha;
    pthread_exit(NULL);
}

void* multi_esparsa_esparsa(void *params) {
    Params p = *(Params*) params;
    int soma_linha = 0, tam1, tam2, pos, i, j;
    
    tam1 = matriz_esparsa1[p.l].size();
    for (i=0; i<tam1; i++) {
        pos = matriz_esparsa1[p.l][i].first;
        tam2 = matriz_esparsa2[pos].size();
        for (j=0; j<tam2; j++) {
            if (p.c == matriz_esparsa2[pos][j].first) {
                soma_linha += matriz_esparsa1[p.l][i].second * matriz_esparsa2[pos][j].second;
            }
        }
    }
    matriz_res.m[p.l][p.c] = soma_linha;
    pthread_exit(NULL);
}

void* multi_esparsa_densa(void *params) {
    Params p = *(Params*) params;
    int soma_linha = 0, tam, pos, i;

    tam = matriz_esparsa1[p.l].size();
    for (i=0; i<tam; i++) {
        pos = matriz_esparsa1[p.l][i].first;
        soma_linha += matriz_esparsa1[p.l][i].second * matriz_densa.m[pos][p.c];
    }
    matriz_res.m[p.l][p.c] = soma_linha;
    pthread_exit(NULL);
}

Params create_params(int l, int c) { //Função para definir os parametros para cada thread
    Params params;
    params.l = l; params.c = c;
    return params;
}

void menu(int op, Parametros p) {
    int i, j, tam, qtdThreads;

    if (op == 0) {
        if (p.coluna_matriz_esparsa1 == p.tam_vetor) {
            qtdThreads = p.linha_matriz_esparsa1; //Definindo o número de threads
            pthread_t thread[qtdThreads];
            Params params[qtdThreads];

            matriz_res.c = 1; matriz_res.l = p.linha_matriz_esparsa1; //Definindo as dimensões da matriz resultante
            matriz_res.m = (int **) malloc (sizeof(int *)*matriz_res.l); //Alocando a matriz resultante

            for (i=0; i<matriz_res.l; i++) matriz_res.m[i] = (int *) calloc (matriz_res.c, sizeof(int));
            for (i=0; i < p.linha_matriz_esparsa1; i++) { 
                params[i] = create_params(i, 0);
                pthread_create(&thread[i], NULL, multi_esparsa_vetor, &params[i]); //Criando uma thread para cada linha
            }
            for(i=0; i<qtdThreads; i++) {
                pthread_join(thread[i], NULL); //Esperando as threads serem finalizadas
            }
        }

        else {
            boolean = 0;
            printf("Dimensões inválidas.\nNão é possivel multiplicar essa matriz por esse vetor coluna.\n");
        }
    }
    
    else if (op == 1) {
        if (p.coluna_matriz_esparsa1 == p.linha_matriz_esparsa2) {
            qtdThreads = p.linha_matriz_esparsa1*p.coluna_matriz_esparsa2; //Definindo o número de threads
            pthread_t thread[qtdThreads];
            Params params[qtdThreads];
            int cnt = 0; //Contador para o número de threads

            matriz_res.l = p.linha_matriz_esparsa1; matriz_res.c = p.coluna_matriz_esparsa2; //Definindo as dimensões da matriz resultante
            matriz_res.m = (int **) malloc (sizeof(int *)*matriz_res.l); //Alocando a matriz resultante
            for (i=0; i<matriz_res.l; i++) matriz_res.m[i] = (int *) calloc (matriz_res.c, sizeof(int));

            for (i=0; i < p.linha_matriz_esparsa1; i++) { 
                for (j=0; j<p.coluna_matriz_esparsa2; j++) {
                    params[cnt] = create_params(i, j);
                    pthread_create(&thread[cnt], NULL, multi_esparsa_esparsa, &params[cnt]); //Criando threads para multiplicar cada linha por cada coluna
                    cnt++;
                }
            }
            for(i=0; i<qtdThreads; i++) {
                pthread_join(thread[i], NULL); //Esperando as threads serem finalizadas
            }
        }
        else {
            boolean = 0;
            printf("Dimensões inválidas.\nNão foi possivel multiplicar essas matrizes.\n");
        }
    }

    else if(op == 2) {
        if (p.coluna_matriz_esparsa1 == p.linha_matriz) {
            qtdThreads = p.linha_matriz_esparsa1*p.coluna_matriz; //Definindo o número de threads
            pthread_t thread[qtdThreads];
            Params params[qtdThreads];
            int cnt = 0; //Contador para o número de threads
            
            matriz_res.l = p.linha_matriz_esparsa1; matriz_res.c = p.coluna_matriz; //Definindo as dimensões da matriz resultante
            matriz_res.m = (int **) malloc (sizeof(int *)*matriz_res.l); //Alocando a matriz resultante
            for (i=0; i<matriz_res.l; i++) matriz_res.m[i] = (int *) calloc (matriz_res.c, sizeof(int));

            for (i=0; i<p.linha_matriz_esparsa1; i++) {
                for (j=0; j<p.coluna_matriz; j++) {
                    params[cnt] = create_params(i, j);
                    pthread_create(&thread[cnt], NULL, multi_esparsa_densa, &params[cnt]); //Criando threads para multiplicar cada linha por cada coluna
                    cnt++;
                }
            }
            for(i=0; i<qtdThreads; i++) {
                pthread_join(thread[i], NULL); //Esperando as threads serem finalizadas
            }
        }
        else {
            boolean = 0;
            printf("Dimensões inválidas.\nNão foi possivel multiplicar essas matrizes.\n");
        }
        
    }
    
    return;
}

Parametros create_parametros() { //Função para inicializar os parametros das entradas
    Parametros p;
    p.coluna_matriz = 0; p.linha_matriz = 0;
    p.coluna_matriz_esparsa1 = 0; p .linha_matriz_esparsa1 = 0;
    p.coluna_matriz_esparsa2 = 0; p.linha_matriz_esparsa2 = 0;
    p.tam_vetor = 0;
    return p;
}

int main() {
    int op, pos, flag, i, j;
    float elemento;
    Parametros parametros = create_parametros();

    printf("Digite a sua escolha:\n");
    printf(" 0 - Multiplicação de uma matriz esparsa por um vetor coluna.\n");
    printf(" 1 - Multiplicação de uma matriz esparsa por uma matriz esparsa\n");
    printf(" 2 - Multiplicação de uma matriz esparsa por uma matriz densa.\n");
    printf("Opção: ");
    scanf("%d", &op);

    printf("\nQuantidade de linhas da sua matriz esparsa: ");
    scanf("%d", &parametros.linha_matriz_esparsa1);
    matriz_esparsa1 = (vector<pair<int,float>> *)malloc(parametros.linha_matriz_esparsa1 * sizeof(vector<pair<int,float>>));
    printf("- Digite os elementos da sua matriz esparsa, um par por linha, no formato 'int float', separados por um espaço.\n");
    printf("- Obs: Insira -1 -1 para pular de linha na matriz esparsa.\n\n");

    for (i=0; i<parametros.linha_matriz_esparsa1; i++) { //Leitura da matriz esparsa
        flag = 1;
        while(flag) {
            scanf("%d %f", &pos, &elemento);
            if (elemento == -1 && pos == -1) flag = 0;
            else {
                matriz_esparsa1[i].push_back(make_pair(pos, elemento));
                if (pos > parametros.coluna_matriz_esparsa1) parametros.coluna_matriz_esparsa1 = pos;
            }
        }
    }
    parametros.coluna_matriz_esparsa1++;
    printf("Matriz esparsa digitada:\n");
    print_matriz_esparsa(matriz_esparsa1, parametros.linha_matriz_esparsa1);
    printf("\n");

    if (op == 0) {
        printf("Quantidade de elementos do seu vetor coluna: "); //Leitura do vetor coluna
        scanf("%d", &parametros.tam_vetor);
        printf("Digite os elementos do seu vetor coluna: ");
        vetor_coluna.clear();
        vetor_coluna.resize(parametros.tam_vetor);
        for (int i=0; i<parametros.tam_vetor; i++) {
            scanf("%d", &vetor_coluna[i]);
        }
        printf("Vetor coluna digitado:\n");
        for (int i=0; i<parametros.tam_vetor; i++) printf("%d\n", vetor_coluna[i]);
        printf("\n");

    }

    else if (op == 1) {
        printf("Quantidade de linhas da sua segunda matriz esparsa: ");
        scanf("%d", &parametros.linha_matriz_esparsa2);
        matriz_esparsa2 = (vector<pair<int,float>> *)malloc(parametros.linha_matriz_esparsa2 * sizeof(vector<pair<int,float>>));        printf("- Digite os elementos da sua matriz esparsa, um par por linha, no formato 'int float', separados por um espaço.\n");
        printf("- Obs: Insira -1 -1 para pular de linha na matriz esparsa.\n\n");

        for (i=0; i<parametros.linha_matriz_esparsa2; i++) { //Leitura da matriz esparsa
            flag = 1;   
            while(flag) {
                scanf("%d %f", &pos, &elemento);
                if (elemento == -1 && pos == -1) {
                    flag = 0;
                }
                else {
                    matriz_esparsa2[i].push_back(make_pair(pos, elemento));
                    if (pos > parametros.coluna_matriz_esparsa2) parametros.coluna_matriz_esparsa2 = pos;
                }
            }
        }
        parametros.coluna_matriz_esparsa2++;
        printf("Matriz esparsa 2 digitada:\n");
        print_matriz_esparsa(matriz_esparsa2, parametros.linha_matriz_esparsa2);
        printf("\n");
    }

    else if (op == 2) {
        printf("Digite as dimensões da sua matriz densa.\n");
        printf("Linhas: ");
        scanf("%d", &parametros.linha_matriz);
        printf("Coluna: ");
        scanf("%d", &parametros.coluna_matriz);
        matriz_densa.l = parametros.linha_matriz;
        matriz_densa.c = parametros.coluna_matriz;
        matriz_densa.m = (int **) malloc (sizeof(int *)*parametros.linha_matriz);
        for (i=0; i<parametros.linha_matriz; i++) matriz_densa.m[i] = (int *) calloc (parametros.coluna_matriz, sizeof(int));
        for (i=0; i<parametros.linha_matriz; i++) {
            for (j=0; j<parametros.coluna_matriz; j++) { //LEITURA DA MATRIZ DENSA
                scanf("%d", &matriz_densa.m[i][j]);
            }
        }
        printf("Matriz densa digitada:\n");
        print_matriz(matriz_densa);
    }
    menu(op, parametros);
    if (boolean) {
        printf("\n");
        printf("Resultado da multiplicação: \n");
        print_matriz(matriz_res);
    }
    return 0;
}