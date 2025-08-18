#include "pais.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    Hash *h = hsh_cria();

    FILE *fp = fopen("entrada.txt", "r");

    while(!feof(fp)){

        Pais *p = lePais(fp);
        //imprimePais(p);

        hsh_insere(h, p);

    }

    fclose(fp);

    //printaHashMap(h);

    Pais **vet = criaVetorOrdenado(h);

    imprimeVetor(vet, retTamTab(h));

    liberaVet(vet, retTamTab(h));

    liberaHash(h);

    return 0;

}