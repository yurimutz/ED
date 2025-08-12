#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "bitmap.h"
#include "lista.h"

void leArquivo(int *vetFreq, FILE *fp){

    unsigned char aux;
    while(fread(&aux, sizeof(char), 1, fp) == 1){
        
        vetFreq[aux]++;
        
    }

}

int descobreTamString(FILE *fp, unsigned char **dic){

    int tam = 0;

    unsigned char aux;
    while(fread(&aux, sizeof(char), 1, fp) == 1){
        
        tam = tam + strlen(dic[aux]);
        
    }

    //+1 para o caractere '\0
    return tam + 1;

}

unsigned char *codificaArquivo(unsigned char **dic, FILE *fp){

    fseek(fp, 0, SEEK_SET);

    unsigned char *txtCodificado = calloc(descobreTamString(fp, dic), sizeof(char));

    fseek(fp, 0, SEEK_SET);

    char aux;
    while(fread(&aux, sizeof(char), 1, fp) == 1){
        
        strcat(txtCodificado, dic[aux]);
        
    }

    return txtCodificado;

}

void compactaArquivo(unsigned char *codificado, unsigned int tam){

    bitmap *bitmap = bitmapInit((unsigned int)tam);

    for(int i=0; i < tam; i++){

        bitmapAppendLeastSignificantBit(bitmap, codificado[i]);

    }

}

int main(){

    int *vetFreq = calloc(256, sizeof(int));

    FILE *fp = fopen("entrada.txt", "r");

    //essa leitura verificar duas vezes se e o feof, assim, o ultimo carectere e lido 2x, freq do ultimo fica 1 unidade maior
    //for(int i=0; !feof(fp); i++){

        //fscanf(fp, "%c", &texto[i]);

        //fazendo desse jeito o carac 'o' tem freq errada
        // char aux;
        // fscanf(fp, "%c", &aux);
        // vetFreq[aux]++;

    //}

    leArquivo(vetFreq, fp);

    Lista *l = criaLista();

    l = criaListaOrdenada(l, vetFreq);

    criaArvoreHuff(l);

    //imprimeLista(l);

    //tamanho da arvore + espaco para o caractere "\0"
    int altura = retAlturaCelula(l) + 1;

    unsigned char **dicionario = criaDicionario(l, altura);

    unsigned char *txtCodificado = codificaArquivo(dicionario, fp);

    unsigned char *txtDecodificado = decodificaArquivo(l, txtCodificado, fp);

    fclose(fp);

    return 0;

}