#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "bitmap.h"
#include "lista.h"

bitmap *funcaoTeste(unsigned int tamUtil, unsigned int tamTotal, unsigned char *conteudo){

    bitmap *bm = bitmapInit(tamTotal+1);

    for(unsigned int i=0; i < tamTotal/8; i++){

        appendNovo(bm, conteudo[i]);

    }

    return bm;

}

int main(int argc, char *argv[]){

    if(argc<2){
        printf("Informe o diretorio\n");
        return 1;
    }

    char *dir = malloc(1000 * sizeof(char));
    sprintf(dir, "%s", argv[1]);

    //FILE *fp2 = fopen("saida.txt", "rb");
    FILE *fp2 = fopen(dir, "rb");

    unsigned int tamTotal=0, tamUtil=0;

    fread(&tamUtil, sizeof(unsigned int), 1, fp2);
    fread(&tamTotal, sizeof(unsigned int), 1, fp2);

    unsigned char *strAux = malloc((tamTotal+1) * sizeof(unsigned char));

    fread(strAux, sizeof(unsigned char), tamTotal/8, fp2);

    unsigned int tamTotal2=0, tamUtil2=0;

    fread(&tamUtil2, sizeof(unsigned int), 1, fp2);
    fread(&tamTotal2, sizeof(unsigned int), 1, fp2);

    unsigned char *stringDec = malloc((tamTotal2+1) * sizeof(unsigned char));

    fread(stringDec, sizeof(unsigned char), tamTotal2/8, fp2);

    bitmap *bitmapArv = funcaoTeste(tamUtil, tamTotal, strAux);

    bitmap *bitmapString = funcaoTeste(tamUtil2, tamTotal2, stringDec);

    unsigned int indice = 0;
    Arv * arvNovo = recriaArvore(bitmapArv, &indice, tamUtil);

    decodificaFinal2(arvNovo, bitmapString, tamUtil2, dir);

    free(strAux);
    free(stringDec);
    bitmapLibera(bitmapString);
    bitmapLibera(bitmapArv);
    abb_libera(arvNovo);

    return 0;

}