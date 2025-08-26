#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "bitmap.h"
#include "lista.h"

void leArquivo(unsigned int *vetFreq, FILE *fp){

    unsigned char aux;
    while(fread(&aux, sizeof(unsigned char), 1, fp) == 1){
        
        vetFreq[aux]++;
        
    }

}

unsigned int descobreTamString(FILE *fp, unsigned char **dic, unsigned int altura){

    unsigned int tam = 0;

    unsigned char aux;
    while(fread(&aux, sizeof(unsigned char), 1, fp) == 1){
        
        tam = tam + altura;
        
    }

    return tam + 1;

}

unsigned char *codificaArquivo(unsigned char **dic, FILE *fp, unsigned int altura){

    fseek(fp, 0, SEEK_SET);

    unsigned char *txtCodificado = calloc(descobreTamString(fp, dic, altura)+1, sizeof(char));

    /*Implementado assim pois, anteriormente, usei strcat e deu poblema com arquivos grandes*/

    //Cria um ponteiro para a posicao atual de escrita
    unsigned char *ponteiro_atual = txtCodificado;

    //Segunda passada para codificar
    fseek(fp, 0, SEEK_SET);
    
    unsigned char aux;
    while(fread(&aux, sizeof(unsigned char), 1, fp) == 1){

        unsigned char* codigo = dic[aux];
        int tam_codigo = strlen(codigo);

        //Copia o codigo diretamente para a posicao atual
        memcpy(ponteiro_atual, codigo, tam_codigo);
        
        // Avança o ponteiro para o final dos dados recem-copiados
        ponteiro_atual += tam_codigo;
    }

    return txtCodificado;

}

void compactaArquivo(unsigned char *codificado, char *dir){

    int j=0;

    unsigned int tamUtil = strlen(codificado);

    //torna multiplo de 8
    unsigned int tamTotal = tamUtil;
    while(tamTotal % 8 != 0){

        tamTotal++;

    }

    bitmap *bitmap = bitmapInit(tamTotal);

    for(int i=0; i < tamUtil; i++){

        bitmapAppendLeastSignificantBit(bitmap, codificado[i]);

    }

    //FILE *fp = fopen("saida.txt", "ab");
    FILE *fp = fopen(dir, "ab");

    //tamanho util do dado compactado
    fwrite(&tamUtil, sizeof(unsigned int), 1, fp);
    //tamanho total do dado compactado (multiplo de 8 para formar bytes);
    fwrite(&tamTotal, sizeof(unsigned int), 1, fp);
    fwrite(bitmapGetContents(bitmap), sizeof(char), tamTotal/8, fp);

    bitmapLibera(bitmap);
    fclose(fp);

}

void liberaStrings(unsigned char **str){

    
    for(unsigned int i=0; i < 256; i++){

        free(str[i]);

    }

    free(str);

}

int main(int argc, char *argv[]){

    if(argc<2){
        printf("Informe o diretorio\n");
        return 1;
    }

    char *dir = malloc(1000 * sizeof(char));
    sprintf(dir, "%s", argv[1]);

    unsigned int *vetFreq = calloc(256, sizeof(int));

    FILE *fp = fopen(dir, "rb");

    //preenche o vetor de frequencias
    leArquivo(vetFreq, fp);

    Lista *l = criaLista();

    l = criaListaOrdenada(l, vetFreq);

    criaArvoreHuff(l);

    //tamanho da arvore + espaco para o caractere "\0"
    unsigned int altura = retAlturaCelula(l) + 1;

    unsigned char **dicionario = criaDicionario(l, altura);

    unsigned char *txtCodificado = codificaArquivo(dicionario, fp, altura);

    fclose(fp);

    stringArvore(l, dir);

    compactaArquivo(txtCodificado, dir);

    liberaStrings(dicionario);
    free(txtCodificado);
    liberaLista(l);
    free(vetFreq);
    free(dir);

    return 0;

}