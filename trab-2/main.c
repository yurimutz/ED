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

void compactaArquivo(unsigned char *codificado){

    int j=0;

    unsigned int tam = strlen(codificado);

    while(tam % 8 != 0){

        tam++;

    }

    bitmap *bitmap = bitmapInit(tam);

    for(int i=0; i < strlen(codificado); i++){

        bitmapAppendLeastSignificantBit(bitmap, codificado[i]);

    }

    FILE *fp = fopen("saida.txt", "ab");

    int tamAux = strlen(codificado);

    //tamanho util do dado compactado
    fwrite(&tamAux, sizeof(int), 1, fp);
    //tamanho total do dado compactado (multiplo de 8 para formar bytes);
    fwrite(&tam, sizeof(int), 1, fp);
    fwrite(bitmapGetContents(bitmap), sizeof(char), tam/8, fp);

    fclose(fp);

}

bitmap *funcaoTeste(int tamUtil, int tamTotal, char *conteudo){

    bitmap *bm = bitmapInit(tamTotal);

    for(int i=0; i < tamTotal/8; i++){

        appendNovo(bm, conteudo[i]);

    }

    return bm;

}

int main(){

    int *vetFreq = calloc(256, sizeof(int));

    FILE *fp = fopen("entrada.txt", "r");

    leArquivo(vetFreq, fp);

    Lista *l = criaLista();

    l = criaListaOrdenada(l, vetFreq);

    criaArvoreHuff(l);

    //tamanho da arvore + espaco para o caractere "\0"
    int altura = retAlturaCelula(l) + 1;

    unsigned char **dicionario = criaDicionario(l, altura);

    unsigned char *txtCodificado = codificaArquivo(dicionario, fp);

    //printf("%s\n", txtCodificado);

    unsigned char *txtDecodificado = decodificaArquivo(l, txtCodificado, fp);

    fclose(fp);

    stringArvore(l);

    compactaArquivo(txtCodificado);

    FILE *fp2 = fopen("saida.txt", "rb");

    int tamTotal=0, tamUtil=0;

    fread(&tamUtil, sizeof(int), 1, fp2);
    fread(&tamTotal, sizeof(int), 1, fp2);

    //printf("%d %d\n", tamUtil, tamTotal);

    unsigned char *strAux = malloc((tamTotal+1) * sizeof(char));

    fread(strAux, sizeof(unsigned char), tamTotal/8, fp2);

    int tamTotal2=0, tamUtil2=0;

    fread(&tamUtil2, sizeof(int), 1, fp2);
    fread(&tamTotal2, sizeof(int), 1, fp2);

    unsigned char *stringDec = malloc(sizeof(tamTotal2+1) * sizeof(char));

    fread(stringDec, sizeof(unsigned char), tamTotal2/8, fp2);

    //printf("%s", stringDec);
    //printf("%d %d\n", tamUtil2, tamTotal2);

    bitmap *bitmapArv = funcaoTeste(tamUtil, tamTotal, strAux);

    bitmap *bitmapString = funcaoTeste(tamUtil2, tamTotal2, stringDec);

    int indice = 0;
    Arv * arvNovo = recriaArvore(bitmapArv, &indice);

    decodificaFinal2(arvNovo, bitmapString, tamUtil2);
    //abb_imprime (arvNovo);
    //imprimeLista(l);

    fclose(fp2);

    

    return 0;

}