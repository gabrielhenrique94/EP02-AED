/* Arquivo arvoreDecaria.c */
#include "arvoreDecaria.h"

/* ACH2023 - 2o Semestre de 2013
   Turma 
   Prof. Luciano Antonio Digiampietri
   Aluno:                 - No USP:
*/

/* Funcao que retorna 10 elevado a x para x >= 0 ,
   util para ser usada com a funcao imprimir.    */
int potenciaDeDez(int x){
  if (x<=0) return 1;
  int i;
  int res = 1;
  for (i=0;i<x;i++) res*=10;
  return res;
}

/* Cria um novo No e inicializa suas variaveis, util para a insercao */
PontNo criarNo(){
  int i;
  PontNo novo = (PontNo) malloc(sizeof(No));
  for (i=0;i<10;i++) novo->filhos[i] = NULL;
  novo->fimDoNumero = false;
  return novo;
}
       
/* Inicializa a arvore apontada por a, criando o noh raiz */
void inicializarArvore(Arvore* a){
  a->raiz = criarNo();
}


/* Funcao auxiliar da funcao inserir (pode ser recursiva).
   Recebe o endereco do no atual e o subNumero, isto eh, a parte do numero
   que falta ser inserida */
bool inserirNumeroAux1(PontNo raizSubArvore, int subNumero){

  /* COMPLETAR */

  return false;
}

/* Funcao de insercao que recebe uma arvore e um numero e deve fazer a insercao
   deste numero na arvore caso ele nao esteja lah e retornar true; caso o 
   numero ja exista devera retornar false */
bool inserirNumero(Arvore a, int numero){

  /* COMPLETAR */

  return false;
}

/* Funcao auxiliar para retornar a altura da subarvore iniciada pelo noh 
   apontado pelo parametro no. */
int alturaArvoreAux(PontNo no){

  /* COMPLETAR */

  return 0;
}

/* Funcao que retorna a altura da arvore a. A altura deste tipo de arvore sera
   uma unidade maior do que a quantidade de digitos do maior numero cadastrado.*/
int alturaArvore(Arvore a){

  /* COMPLETAR */

  return 0;
}


/* Funcao auxiliar para retornar a quantidade de nos da subarvore iniciada pelo 
   noh apontado pelo parametro no. */
int numeroDeNosDaArvoreAux(PontNo no){

  /* COMPLETAR */

  return 0;
}

/* Funcao que retorna a quantidade de nos da arvore a, incluindo a raiz.*/
int numeroDeNosDaArvore(Arvore a){

  /* COMPLETAR */

  return 0;
}

/* Funcao auxiliar para retornar a quantidade de numeros da subarvore iniciada 
   pelo noh apontado pelo parametro no. A contagem de numeros corresponde a 
   quantidade de nos com o campo fimDoNumero=true*/
int quantidadeDeNumerosDaArvoreAux(PontNo no){

  /* COMPLETAR */

  return 0;
}

/* Funcao que retorna a quantidade de numeros da arvore a. A contagem de numeros
   corresponde a quantidade de nos com o campo fimDoNumero=true**/
int quantidadeDeNumerosDaArvore(Arvore a){

  /* COMPLETAR */

  return 0;
}

/* Funcao auxiliar para imprimir em pre-ordem todos os numeros da arvore.
   A ideia desta funcao eh receber no parametro subArvore o noh atual; o 
   parametro subNumero conterah o valor do numero ate o momento (isto eh, a 
   concatenacao dos digitos anteriores) e a profundidade atual do noh subArvore:
   esta informacao pode ser util para adicionar ao subNumero o valor correspon-
   dente ao digito atual [utilizando a funcao potenciaDeDez]. */
void imprimirNumerosAux(PontNo subArvore, int subNumero, int profundidadeAtual){

  /* COMPLETAR */

}

/* Funcao principal para se imprimir todos os numeros em pre-ordem registrados
   na arvore a. */
void imprimirNumeros(Arvore a){

  /* COMPLETAR */

}

/* Funcao auxiliar para a busca de um numero numa dada arvore. O parametro 
   subArvore corresponde ao noh atual; o parametro subNumero corresponde a parte
   do numero que ainda falta ser encontrada. */
bool buscaNumeroAux(PontNo subArvore, int subNumero){

  /* COMPLETAR */

  return false;
}

/* Funcao principal para buscar o numero 'numero' na arvore a que deve retornar
   true caso este numero pertenca a arvore e false caso contrario. */
bool buscaNumero(Arvore a, int numero){

  /* COMPLETAR */

  return false;
}


