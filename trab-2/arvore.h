#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h" // Dependência para operações com bitmaps

// Define um apelido 'Arv' para a estrutura 'struct arv' (cuja definição está em arvore.c).
// Esta é uma declaração opaca, escondendo os detalhes de implementação.
typedef struct arv Arv;

/**
 * @brief Cria um nó folha para a árvore.
 * @param frequencia A frequência do caractere.
 * @param carac O caractere (byte) associado ao nó.
 * @return Um ponteiro para o novo nó da árvore criado.
 */
Arv* arv_cria (unsigned int frequencia, unsigned char carac);

/**
 * @brief Cria um nó interno (não folha) da árvore de Huffman.
 * A frequência deste nó será a soma das frequências dos seus filhos.
 * @param esq Ponteiro para a sub-árvore esquerda.
 * @param dir Ponteiro para a sub-árvore direita.
 * @return Um ponteiro para o novo nó interno criado.
 */
Arv* arvCriaNaoVazia(Arv *esq, Arv *dir);

/**
 * @brief Libera toda a memória alocada para a árvore e seus descendentes.
 * @param a Ponteiro para a raiz da árvore a ser liberada.
 * @return Retorna NULL.
 */
Arv* abb_libera (Arv* a);

/**
 * @brief Retorna a frequência armazenada em um nó da árvore.
 * @param a Ponteiro para o nó da árvore.
 * @return A frequência do nó.
 */
unsigned int retFrequencia(Arv *a);

/**
 * @brief Retorna o caractere armazenado em um nó da árvore (geralmente um nó folha).
 * @param a Ponteiro para o nó da árvore.
 * @return O caractere (byte) do nó.
 */
unsigned char retCarac(Arv *a);

/**
 * @brief Calcula a altura da árvore.
 * @param a Ponteiro para a raiz da árvore.
 * @return A altura da árvore. Uma árvore vazia tem altura -1.
 */
unsigned int altura(Arv* a);

/**
 * @brief Preenche recursivamente um dicionário (array de strings) com os códigos de Huffman.
 * Percorre a árvore e constrói os códigos binários para cada caractere (nó folha).
 * @param dic O dicionário a ser preenchido.
 * @param a O nó atual da árvore na recursão.
 * @param conteudo O código binário construído até o momento.
 * @param altura A altura da árvore, usada para alocar memória para os códigos.
 */
void preencheDicionario(unsigned char **dic, Arv *a, unsigned char *conteudo, unsigned int altura);

/**
 * @brief Decodifica uma sequência de bits (armazenada em um bitmap) usando a árvore de Huffman.
 * @param a A raiz da árvore de Huffman.
 * @param bm O bitmap contendo os dados compactados.
 * @param tamUtil O número de bits úteis no bitmap.
 * @param dir O caminho do arquivo de saída onde o conteúdo decodificado será salvo.
 * @return Um ponteiro para a string decodificada (embora o código atual a libere internamente).
 */
unsigned char *decodificaFinal2(Arv *a, bitmap *bm, unsigned int tamUtil, char *dir);

/**
 * @brief Reconstrói a árvore de Huffman a partir de sua representação em um bitmap.
 * @param bm O bitmap que contém a estrutura da árvore serializada.
 * @param tamAtual Um ponteiro para um índice que rastreia a posição de leitura atual no bitmap.
 * @param tamUtil O número total de bits úteis na representação da árvore.
 * @return Um ponteiro para a raiz da árvore reconstruída.
 */
Arv *recriaArvore(bitmap *bm, unsigned int *tamAtual, unsigned int tamUtil);

/**
 * @brief Calcula o tamanho em bits necessário para representar (serializar) a árvore.
 * @param a A raiz da árvore.
 * @return O número de bits necessários para a representação.
 */
unsigned int calculaTamanhoArvore(Arv* a);

/**
 * @brief Cria uma representação em string da estrutura da árvore para serialização.
 * '0' representa um nó interno, '1' seguido pelo caractere representa um nó folha.
 * @param a A raiz da árvore.
 * @param buffer O buffer onde a string será armazenada.
 * @param indice Um ponteiro para o índice da posição atual no buffer.
 */
void criaStringArvore_Manual(Arv* a, unsigned char* buffer, unsigned int* indice);

#endif