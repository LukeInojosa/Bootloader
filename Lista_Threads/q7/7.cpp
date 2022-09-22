#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int boolean = 1;

typedef struct {
    int **m;
    int n;
} Matrix;

typedef struct {
    int l, c;
    Matrix matrix;
} Params;

Params create_params(int l, int c, Matrix matrix) {
    Params params;
    params.l = l;
    params.c = c;
    params.matrix = matrix;
    return params;
}

void* check_line(void *params) {
    Params p = *(Params*) params;
    int i, j, k;
    for (i=0; i<p.matrix.n; i++) {
        for (j=i+1; j<p.matrix.n; j++) {
            if (p.matrix.m[p.l][i] == p.matrix.m[p.l][j]) {
                boolean = 0;
            }
        }
    }
    pthread_exit(NULL);
}

void* check_column(void *params) {
    Params p = *(Params*) params;
    int i, j, k;
    for (i=0; i<p.matrix.n; i++) {
        for (j=i+1; j<p.matrix.n; j++) {
            if (p.matrix.m[i][p.c] == p.matrix.m[j][p.c]){
                boolean = 0;
            }
        }
    }
    pthread_exit(NULL);
}

int check_matrix(Matrix matrix) {
    Params params1[matrix.n], params2[matrix.n];
    int i;
    int res;
    pthread_t threadsL[matrix.n], threadsC[matrix.n];

    for (i=0; i<matrix.n; i++) {
        params1[i] = create_params(i, 0, matrix);
        pthread_create(&threadsL[i], NULL, check_line, &params1[i]);
    }

    for (i=0; i<matrix.n; i++) {
        params2[i] = create_params(0, i, matrix);
        pthread_create(&threadsC[i], NULL, check_column, &params2[i]);
    }

    for(i=0; i<matrix.n; i++) {
        pthread_join(threadsC[i], NULL);
        pthread_join(threadsL[i], NULL);
    }
    return boolean;
}

int main (){  
    Matrix matrix;
    int res, i, j;

    printf("Digite o tamanho da sua matriz NxN: ");
    scanf("%d", &matrix.n);

    matrix.m = (int **) malloc(sizeof(int *) * matrix.n);

    for (i = 0; i < matrix.n; i++) matrix.m[i] = (int *) malloc(sizeof(int) * matrix.n); 
    for (i = 0; i < matrix.n; i++) {
        for (j = 0; j < matrix.n; j++) {
            scanf("%d", &matrix.m[i][j]);
        }
    }

    res = check_matrix(matrix);
    if (res) {
        printf("É um quadrado latino!\n");
    }
    else {
        printf("Ops, esse não é um quadrado latino :(\n");
    }

    for (i = 0; i < matrix.n; i++) {
        free(matrix.m[i]);
    }
    free(matrix.m);
    return 0;
}