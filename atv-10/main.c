#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(long int *vet, int n){

    long int temp = 0;

    for(int i=0; i<n-1; i++){

        for(int j=i+1; j<n; j++){

            if(vet[i] > vet[j]){

                temp = vet[i];
                vet[i] = vet[j];
                vet[j] = temp;

            }

        }

    }

}


void rapida (int n, long int* v){

    if (n <= 1){ 
        return;
    } else {
    int x = v[0];
    int a = 1;
    int b = n-1;
    do {

        while (a < n && v[a] <= x){
            a++;
        }

        while (v[b] > x){
             b--;
        }

        if (a < b) { 

            int temp = v[a];
            v[a] = v[b];
            v[b] = temp;
            a++; b--;

        }

        } while (a <= b);
            
            v[0] = v[b];
            v[b] = x;
            rapida(b,v);
            rapida(n-a,&v[a]);

        
    }

}

int busca (int n, long int* vet, int elem){
    int i;
    for (i=0; i<n; i++) {
    if (elem == vet[i])
    return i;
    }
    return -1;
}


int main(){

    long int *vet;

    clock_t start, end;

    start = clock();

    vet = malloc(100000 * sizeof(long int));

    for(int i=0; i < 100000; i++){

        vet[i] = rand() % 100;

    }

    //bubbleSort(vet, 100000);

    //rapida (100000, vet);

    // int cont = 0;

    // for(int j = 0; j < 5 ; j++){

    //     int ret = busca (100000, vet, 86);

    //     if(ret == 86){

    //         cont ++;

    //     }

    // }

    end = clock();

    float tempo = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Tempo de execução: %f segundos\n", tempo);

    return 0;

}