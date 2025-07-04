// Feito dia 03/07/2025
// Yuri Tressmann Mutz
// Todos os direitos reservados

#ifndef REC_H
#define REC_H

#include "lista.h"
#include "leitor.h"
#include "livro.h"

/*Tipo que define uma recomendacao (tipo opaco)
 *Cada recomendacao deve ter os seguintes atributos:
 * * Um leitor que faz a recomendacao;
 * * Um livro que foi recomendado;
 * */
typedef struct Rec Rec;

/* Cria uma recomendacao com um leitor e um livro;
* inputs: Livro e Leitor a ser adicionados;
* output: Recomendacao criada com os ponteiros diferentes de NULL;
* pre-condicao: livro e leitor ja alocados;
* pos-condicao: Recomendacao criada com os ponteiros diferentes de NULL */
Rec *criaRec(Livro *livro, Leitor *leitor);

/* Libera a memoria alocada em uma recomendacao. Nao libera o livro nem o leitor;
* inputs: Recomendacao;
* output: vazio
* pre-condicao: Recomendacao criada;
* pos-condicao: Toda memoria alocada em um recomendacao liberada;  */
void liberaRec(Rec *rec);

/* Imprime o conteudo de uma recomendacao;
* inputs: Recomendacao;
* output: vazio
* pre-condicao: Recomendacao criada;
* pos-condicao: Sem mudanca; */
void imprimeRec(Rec *rec);

/* Compara os id's do livro e do leitor de uma recomendacao com os do parametros respectivamente;
* inputs: Recomendacao ja criada, um id de um livro, um id de um leitor;
* output: 1 se a recomendacao existir, 0 caso contrario;
* pre-condicao: Recomendacao criada, id's validos;
* pos-condicao: Sem mudanca; */
int comparaRec(Rec *l, int idLivro, int idLeitor);

#endif