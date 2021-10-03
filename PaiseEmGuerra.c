#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TAM_N 500
int *cidades[TAM_N];

void inicializa_w(int w[TAM_N][TAM_N], int N) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            w[i][j] = 1001;
        }
    }
}

int extract_min(int *d, int *v, int N) {
    int i, menor = 0, u = 1001;
    for (i = 0; i < N; i++) {
        if ((d[i] < u) && (!v[i])) {
            menor = i;
            u = d[i];
        }
    }
    return menor;
}

int dijkstra(int w[TAM_N][TAM_N], int N, int O, int D) {
    int i, v[N], origem, destino;
    if (w[O][D] == 0) return 0;
    else if (cidades[O] != NULL) return cidades[O][D];
    else {
        int *d = malloc(sizeof(int) * N);
        cidades[O] = d;
        for (i = 0; i < N; i++) {
            v[i] = 0;
            d[i] = 1001;
        }
        d[O] = 0;
        for (i = 0; i < N; i++) {
            origem = extract_min(d, v, N);

            v[origem] = 1;
            //Relax
            for (destino = 0; destino < N; destino++) {
                if ((!v[destino]) && (d[origem] < 1001) && (w[origem][destino] < 1001) && (d[origem] + w[origem][destino] < d[destino])) 
                    d[destino] = d[origem] + w[origem][destino];
            }
        }
        return d[D];
    }
}

int main () {
    int N, E;
    int X, Y, H;
    int K,M;
    int O, D;
    int w[TAM_N][TAM_N];
    int i;

    while (scanf("%d %d", &N, &E), (N != 0) || (E != 0)) {
        while (((N <= 0) || (N > 500)) || ((E < 0) || (E > pow(N, 2)))) 
            scanf("%d %d", &N, &E);
        inicializa_w(w, N);
        for (i = 0; i < N; i++) {
            if (cidades[i] != NULL) {
                free(cidades[i]);
                cidades[i] = NULL;
            }
        }

        for (i = 0; i < E; i++) {
            scanf("%d %d %d", &X, &Y, &H);
            while (((X <= 0) || (X > N)) || ((Y <= 0) || (Y > N)) ||((H <= 0) || (H > 1000)))
                scanf("%d %d %d", &X, &Y, &H);

            if (w[Y-1][X-1] < 1001) 
                w[X-1][Y-1] = w[Y-1][X-1] = 0;
            else 
                w[X-1][Y-1] = H;
        }

        scanf("%d", &K);
        while ((K < 0) || (K > 100))
            scanf("%d", &K);

        for (i = 0; i < K; i++) {
            scanf("%d %d", &O, &D);
            while (((O <= 0) || (O > N)) || ((D <= 0) || (D > N)))
                scanf("%d %d", &O, &D);

            M = dijkstra(w, N, O-1, D-1);
            if (M == 1001) 
               printf("Nao e possivel entregar a carta\n");
            else 
                printf("%d\n", M);
        }
        printf("\n");
    }
    return 0;
}
