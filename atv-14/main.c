#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    Hash *hash = hsh_cria();

    FILE *fp = fopen("entrada.txt", "r");

    while(!feof(fp)){

        char strAux[100];

        fscanf(fp, "%[^\n]", strAux);
        fscanf(fp, "%*[\n]");

        Palavra *palavraAux = criaPalavra(strAux);

        hsh_insere (hash, palavraAux);

    }

    fclose(fp);

    Palavra **vet = criaVetorOrdenado(hash);

    printaInformacoes(vet, hash);

    liberaVet(vet, hash);

    liberaHash(hash);

    return 0;

}