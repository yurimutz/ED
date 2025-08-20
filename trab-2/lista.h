#ifndef LISTA
#define LISTA

#include "arvore.h" // Dependência da estrutura da árvore

// Declarações opacas para as estruturas de Lista e Célula.
// Os detalhes de implementação estão em lista.c.
typedef struct Lista Lista;
typedef struct Celula Celula;

/**
 * @brief Cria e inicializa uma nova lista vazia.
 * @return Um ponteiro para a lista recém-criada.
 */
Lista *criaLista();

/**
 * @brief Libera toda a memória alocada para a lista e seus elementos.
 * Isso inclui a liberação das árvores contidas em cada célula.
 * @param l A lista a ser liberada.
 */
void *liberaLista(Lista *l);

/**
 * @brief Remove e retorna a primeira célula da lista.
 * @param l A lista da qual a célula será retirada.
 * @return Um ponteiro para a célula retirada, ou NULL se a lista estiver vazia.
 */
Celula *retiraPrimeiro(Lista *l);

/**
 * @brief Insere um nó de árvore na lista de forma ordenada (crescente) por frequência.
 * @param l A lista onde a árvore será inserida.
 * @param a O nó da árvore a ser inserido.
 */
void insereListaOrdenado(Lista *l, Arv *a);

/**
 * @brief Insere uma célula já existente no final da lista.
 * @param l A lista.
 * @param cel A célula a ser inserida.
 */
void *insereCelula(Lista *l, Celula *cel);

/**
 * @brief Cria um novo nó pai de Huffman a partir de duas células (contendo sub-árvores)
 * e insere o novo nó de volta na lista de forma ordenada.
 * @param l A lista.
 * @param esq A célula contendo a sub-árvore esquerda.
 * @param dir A célula contendo a sub-árvore direita.
 */
void insereCelulasHuff(Lista *l, Celula *esq, Celula *dir);

/**
 * @brief Constrói a árvore de Huffman completa a partir da lista ordenada de nós.
 * Ao final do processo, a lista conterá apenas um elemento: a raiz da árvore de Huffman.
 * @param l A lista contendo os nós iniciais.
 */
void criaArvoreHuff(Lista *l);

/**
 * @brief Retorna a altura da árvore de Huffman contida na lista (após sua construção).
 * @param l A lista (que deve conter apenas a raiz da árvore).
 * @return A altura da árvore.
 */
unsigned int retAlturaCelula(Lista *l);

/**
 * @brief Cria o dicionário de códigos de Huffman (mapa de char para string de bits).
 * @param a A lista contendo a árvore de Huffman completa.
 * @param altura A altura da árvore, usada para alocação de memória.
 * @return Um array de strings (char**) onde o índice corresponde ao valor do byte.
 */
unsigned char **criaDicionario(Lista *a, unsigned int altura);

/**
 * @brief Serializa a estrutura da árvore de Huffman e a escreve no início de um arquivo compactado.
 * @param l A lista contendo a árvore de Huffman.
 * @param dir O caminho para o arquivo de saída.
 */
void stringArvore(Lista *l, char *dir);

/**
 * @brief Cria uma lista ordenada de nós (folhas) a partir de um vetor de frequências.
 * Para cada caractere com frequência > 0, um nó é criado e inserido na lista.
 * @param l A lista (inicialmente vazia).
 * @param vetFreq O vetor de frequências de caracteres.
 * @return A lista preenchida e ordenada.
 */
Lista *criaListaOrdenada(Lista *l, unsigned int *vetFreq);

#endif