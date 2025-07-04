// Feito dia 09/06/2025
// Yuri Tressmann Mutz
// Todos os direitos reservados

#ifndef LISTA
#define LISTA

#include <stdio.h>

#define LIVRO 0
#define LEITOR 1
#define REC 2

/*Tipo que define uma Lista (tipo opaco)
 *Cada Lista deve ter os seguintes atributos:
 * * Celula que marca o incio da lista;
 * * Celula que marca o fim da lista;
 * */
typedef struct Lista Lista;

/*Tipo que define uma Celula (tipo opaco)
 *Cada Lista deve ter os seguintes atributos:
 * * Celula que marca o incio da lista;
 * * O tipo da celula(0 se LIVRO, 1 se LEITOR, 2 se REC);
 * * Uma Celula que marca a proxima no encadeamento;
 * */
typedef struct Celula Celula;

/* Cria uma lista (aloca dinamicamente) e aponta as celulas INICIO e FIM para NULL;
* inputs: Vazio;
* output: Lista criada; 
* pre-condicao: Vazio;
* pos-condicao: Lista dinamicamente criada  */
Lista *criaLista();

/* Libera toda a memoria alocada em uma Lista, incluindo o prod de uma celula;
* inputs: Uma Lista ja criada;
* output: Vazio; 
* pre-condicao: Lista != NULL;
* pos-condicao: Toda a memoria de uma Lista liberada; */
void liberaLista(Lista *l);

/* Libera a memoria alocada em uma Lista e em suas celulas, prod continua alocado;
* inputs: Uma Lista ja criada;
* output: Vazio; 
* pre-condicao: Lista != NULL;
* pos-condicao: Apenas a memoria de uma Lista e de suas celulas liberada; */
void liberaExterno(Lista *l);

/* Imprime, caso seja tipo Leitor, o nome de um Leitor e, caso seja um livro, o titulo em um arquivo;
* inputs: Uma lista ja criada, um arquivo ja aberto;
* output: Informacoes impressas em um arquivo; 
* pre-condicao: Leitor != NULL, arquivo ja aberto;
* pos-condicao: Sem mudanca; */
void imprimeLista(Lista *l, FILE *fp);

/* Imprime, caso seja tipo Leitor, o nome de um Leitor e, caso seja um livro, o titulo em um arquivo;
* inputs: Uma lista ja criada, um arquivo ja aberto;
* output: Informacoes impressas em um arquivo; 
* pre-condicao: Leitor != NULL, arquivo ja aberto;
* pos-condicao: Sem mudanca; */
void imprimeBookED(Lista *l, FILE *fp);

/* Verifica se existe uma celula na lista que tenha o mesmo nome passado no parametro. Caso exista, retira ela da lista e retorna para outro uso;
* inputs: Uma lista ja criada, um nome alocado dinamicamente;
* output: Se encontrar, retorna a celula, caso contrario, retorna NULL; 
* pre-condicao: Lista != NULL, nome alocado dinamicamente;
* pos-condicao: Se encontar, lista sem a celula; */
Celula *retiraLista(Lista *l, char *nome);

/* Aloca uma celula, atribui as informacoes passadas como parametro nela e a insere numo lista;
* inputs: Uma lista ja criada, um prod ja criado, o tipo do prod;
* output: Vazio; 
* pre-condicao: Lista != NULL, prod ja criado;
* pos-condicao: Lista com uma nova celula que contenha o prod passado como parametro; */
void *insereLista(Lista *l, void *p, int tipo);

/* Aloca uma celula, atribui as informacoes da celula passada como parametro nela e a insere numo lista;
* inputs: Uma lista ja criada, uma celula ja criada;
* output: Vazio; 
* pre-condicao: Lista != NULL, uma celula ja criada;
* pos-condicao: Lista com uma nova celula que contenha as informacoes da celula passada como parametro; */
void *insereCelula(Lista *l, Celula *cel);

/* Compara o id passado como parametro com as da celulas de uma lista. Caso ocorra semelhanca, retorna a celula encontrada;
* inputs: Uma lista ja criada, um id;
* output: Se encontrar, uma celula, caso contrario, NULL; 
* pre-condicao: Lista != NULL;
* pos-condicao: Sem mudanca na estrutura; */
Celula *busca(Lista *l, int id);

/* Retorna o id de uma Celula (nesse caso, de um livro);
* inputs: Uma Celula ja criada;
* output: Id da celula passada no parametro; 
* pre-condicao: Celula != NULL;
* pos-condicao: Sem mudanca; */
int retIdLivroLista(Celula *l);

/* Retorna a lista Lidos de uma Celula(nesse caso, de um leitor);
* inputs: Uma Celula ja criada;
* output: Lista lidos; 
* pre-condicao: Celula != NULL;
* pos-condicao: Sem mudanca; */
Lista *retListaLidos(Celula *cel);

/* Retorna a lista Desejados de uma Celula(nesse caso, de um leitor);
* inputs: Uma Celula ja criada;
* output: Lista Desejados; 
* pre-condicao: Celula != NULL;
* pos-condicao: Sem mudanca; */
Lista *retListaDesejados(Celula *cel);

