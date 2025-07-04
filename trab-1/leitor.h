// Feito dia 09/06/2025
// Yuri Tressmann Mutz
// Todos os direitos reservados

#ifndef LEITOR_H
#define LEITOR_H

#include <stdio.h>
#include "lista.h"

/*Tipo que define Leitor (tipo opaco)
 *Cada Leitor deve ter os seguintes atributos:
 * * Um id;
 * * Um nome;
 * * O numero de afinidades que ele possui;
 * * Uma matriz de char que armazena essas afinidades;
 * * Uma Lista com os livros lidos;
 * * Uma Lista com os livros desejados;
 * * Uma Lista com os livros recomendados;
 * * Uma Lista com as recomendacoes feitas;
 * * Uma Lista com os leitores que possui afinidade direta;
 * */
typedef struct Leitor Leitor;

/* Cria um Leitor
* inputs: Dois inteiros (id e nAfinidades). String nome alocada dinamicamente. Arquivo fp;
* output: Leitor criado; 
* pre-condicao: String parametro alocada dinamicamente, arquivo fp ja aberto;
* pos-condicao: Livro criado  */
Leitor *criaLeitor(int id, char *nome, int nAfinidades, FILE *fp);

/* Le as informacoes de um Leitor do arquivo fp;
* inputs: Um arquivo ja aberto;
* output: Leitor criado; 
* pre-condicao: O arquivo ja deve vir aberto;
* pos-condicao: Leitor criado  */
Leitor *leLeitor(FILE *fp);

/* Le uma string de um arquivo e aloca uma string dinamicamente, a qual ira receber essa informacao;
* inputs: Um arquivo ja aberto;
* output: String dinamicamente criado com um conteudo valido; 
* pre-condicao: O arquivo ja deve vir aberto;
* pos-condicao: String dinamicamente criado com um conteudo valido; */
char *leLinha(FILE *fp);

/* Libera toda a memoria alocada em um Leitor;
* inputs: Um Leitor ja criado;
* output: Vazio; 
* pre-condicao: Leitor != NULL;
* pos-condicao: Toda a memoria de um Leitor liberada; */
void liberaLeitor(Leitor *l);

/* Imprime as informacoes de um Leitor;
* inputs: Um Leitor ja criado, um arquivo ja aberto;
* output: Informacoes impressas em um arquivo; 
* pre-condicao: Leitor != NULL, arquivo ja aberto;
* pos-condicao: Sem mudanca; */
void imprimeLeitor(Leitor *l, FILE *fp);

/* Imprime as informacoes de um Leitor;
* inputs: Um Leitor ja criado;
* output: Vazio; 
* pre-condicao: Leitor != NULL;
* pos-condicao: Sem mudanca; */
void imprimeLeitor2(Leitor *l);

/* Retorna o id de um Leitor;
* inputs: Um Leitor ja criado;
* output: Id do Leitor passado no parametro; 
* pre-condicao: Leitor != NULL;
* pos-condicao: Sem mudanca; */
int retId(Leitor *l);

/* Retorna a lista Lidos de um Leitor;
* inputs: Um Leitor ja criado;
* output: Lista lidos; 
* pre-condicao: Leitor != NULL;
* pos-condicao: Sem mudanca; */
Lista *retListaLidosLeitor(Leitor *l);

/* Retorna a lista Desejados de um Leitor;
* inputs: Um Leitor ja criado;
* output: Lista lidos; 
* pre-condicao: Leitor != NULL;
* pos-condicao: Sem mudanca; */
Lista *retListaDesejadosLeitor(Leitor *l);

/* Retorna a lista Recomendados de um Leitor;
* inputs: Um Leitor ja criado;
* output: Lista lidos; 
* pre-condicao: Leitor != NULL;
* pos-condicao: Sem mudanca; */
Lista *retListaRecomendadosLeitor(Leitor *l);

/* Retorna a lista leitoresComAfinidade de um Leitor;
* inputs: Um Leitor ja criado;
* output: Lista leitoresComAfinidade; 
* pre-condicao: Leitor != NULL;
* pos-condicao: Sem mudanca; */
Lista *retListaLeitoresComAfinidadeLeitor(Leitor *l);

/* Retorna a lista recProd de um Leitor;
* inputs: Um Leitor ja criado;
* output: Lista recProd; 
* pre-condicao: Leitor != NULL;
* pos-condicao: Sem mudanca; */
Lista *retRecProd(Leitor *l);

/* Retorna o nome de um Leitor;
* inputs: Um Leitor ja criado;
* output: Nome do Leitor passado no parametro; 
* pre-condicao: Leitores != NULL;
* pos-condicao: Sem mudanca; */
char *retLeitorNome(Leitor *l);

/* Percorre as matrizes afinidade de dois leitores e verifica se ocorre semelhanca;
* inputs: Dois Leitores ja criados;
* output: 1 se existe afinidade, 0 caso contrario; 
* pre-condicao: Leitores != NULL;
* pos-condicao: Sem mudanca; */
int verficaAfinidade(Leitor *l1, Leitor *l2);

/* Percorre as listas LeitoresComAfinidade de dois leitores e verifica se ocorre semelhanca;
* inputs: Dois Leitores ja criados;
* output: 1 se existe afinidade, 0 caso contrario; 
* pre-condicao: Leitores != NULL;
* pos-condicao: Sem mudanca; */
int verificaListaLeitoresComAfinidade(Leitor *l1, Leitor *l2);

/* Percorre as listas LeitoresComAfinidade de dois leitores e verifica se ocorre semelhanca, ocorre de maneira recursiva;
   Caso nao ocorra afinidade em um no, a Lista visitados recebe a celula atual e a celula atual e atualizada para o proximo ciclo;
* inputs: Dois Leitores ja criados, uma Lista ja criada(na primeira chamada ela esta vazia);
* output: 1 se existe afinidade, 0 caso contrario; 
* pre-condicao: Leitores != NULL, Lista != NULL;
* pos-condicao: Sem mudanca; */
int buscaProfundidade(Leitor *l1, Leitor *l2, Lista *visitados);

/* Compara os id's de dois livros;
* inputs: Dois livros ja criados;
* output: 1 se igual, 0 caso contrario; 
* pre-condicao: Livros != NULL;
* pos-condicao: Sem mudanca; */
int comparaIdLeitor(Leitor *l1, Leitor *l2);

#endif