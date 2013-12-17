#include <stdlib.h>
#include <stdio.h>
#include "arvore_rubro_negra.h"

/* no especial que ira representar todos os nos externos (folhas) */
PNO externo = NULL;

/* inicializa uma arvore vazia */
void inicializar_arvoreRB(PNO* raiz){
  /* completar. Aqui eh um bom lugar para criar o no externo */
  externo = (PNO) malloc(sizeof(NO));
  externo->cor = negro;
  *raiz = externo;
}

/* imprime em pre-ordem*/
void imprime_arvoreRB(PNO raiz){
  if (raiz == externo){
    printf("(N)");
    return;
  }
  printf("(");
  //imprime a cor
  if (raiz->cor == rubro) printf("R ");
  else printf("N ");

  printf("%d",raiz->chave);
  imprime_arvoreRB(raiz->esq);
  imprime_arvoreRB(raiz->dir);
  printf(")");
}

/* cria um novo (aloca memoria) com chave=ch, inicializa propriamente os filhos esquerdo e direito e retorna 
   seu endereco */
PNO criar_novo_no(TIPOCHAVE ch){
    PNO novo = (PNO) malloc(sizeof(NO));
    novo->chave = ch;
    novo->dir = externo;
    novo->esq = externo;
    novo->cor = rubro;
    
    return novo;
}

/* verifica e acerta o equilibrio de um no apÃ³s uma inserÃ§Ã£o. */
void rotacionar(PNO* raiz, PNO filho, PNO atual, PNO pai, PNO avo, char* controle){
  /* completar */
}
 
/* insere sem repeticao um novo no com chave = x, atual, pai e avo apontam, respectivamente, para o no corrente da busca, seu pai e seu avo, e controle controla a chamada da funcao rotacionar. Retorna true se inserir com sucesso e false caso contrario (se ja existir um no com a chave x). */
bool inserir_RN(PNO* raiz, TIPOCHAVE x, PNO* atual, PNO pai, PNO avo, char* controle){
    if (*atual == NULL || *raiz == NULL) return false;
    if (*atual == externo) {
        *atual = criar_novo_no(x);
        if (arvoreRN_vazia(raiz)){ 
            *raiz = *atual;
            
        } else {
            if (pai->chave > atual->chave) {
                *pai->esq = *atual;
            } else {
                *pai->dir = *atual;
            }
            
        }
        
        if (*raiz == *atual) {
            *raiz->cor = negro;
        } else {
            //ajusta pai do atual, ajusta filho do atual
        }
    } else {
        //Fazer
    }
}  


/* retorna true se a arvore rubro negra estiver vazia e false caso contrario */
bool arvoreRN_vazia(PNO raiz){
    if (raiz == externo) return true;
    return false;
}

/* Busca o nÃ³ com  chave = x. 
   Retorna o ponteiro para o nÃ³.
   VocÃª pode utilizar o no "externo" como sentinela. */
PNO buscar_no(PNO raiz, TIPOCHAVE x){
    if (arvoreRN_vazia(raiz))   return NULL;
    PNO no = raiz;
    while (no != externo && no->chave != x) {
        if (x > no->chave) {    // vai para a direita 
            no = no->dir;
        } else {                //vai para a esquerda 
            no = no->esq;
        }
    }
    if (no != externo) return no;
    return NULL;
}

/* retorna um ponteiro para o nÃ³ que Ã© o menor descendente direito de "no" (que nÃ£o seja o externo). */
PNO menor_descendente_direito(PNO no){
    if (no != NULL) {
        aux_dir = no;
        while (aux_dir->dir != externo) {
            aux_dir = aux_dir->dir;
        }
        if (aux_dir != no) return aux_dir;
    }
    return NULL;
}

/* remove a chave x da arvore com raiz apontada por raiz. 
   Retorna true se removeu com sucesso e false caso contrario (se nao havia um no com a chave x). */
bool remover_RN(PNO* raiz, TIPOCHAVE x){
  /* completar */
}  

/* faz uma rotaÃ§Ã£o a esquerda no nÃ³ no, na Ã¡rvore apontada por raiz */
void rotacionar_a_esquerda(PNO* raiz, PNO no){
  /* completar */
}

/* faz uma rotaÃ§Ã£o a direita no nÃ³ no, na Ã¡rvore apontada por raiz */
void rotacionar_a_direita(PNO* raiz, PNO no){
  /* completar */
}

/* equilibra a Ã©rvore apontada por raiz, assumindo que o nÃ³ problemÃ¡tico Ã© q. */
void equilibrar_RN_apos_remocao(PNO* raiz, PNO q){
  /* completar */
}
