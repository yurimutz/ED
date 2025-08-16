#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "bitmap.h"
#include "lista.h"

void leArquivo(int *vetFreq, FILE *fp){

    unsigned char aux;
    while(fread(&aux, sizeof(unsigned char), 1, fp) == 1){
        
        vetFreq[aux]++;
        
    }

}

unsigned int descobreTamString(FILE *fp, unsigned char **dic, unsigned int altura){

    unsigned int tam = 0;

    unsigned char aux;
    while(fread(&aux, sizeof(unsigned char), 1, fp) == 1){
        
        //tam = tam + strlen(dic[aux]);
        tam = tam + altura;
        
    }

    //+1 para o caractere '\0
    return tam + 1;

}

unsigned char *codificaArquivo(unsigned char **dic, FILE *fp, unsigned int altura){

    fseek(fp, 0, SEEK_SET);

    unsigned char *txtCodificado = calloc(descobreTamString(fp, dic, altura)+1, sizeof(char));

    // fseek(fp, 0, SEEK_SET);

    // unsigned char aux;
    // while(fread(&aux, sizeof(char), 1, fp) == 1){
        
    //     strcat(txtCodificado, dic[aux]);
           
    // }

    // return txtCodificado;

    //3. [A GRANDE MUDANÇA] Cria um ponteiro para a posição atual de escrita
    unsigned char *ponteiro_atual = txtCodificado;

    // 4. Segunda passada para codificar
    fseek(fp, 0, SEEK_SET);
    
    unsigned char aux;
    while(fread(&aux, sizeof(unsigned char), 1, fp) == 1){
        // Pega o código de Huffman para o caractere lido
        unsigned char* codigo = dic[aux];
        int tam_codigo = strlen(codigo);

        // 5. [A GRANDE MUDANÇA] Copia o código diretamente para a posição atual
        memcpy(ponteiro_atual, codigo, tam_codigo);
        
        // 6. Avança o ponteiro para o final dos dados recém-copiados
        ponteiro_atual += tam_codigo;
    }

    // O '\0' final já está garantido pelo uso do calloc
    return txtCodificado;


}

void compactaArquivo(unsigned char *codificado){

    int j=0;

    unsigned int tamUtil = strlen(codificado);

    unsigned tamTotal = tamUtil;
    while(tamTotal % 8 != 0){

        tamTotal++;

    }

    bitmap *bitmap = bitmapInit(tamTotal);

    for(int i=0; i < tamUtil; i++){

        bitmapAppendLeastSignificantBit(bitmap, codificado[i]);

    }

    FILE *fp = fopen("saida.txt", "ab");

    //tamanho util do dado compactado
    fwrite(&tamUtil, sizeof(int), 1, fp);
    //tamanho total do dado compactado (multiplo de 8 para formar bytes);
    fwrite(&tamTotal, sizeof(int), 1, fp);
    fwrite(bitmapGetContents(bitmap), sizeof(char), tamTotal/8, fp);

    bitmapLibera(bitmap);
    fclose(fp);

}

bitmap *funcaoTeste(unsigned int tamUtil, unsigned int tamTotal, unsigned char *conteudo){

    bitmap *bm = bitmapInit(tamTotal+1);

    for(unsigned int i=0; i < tamTotal/8; i++){

        appendNovo(bm, conteudo[i]);

    }

    return bm;

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
    //printf("%s", dir);

    unsigned int *vetFreq = calloc(256, sizeof(int));

    //FILE *fp = fopen("entrada.txt", "r");
    FILE *fp = fopen(dir, "r");

    leArquivo(vetFreq, fp);

    Lista *l = criaLista();

    l = criaListaOrdenada(l, vetFreq);

    criaArvoreHuff(l);

    //tamanho da arvore + espaco para o caractere "\0"
    unsigned int altura = retAlturaCelula(l) + 1;

    unsigned char **dicionario = criaDicionario(l, altura);

    unsigned char *txtCodificado = codificaArquivo(dicionario, fp, altura);

    fclose(fp);

    stringArvore(l);

    compactaArquivo(txtCodificado);

    FILE *fp2 = fopen("saida.txt", "rb");

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

    decodificaFinal2(arvNovo, bitmapString, tamUtil2);

    fclose(fp2);

    liberaStrings(dicionario);
    free(txtCodificado);
    free(strAux);
    free(stringDec);
    bitmapLibera(bitmapString);
    bitmapLibera(bitmapArv);
    liberaLista(l);
    abb_libera(arvNovo);
    free(vetFreq);
    free(dir);

    return 0;

}