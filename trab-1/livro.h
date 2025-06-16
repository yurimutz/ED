// Feito dia 09/06/2025
// Yuri Tressmann Mutz
// Todos os direitos reservados

#ifndef LIVRO_H
#define LIVRO_H

#include <stdio.h>

typedef struct Livro Livro;

Livro *criaLivro(int id, char *titulo, char *autor, char *genero, int ano);

Livro *leLivro(FILE *fp);

char *leLinha2(FILE *fp);

void liberaLivro(Livro *l);

void imprimeLivro(Livro *l);

int retIdLivro(Livro *l);

char *retLivroTitulo(Livro *l);

#endif