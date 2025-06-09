#ifndef PRODUTO
#define PRODUTO

typedef struct Produto Produto;

Produto *criaProduto(int codigo, char *nome, float preco);

Produto *leProduto();

char *leLinha();

void *liberaProduto(Produto *p);

void printaProduto(Produto *p);

int retornaCodigo(Produto *p);

#endif