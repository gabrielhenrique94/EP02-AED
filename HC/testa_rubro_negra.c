#include <stdio.h>
#include "arvore_rubro_negra.h"


void main(){
  PNO raiz;
  inicializar_arvoreRB(&raiz);
  char controle = 1;

  char operacao;
  TIPOCHAVE x;
  scanf("%c %d", &operacao, &x);
  while (operacao != 'f'){ 
    switch (operacao) {
    case 'i': 
      controle = 1; 
      inserir_RN(&raiz, x, &raiz, NULL, NULL, &controle); 
      break;
    case 'p': imprime_arvoreRB(raiz); printf("\n"); break;
    default: while (operacao != '\n') scanf("%c",&operacao);
    }
    scanf("%c %d", &operacao, &x);
  }
}
