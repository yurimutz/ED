#ifndef PRODUTO
#define PRODUTO

typedef struct Produto Produto;

Produto *criaProduto(char *nome, float valor);

void liberaProduto(Produto *i);

Produto *leProduto();

float valorProduto(Produto *p);

void printaProduto(Produto *p);

#endif