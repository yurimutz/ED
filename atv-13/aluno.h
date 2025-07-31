#if !defined(_ALUNO_H_)
#define _ALUNO_H_

typedef struct Aluno Aluno;

/**
 * @brief Aloca memoria para um aluno
 * 
 * @return A estrutura Aluno inicializada. Caso não seja possível alocar memória, o programa é encerrado.
*/
Aluno *CriaAluno(int mat, char *nome, int cr);

/**
 * @brief Libera a memoria alocada para um aluno
 * 
 * @param aluno Ponteiro para o aluno
 * Dica: Foi usado data_type para generalizar a funcao e usar na estrutura Vector. Por isso, é necessário fazer um cast para Aluno* dentro da função.
*/
void DestroiAluno(void *aluno);

/**
 * @brief Le os dados de um aluno
 * 
 * @param aluno Ponteiro para o aluno
*/
Aluno *LeAluno(FILE *fp);

int retMat(Aluno *aluno);

int imprimeAluno(void *aluno, void *fp);

char *retNome(Aluno *aluno);

Aluno* mudaMat(Aluno *aluno, int matNovo);

int comparaNome(void *a, void *nome);

int comparaMat(void *a, void *mat);

#endif // _ALUNO_H_