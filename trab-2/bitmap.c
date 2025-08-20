/** Define um TAD representando um mapa de bits.
 * @file bitmap.c
 * @author Joao Paulo Andrade Almeida (jpalmeida@inf.ufes.br)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bitmap.h"

struct map {
    unsigned int max_size;        ///< tamanho maximo em bits
    unsigned int length;         ///< tamanho atual em bits
    unsigned char* contents;     ///< conteudo do mapa de bits
};

/**
 * Funcao auxiliar que imprime uma mensagem de falha e aborta o programa caso testresult seja falso.
 * @param testresult Valor booleano representando o resultado do teste que deveria ser verdadeiro.
 * @param message A mensagem para ser impressa se resultado do teste for falso.
 */
void assert(int testresult, char* message) {
	if (!testresult) {
		printf("%s\n", message);
		exit(EXIT_FAILURE);
	}
}


/**
 * Retorna o conteudo do mapa de bits.
 * @param bm O mapa de bits.
 */
unsigned char* bitmapGetContents(bitmap* bm) {
	return bm->contents;
}

/**
 * Retorna o tamanho maximo do mapa de bits.
 * @param bm O mapa de bits.
 * @return O tamanho maximo do mapa de bits.
 */
unsigned int bitmapGetMaxSize(bitmap* bm) {
	return bm->max_size;
}

/**
 * Retorna o tamanho atual do mapa de bits.
 * @param bm O mapa de bits.
 * @return O tamanho atual do mapa de bits.
 */
unsigned int bitmapGetLength(bitmap* bm) {
	return bm->length;
}

/**
 * Constroi um novo mapa de bits, definindo um tamanho maximo.
 * @param max_size O tamanho maximo para o mapa de bits.
 * @return O mapa de bits inicializado.
 */
bitmap* bitmapInit(unsigned int max_size) {
	bitmap* bm;
    bm = (bitmap*)malloc(sizeof(bitmap));
	// definir tamanho maximo em bytes, com arredondamento para cima
	unsigned int max_sizeInBytes=(max_size+7)/8;
	// alocar espaco de memoria para o tamanho maximo em bytes
	bm->contents=calloc(max_sizeInBytes, sizeof(char));
	// verificar alocacao de memoria
	assert(bm->contents!=NULL, "Erro de alocacao de memoria.");
	// definir valores iniciais para tamanho maximo e tamanho atual
	bm->max_size=max_size;
	bm->length=0;
	return bm;
}

/**
 * Retorna o valor do bit na posicao index.
 * @param bm O mapa de bits.
 * @param index A posicao do bit.
 * @pre index<bitmapGetLength(bm)
 * @return O valor do bit.
 */
unsigned char bitmapGetBit(bitmap* bm, unsigned int index) // index in bits
{
	// verificar se index<bm.length, pois caso contrario, index e' invalido
	assert(index<bm->length, "Acesso a posicao inexistente no mapa de bits.");
	// index/8 e' o indice do byte que contem o bit em questao
	// 7-(index%8) e' o deslocamento do bit em questao no byte
	return (bm->contents[index/8] >> (7-(index%8))) & 0x01;
}

/**
 * Modifica o valor do bit na posicao index.
 * @param bm O mapa de bits.
 * @param index A posicao do bit.
 * @param bit O novo valor do bit.
 * @post bitmapGetBit(bm,index)==bit
 */
static void bitmapSetBit(bitmap* bm, unsigned int index, unsigned char bit) {
    // verificar se index<bm->length, pois caso contrario, index e' invalido
    assert(index<bm->length, "Acesso a posicao inexistente no mapa de bits.");
    // index/8 e' o indice do byte que contem o bit em questao
    // 7-(index%8) e' o deslocamento do bit em questao no byte
    bit=bit & 0x01;
    bit=bit<<(7-(index%8));
    bm->contents[index/8]= bm->contents[index/8] | bit;
}


/**
 * Adiciona um bit no final do mapa de bits.
 * @param bm O mapa de bits.
 * @param bit O novo valor do bit.
 * @pre bitmapGetLength(bm) < bitmapGetMaxSize(bm)
 * @post (bitmapGetBit(bm,bitmapGetLength(bm) @ pre)==bit) 
 * and (bitmapGetLength(bm) == bitmapGetLength(bm) @ pre+1)
 */
void bitmapAppendLeastSignificantBit(bitmap* bm, unsigned char bit) {
	// verificar se bm->length<bm->max_size, caso contrario, o bitmap esta' cheio
	assert(bm->length<bm->max_size, "Tamanho maximo excedido no mapa de bits.");
	// como um bit sera' adicionado, devemos incrementar o tamanho do mapa de bits
	bm->length++;
	bitmapSetBit(bm, bm->length-1, bit);
}

void appendNovo(bitmap *bm, unsigned char byte){

	// 1. Garante que há espaço para mais 8 bits.
    assert((bitmapGetLength(bm) + 8) <= bitmapGetMaxSize(bm), "Tamanho maximo excedido no mapa de bits.");

    // 2. Itera por cada bit do byte, do mais significativo (MSB) para o menos significativo (LSB).
    // O loop vai de 7 a 0 para pegar os bits na ordem correta (da esquerda para a direita).
    for (int i = 7; i >= 0; i--) {
        // 3. Isola o bit na posição 'i'.
        //    (byte >> i) -> Desloca o bit de interesse para a posição mais à direita.
        //    & 0x01    -> Zera todos os outros bits, deixando apenas o bit que queremos.
        unsigned char bit = (byte >> i) & 0x01;

        // 4. Adiciona o bit isolado ao final do bitmap usando a função existente.
        //    Esta função já cuida de incrementar o bm->length e de setar o bit
        //    na posição correta.
        bitmapAppendLeastSignificantBit(bm, bit);
    }

}

/**
 * Libera a memória dinâmica alocada para o mapa de bits.
 * @param bm O mapa de bits.
 */
void bitmapLibera (bitmap* bm){
    
    free (bm->contents);
    free (bm);
}

unsigned char lerByteInteiro(bitmap* bm, unsigned int indice_inicial){

    assert((indice_inicial + 8) <= bitmapGetLength(bm), "Tentativa de ler alem dos limites do bitmap.");

    unsigned char byte_resultante = 0;

    for (int i = 0; i < 8; i++) {

        unsigned char bit = bitmapGetBit(bm, indice_inicial + i);
        byte_resultante = (byte_resultante << 1) | bit;

    }

    return byte_resultante;
}