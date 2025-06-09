#ifndef LIVRO_H
#define LIVRO_H

typedef struct Livro Livro;

Livro *criaLivro();

void liberaLivro(Livro *livro);

void imprimeLivro(Livro *livro);

#endif