#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define pi 3.14

void calc_esfera (float r, float* area, float* volume);

int raizes (float a, float b, float c, float* x1, float* x2);

int pares (int n, int* vet);

void inverte (int n, int* vet);

double avalia (double* poli, int grau, double x);

int main(){

    // funcao esfera;

    float *area = malloc(sizeof(float));

    float *volume = malloc(sizeof(float));

    float raio = 0;

    scanf("%f", &raio);
    scanf("%*c");

    calc_esfera(raio, area, volume);

    printf("A:%0.2f V:%0.2f\n", *area, *volume);

    free(area);
    free(volume);


    // funcao raizes;

    float *x1 = malloc(sizeof(float));
    
    float *x2 = malloc(sizeof(float));

    float a = 0, b = 0, c = 0;

    scanf("%f %f %f", &a, &b, &c);
    scanf("%*c");

    raizes(a, b, c, x1, x2);

    printf("x1:%0.2f x2:%0.2f\n", *x1, *x2);

    free(x1);
    free(x2);


    // funcao pares;

    int n = 0;

    scanf("%d", &n);
    scanf("%*c");

    int *vet = malloc(n * sizeof(int));

    for(int i = 0; i < n; i++){

        scanf("%d", &vet[i]);
        scanf("%*c");

    }

    printf("Pares:%d\n", pares(n, vet));

    free(vet);


    //funcao inverte;

    int m = 0;

    scanf("%d", &n);
    scanf("%*c");

    int *vet2 = malloc(m * sizeof(int));

    for(int i = 0; i < n; i++){

        scanf("%d", &vet2[i]);
        scanf("%*c");

    }

    inverte(n, vet2);

    for(int i = 0; i < n; i++){

        printf("%d ", vet[i]);

    }

    printf("\n");

    free(vet);


    //funcao avalia;

    int grau = 0;

    scanf("%d", &grau);
    scanf("%*c");

    double *poli = malloc((grau+1) * sizeof(double));

    for(int i = 0; i < grau+1; i++){

        scanf("%lf", &poli[i]);
        scanf("%*c");

    }

    double x = 0;

    printf("escreva o valor de x:");
    scanf("%lf", &x);
    scanf("%*c");

    printf("raiz:%lf\n", avalia(poli, grau, x));

    free(poli);

    return 0;

}

void calc_esfera(float r, float* area, float* volume){

    *area = 4 * pi * r * r;

    *volume = (4 * pi * r * r * r) / 3;

}

int raizes(float a, float b, float c, float* x1, float* x2){

    float delta = (b * b) - (4 * a * c);
    
    *x1 = ((b * (-1)) + sqrt(delta)) / (2 * a);

    *x2 = ((b * (-1)) - sqrt(delta)) / (2 * a);

    return 1;

}

int pares (int n, int* vet){

    int contador = 0;

    for(int i = 0; i < n; i++){

        if(vet[i] % 2 == 0){

            contador++;

        }

    }

    return contador;

}

void inverte (int n, int* vet){

    int aux;

    for(int i =0 ; i < n/2; i++){

        aux = vet[i];
        vet[i] = vet[n - 1 - i];
        vet[n - 1 - i] = aux;

    }

}

double avalia (double* poli, int grau, double x){

    double contador = 0;

    contador += poli[0];

    for(int i = 1; i < grau+1; i++){

        contador += poli[i] * pow(x, i);

    }

    return contador;

}