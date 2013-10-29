# include <stdio.h>
# include <malloc.h>
# define false 0
# define true 1

typedef int bool;
typedef struct NoAux {
  bool fimDoNumero;
  struct NoAux* filhos[10];
} No, * PontNo;

typedef struct {
  PontNo raiz;
} Arvore;

void inicializarArvore(Arvore* a);
bool inserirNumeroAux1(PontNo raizSubArvore, int subNumero);
bool inserirNumero(Arvore a, int numero);
int numeroDeNosDaArvoreAux(PontNo no);
int numeroDeNosDaArvore(Arvore a);
int quantidadeDeNumerosDaArvoreAux(PontNo no);
int quantidadeDeNumerosDaArvore(Arvore a);
int alturaArvoreAux(PontNo no);
int alturaArvore(Arvore a);
void imprimirNumerosAux(PontNo subArvore, int subNumero, int profundidadeAtual);
void imprimirNumeros(Arvore a);
bool buscaNumeroAux(PontNo subArvore, int subNumero);
bool buscaNumero(Arvore a, int numero);
