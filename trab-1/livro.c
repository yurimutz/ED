// Feito dia 09/06/2025
// Yuri Tressmann Mutz
// Todos os direitos reservados

#include "livro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Livro{

    int id;
    char *titulo;
    char *autor;
    char *genero;
    int ano;

};

Livro *criaLivro(int id, char *titulo, char *autor, char *genero, int ano){

    Livro *l = malloc(sizeof(Livro));

    l->id = id; 
    
    l->titulo = titulo;
    l->autor = autor;
    l->genero = genero;

    l->ano = ano;

    return l;

}

Livro *leLivro(FILE *fp){

    int id=0;
    fscanf(fp, "%d;", &id);

    char *titulo = leLinha2(fp);
    char *autor = leLinha2(fp);
    char *genero = leLinha2(fp);

    int ano=0;
    char lixo;

    fscanf(fp,"%d\n", &ano);

    Livro *l = criaLivro(id, titulo, autor, genero, ano);

    return l;

}

char *leLinha2(FILE *fp){

    char temp[50];
    char lixo;

    fscanf(fp, "%[^;\n]", temp);
    fscanf(fp, "%c", &lixo);

    char *str = strdup(temp);

    return str;

}

void liberaLivro(Livro *l){

    free(l->autor);
    free(l->genero);
    free(l->titulo);

    free(l);

}

void imprimeLivro(Livro *l){

    printf("%d\n", l->id);
    printf("%s\n", l->titulo);
    printf("%s\n", l->autor);
    printf("%s\n", l->genero);
    printf("%d\n", l->ano);

}

int retIdLivro(Livro *l){

    return l->id;

}

char *retLivroTitulo(Livro *l){

    return l->titulo;

}