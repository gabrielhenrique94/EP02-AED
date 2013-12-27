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
    novo->pai = NULL;
    novo->dir = externo;
    novo->esq = externo;
    novo->cor = rubro;
    
    return novo;
}

/* verifica e acerta o equilibrio de um no apÃ³s uma inserÃ§Ã£o. */
void rotacionar(PNO* raiz, PNO filho, PNO atual, PNO pai, PNO avo, char* controle) {
    if (*controle != 2) {
       //pai é negro
        if ((pai->dir == atual && pai->esq->cor == rubro) || (pai->esq == atual && pai->dir->cor == rubro)) {
            *controle = 0;
            //irmão do atual é rubro
            atual->cor = negro;
            if (pai->dir == atual) {
                pai->esq->cor = negro;
            } else {
                pai->dir->cor = negro;
            }
            pai->cor = rubro;
            if (avo->cor == rubro){
                //desequilibro chamada recursiva
                rotacionar(raiz, pai, avo, avo->pai, avo->pai->pai, controle);
            }
            *controle = 1;
            
        } else {
            //irmão do atual é negro
            if (atual->esq == filho && pai->esq == atual) {
                atual->cor = negro;
                pai->cor = rubro;
                rotacionar_a_direita(&pai, atual);
            } else if(atual->esq == filho && pai->dir == atual) {
                filho->cor = negro;
                pai->cor = rubro;
                rotacionar_a_direita(&atual, filho);
                rotacionar_a_esquerda(&pai, filho);
            } else if (atual->dir == filho && pai->dir == atual) {
                atual->cor = negro;
                pai->cor = rubro;
                rotacionar_a_esquerda(&pai, atual);
            } else {
                filho->cor = negro;
                pai->cor = rubro;
                rotacionar_a_esquerda(&atual, filho);
                rotacionar_a_direita(&pai, filho);
            }
            *controle = 1;
        }
        
        *controle = 2;
    }
}
 
/* insere sem repeticao um novo no com chave = x, atual, pai e avo apontam, respectivamente, para o no corrente da busca, seu pai e seu avo, e controle controla a chamada da funcao rotacionar. Retorna true se inserir com sucesso e false caso contrario (se ja existir um no com a chave x). */
bool inserir_RN(PNO* raiz, TIPOCHAVE x, PNO* atual, PNO pai, PNO avo, char* controle){
    if (arvoreRN_vazia(*raiz)) {
        *raiz = criar_novo_no(x);
        (*raiz)->cor = negro;
        return true;
    }
    
    PNO auxpai, auxavo, auxnovo;
    if ((*atual)->pai != NULL) {
        printf("Tem pai");
        auxpai = (*atual)->pai;
        if (auxpai->pai != NULL)
            auxavo = auxpai->pai;
    } else {
        auxpai = NULL;
        auxavo = NULL;
    }
    
  
    if (x == (*atual)->chave) {
        return false;
    } else if (x > (*atual)->chave) {
        printf("X>ATUAL");
        if ((*atual)->dir != externo) {
            printf("DIR ATUAL");
            inserir_RN(raiz, x, &(*atual)->dir, auxpai, auxavo, controle);
        } else {
            printf("CRIA NOVO");
            auxnovo = criar_novo_no(x);
            auxnovo->pai = *atual;
            (*atual)->dir = auxnovo;
            
        }
    } else {
        printf("X<ATUAL");
        if ((*atual)->esq != externo) {
             printf("ESQ ATUAL");
            inserir_RN(raiz, x, &(*atual)->esq, auxpai, auxavo, controle);
        } else {
            printf("CRIA NOVO");
            auxnovo = criar_novo_no(x);
            auxnovo->pai = *atual;
            (*atual)->esq = auxnovo;
        }
    }
     printf("ANTES ATUAL COR");
    if ((*atual)->cor == rubro) { //Caso 2
        printf("ATUAL RUBRO :O");
       rotacionar(raiz, auxnovo, *atual, pai, avo, controle);
    }
    printf("ANTES TRUE");
    return true;
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
        PNO aux_dir = no->dir;
        if (aux_dir != externo) {
            while (aux_dir->esq != externo) {
                aux_dir = aux_dir->esq;
            }
            return aux_dir;
       }
    }
    return NULL;
}

/* remove a chave x da arvore com raiz apontada por raiz. 
   Retorna true se removeu com sucesso e false caso contrario (se nao havia um no com a chave x). */
bool remover_RN(PNO* raiz, TIPOCHAVE x){
    if (arvoreRN_vazia(*raiz)) {
        return false;
    }
    
    PNO no, auxpai, auxmenor;
    no = buscar_no(*raiz, x);
    if (no != NULL) {
        if(no->esq != externo && no->dir != externo) {
            auxmenor = menor_descendente_direito(no);
            no->chave = auxmenor->chave;
            if (auxmenor->dir != externo) {
                auxpai = auxmenor->pai;
                if (auxpai->chave != x) { // É o proprio nó com o valor a ser removido
                    auxpai->esq = auxmenor->dir;
                    auxmenor->dir->pai = auxpai;
                } else {
                    no->dir = auxmenor->dir;
                    auxmenor->dir->pai = no;
                }
            }
            
            free(auxmenor);
             
        } else if (no->esq != externo) {
            auxpai = no->pai;
            if (auxpai != NULL) {
                if (auxpai->dir == no) {
                    auxpai->dir = no->esq;
                } else {
                    auxpai->esq = no->esq;
                }
                free(no);
            }
        } else if (no->dir != externo) {
            auxpai = no->pai;
            if (auxpai != NULL) {
                if (auxpai->dir == no) {
                    auxpai->dir = no->dir;
                } else {
                    auxpai->esq = no->dir;
                }
                free(no);
            }
        } else {
            auxpai = no->pai;
            if (auxpai != NULL) {
                if (auxpai->dir == no) {
                    auxpai->dir = externo;
                } else {
                    auxpai->esq = externo;
                }
            }
            free(no);
        }
    } else {
        return false;
    }
    
    return true;
}  

/* faz uma rotaÃ§Ã£o a esquerda no nÃ³ no, na Ã¡rvore apontada por raiz */
void rotacionar_a_esquerda(PNO* raiz, PNO no){
    PNO pai = *raiz;
    no->pai = pai->pai;
    pai->dir = no->esq;
    pai->pai = no;
    no->esq = pai;
    *raiz = no;
}

/* faz uma rotaÃ§Ã£o a direita no nÃ³ no, na Ã¡rvore apontada por raiz */
void rotacionar_a_direita(PNO* raiz, PNO no){
    PNO pai = *raiz;
    no->pai = pai->pai;
    pai->esq = no->dir;
    pai->pai = no;
    no->dir = pai;
    *raiz = no;
}

/* equilibra a Ã©rvore apontada por raiz, assumindo que o nÃ³ problemÃ¡tico Ã© q. */
void equilibrar_RN_apos_remocao(PNO* raiz, PNO q){
  /* completar */
}
