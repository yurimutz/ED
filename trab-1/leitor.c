#include "leitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Leitor{

    int id;
    char *nome;
    int nAfinidades;
    char afinidades[10][50];
    Lista *lidos;
    Lista *desejados;
    Lista *recomendacoes;
    
};