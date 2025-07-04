// Feito dia 09/06/2025
// Yuri Tressmann Mutz
// Todos os direitos reservados

#ifndef LIVRO_H
#define LIVRO_H

#include <stdio.h>

/*Tipo que define livro (tipo opaco)
 *Cada livro deve ter os seguintes atributos:
 * * Um id;
 * * Um titulo;
 * * Um autor;
 * * Um genero;
 * * Um ano
 * */
typedef struct Livro Livro;

/* Cria um livro
* inputs: Dois inteiros (id e ano). Strings alocadas dinamicamente (titulo, autor, genero);
* output: Livro criado e com seus atributos iguais aos dos parametros; 
* pre-condicao: Strings parametro alocadas dinamicamente;
* pos-condicao: Livro criado  */
Livro *criaLivro(int id, char *titulo, char *autor, char *genero, int ano);

/* Le as informacoes de um livro do arquivo fp;
* inputs: Um arquivo ja aberto;
* output: Livro criado; 
* pre-condicao: O arquivo ja deve vir aberto;
* pos-condicao: Livro criado  */
Livro *leLivro(FILE *fp);

/* Le uma string de um arquivo e aloca uma string dinamicamente, a qual ira receber essa informacao;
* inputs: Um arquivo ja aberto;
* output: String dinamicamente criado com um conteudo valido; 
* pre-condicao: O arquivo ja deve vir aberto;
* pos-condicao: String dinamicamente criado com um conteudo valido; */
char *leLinha2(FILE *fp);

/* Libera toda a memoria alocada em um livro;
* inputs: Um livro ja criado;
* output: Vazio; 
* pre-condicao: Livro != NULL;
* pos-condicao: Toda a memoria de um livro liberada; */
void liberaLivro(Livro *l);

/* Imprime as informacoes de um livro;
* inputs: Um livro ja criado;
* output: Vazio; 
* pre-condicao: Livro != NULL;
* pos-condicao: Sem mudanca; */
void imprimeLivro(Livro *l);

/* Retorna o id de um livro;
* inputs: Um livro ja criado;
* output: Id do livro passado no parametro; 
* pre-condicao: Livro != NULL;
* pos-condicao: Sem mudanca; */
int retIdLivro(Livro *l);

/* Retorna o titulo de um livro;
* inputs: Um livro ja criado;
* output: Titulo do livro passado no parametro; 
* pre-condicao: Livro != NULL;
* pos-condicao: Sem mudanca; */
char *retLivroTitulo(Livro *l);

/* Compara os id's de dois livros;
* inputs: Dois livros ja criados;
* output: 1 se igual, 0 caso contrario; 
* pre-condicao: Livros != NULL;
* pos-condicao: Sem mudanca; */
int comparaIdLivro(Livro *l1, Livro* l2);

#endif