/* Retorna a lista Recomendados de uma Celula(nesse caso, de um leitor);
* inputs: Uma Celula ja criada;
* output: Lista Recomendados; 
* pre-condicao: Celula != NULL;
* pos-condicao: Sem mudanca; */
Lista *retListaRecomendados(Celula *cel);

/* Retorna a lista LeitoresComAfinidade de uma Celula(nesse caso, de um leitor);
* inputs: Uma Celula ja criada;
* output: Lista LeitoresComAfinidade; 
* pre-condicao: Celula != NULL;
* pos-condicao: Sem mudanca; */
Lista *retListaLeitoresComAfinidade(Celula *cel);

/* Retorna a lista RecProd de uma Celula(nesse caso, de um leitor);
* inputs: Uma Celula ja criada;
* output: Lista RecProd; 
* pre-condicao: Celula != NULL;
* pos-condicao: Sem mudanca; */
Lista *retListaRecProd(Celula *cel);

/* Retorna o titulo de uma celula (nesse caso, de um livro);
* inputs: Uma celula ja criado;
* output: Titulo da celula passada no parametro; 
* pre-condicao: Celula != NULL;
* pos-condicao: Sem mudanca; */
char *retLivroTituloLista(Celula *cel);

/* Retorna o nome de uma celula (nesse caso, de um leitor);
* inputs: Uma celula ja criado;
* output: Nome da celula passada no parametro; 
* pre-condicao: Celula != NULL;
* pos-condicao: Sem mudanca; */
char *retLeitorNomeLista(Celula *cel);

/* Compara a lista Lidos de duas celulas. Se tiver semelhanca, imprime que existe livros em comum, caso contrario, imprime que nao existe;
* inputs: Duas celulas ja criadas, um arquivo ja aberto;
* output: Vazio; 
* pre-condicao: Celula != NULL;
* pos-condicao: Sem mudanca; */
void *verificaLivrosEmComum(Celula *l1, Celula *l2, FILE *fp);

/* Percorre uma lista que contem todos o leitores e atualiza a lista LeitoresComAfinidadeLeitor;
* inputs: Lista ja criada;
* output: Vazio; 
* pre-condicao: Lista != NULL;
* pos-condicao: Listas LeitoresComAfinidadeLeitor preenchidas com os leitores que possuem afinidade direta (sem intermediarios) */
void adicionaAfinidades(Lista *l);

/* Verifica a existencia de afinidade entre duas celulas. Tambem realiza a verificacao com a existencia de intermediarios. Imprime os resultados em arquivo; 
* inputs: Duas celulas ja criadas, um arquivo ja aberto;
* output: Vazio; 
* pre-condicao: Celulas != NULL, arquivo ja aberto;
* pos-condicao: Listas LeitoresComAfinidadeLeitor preenchidas com os leitores que possuem afinidade direta (sem intermediarios) */
int verificaAfinidadeLista(Celula *l1, Celula *l2, FILE *fp);

/* Compara duas listas que contem leitores.; 
* inputs: Duas listas ja criadas;
* output: Se existe leitores em comum, 1, caso contrario, 0; 
* pre-condicao: Listas != NULL;
* pos-condicao: Sem mudanca; */
int encotraLeitorComum(Lista *l1, Lista *l2);

/* Compara os id's de duas celulas; 
* inputs: Duas celulas ja criadas;
* output: Se iguais, 1, caso contrario, 0; 
* pre-condicao: Celulas != NULL e do mesmo tipo;
* pos-condicao: Sem mudanca; */
int comparaIdsLista(Celula *l1, Celula *l2);

/* Retorna a primeira celula de uma lista; 
* inputs: Uma lista ja criada;
* output: Primeira celula de uma lista; 
* pre-condicao: Lista != NULL;
* pos-condicao: Sem mudanca; */
Celula *retPrimeiraCelula(Lista *l1);

/* Retorna a proxima celula da celula->inicio de uma lista; 
* inputs: Uma lista ja criada;
* output: Proxima celula da celula->inicio; 
* pre-condicao: Lista != NULL;
* pos-condicao: Sem mudanca; */
Celula *retProximaCelula(Celula *l1);

/* Retorna o id de uma Celula (retorna tanto de um livro como de um leitor);
* inputs: Uma Celula ja criada;
* output: Id da celula passada no parametro; 
* pre-condicao: Celula != NULL;
* pos-condicao: Sem mudanca; */
int retIdLista(Celula *l1);

/* Retorna o prod de uma Celula;
* inputs: Uma Celula ja criada;
* output: O prod da celula passada como parametro; 
* pre-condicao: Celula != NULL;
* pos-condicao: Sem mudanca; */
void *retProdLista(Celula *l1);

/* Verifica se existe uma recomendacao com os id's passados como parametro. Ambos precisam estar na mesma recomendacao para ser True;
* inputs: Uma Lista ja criada, um id de um livro, um id e um leitor que realizou recomendacao;
* output: 1 se existir a recomendacao, 0 caso contrario; 
* pre-condicao: Lista != NULL;
* pos-condicao: Sem mudanca; */
int existeRec(Lista *rec, int idLivro, int idLeitor);

#endif