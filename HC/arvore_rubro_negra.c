#include <stdlib.h>
#include <stdio.h>
#include "arvore_rubro_negra.h"

/* no especial que ira representar todos os nos externos (folhas) */
PNO externo = NULL;
PNO suporte_raiz = NULL;

/* inicializa uma arvore vazia */
void inicializar_arvoreRB(PNO* raiz){
  externo = (PNO) malloc(sizeof(NO));
  externo->cor = negro;
  *raiz = externo;
  suporte_raiz = *raiz;
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
     PNO auxraiz;
    if (*controle != 2 && atual != NULL && pai != NULL) {
       //pai é negro
        if ((pai->dir == atual && pai->esq->cor == rubro) || (pai->esq == atual && pai->dir->cor == rubro)) {
            *controle = 0;
            //irmão do atual é rubro
            
            if (pai->dir == atual) {
                pai->esq->cor = negro;
            } else {
                pai->dir->cor = negro;
            }
            
            atual->cor = negro;
            
            if (*raiz != pai) {
                pai->cor = rubro;
            }
            
            if (avo != NULL && avo->cor == rubro){ // Controle acho que era para o avo
                //desequilibro chamada recursiva
                rotacionar(raiz, pai, avo, avo->pai, avo->pai->pai, controle);
            }

            *controle = 1;
        } else {
        
            //irmão do atual é negro
            if (atual->esq == filho && pai->esq == atual) {
                
                auxraiz = pai;
                atual->cor = negro;
                pai->cor = rubro;
                
                rotacionar_a_direita(&pai, atual);
       
                if (auxraiz == *raiz) {
                    *raiz = pai; 
                    suporte_raiz = *raiz;
                }
            } else if(atual->esq == filho && pai->dir == atual) {
               
                auxraiz = pai;
                filho->cor = negro;
                pai->cor = rubro;
                rotacionar_a_direita(&atual, filho);
                rotacionar_a_esquerda(&pai, atual); //Aqui talvez seja atual ou filho
                if (auxraiz == *raiz) {
                    *raiz = pai; 
                    suporte_raiz = *raiz;
                }
            } else if (atual->dir == filho && pai->dir == atual) {
            
                auxraiz = pai;
                atual->cor = negro;
                pai->cor = rubro;
                rotacionar_a_esquerda(&pai, atual);
                if (auxraiz == *raiz) {
                    *raiz = pai; 
                    suporte_raiz = *raiz;
                }
            } else {
            
                auxraiz = pai;
                filho->cor = negro;
                pai->cor = rubro;
                rotacionar_a_esquerda(&atual, filho);
                rotacionar_a_direita(&pai, atual);
                if (auxraiz == *raiz) {
                    *raiz = pai; 
                    suporte_raiz = *raiz;
                }
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
        suporte_raiz = *raiz;
        return true;
    }
    
    PNO auxnovo;    
  
    if (x == (*atual)->chave) {
        return false;
    } else if (x > (*atual)->chave) {
        if ((*atual)->dir != externo) {
            inserir_RN(raiz, x, &(*atual)->dir, *atual, (*atual)->pai, controle);
        } else {
            auxnovo = criar_novo_no(x);
            auxnovo->pai = *atual;
            (*atual)->dir = auxnovo;
            
        }
    } else {
        if ((*atual)->esq != externo) {
            inserir_RN(raiz, x, &(*atual)->esq, *atual, (*atual)->pai, controle);
        } else {
            auxnovo = criar_novo_no(x);
            auxnovo->pai = *atual;
            (*atual)->esq = auxnovo;
        }
    }

    if (*controle != 2 && (*atual)->cor == rubro) { //Caso 2
       rotacionar(raiz, auxnovo, *atual, (*atual)->pai, (*atual)->pai->pai, controle);
    }
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
    if (no != externo){
        return no;
    
    } else {
        return NULL;
    }
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
    PNO auxno, auxpai, auxmenor, auxraiz, duplamente_negro; //duplamente_negro e o filho do no a ser removido
    
    auxno = buscar_no(*raiz, x);
   
    if (auxno != NULL) {
        COR cor_no = auxno->cor;
        if(auxno->esq != externo && auxno->dir != externo) {
            auxmenor = menor_descendente_direito(auxno);
            cor_no = auxmenor->cor;
            auxno->chave = auxmenor->chave;
            auxpai = auxmenor->pai;
            auxraiz = auxpai;
            if (auxmenor->dir != externo) {
                if (auxpai->chave != x) { // É o proprio nó com o valor a ser removido
                    auxpai->esq = auxmenor->dir;
                    auxmenor->dir->pai = auxpai;
                } else {
                    auxno->dir = auxmenor->dir;
                    auxmenor->dir->pai = auxno;
                }
                duplamente_negro = auxmenor->dir;
            } else {
                if (auxpai->esq == auxmenor) {
                    auxpai->esq = externo;
                } else {
                    auxpai->dir = externo;
                }
                duplamente_negro = externo;
            }            
            
            free(auxmenor);
             
        } else if (auxno->esq != externo) {
            auxpai = auxno->pai;
            auxraiz = auxpai;
            if (auxpai != NULL) {
                if (auxpai->dir == auxno) {
                    auxpai->dir = auxno->esq;
                    auxpai->esq->pai = auxpai;
                } else {
                    auxpai->esq = auxno->esq;
                    auxpai->esq->pai = auxpai;
                }
                duplamente_negro = auxpai->esq;
            } else {
                *raiz = auxno->esq;
                (*raiz)->pai = NULL;
                suporte_raiz = *raiz;
                duplamente_negro = *raiz;
            }
            
            free(auxno);
            
        } else if (auxno->dir != externo) {
            auxpai = auxno->pai;
            auxraiz = auxpai;
            if (auxpai != NULL) {
                if (auxpai->dir == auxno) {
                    auxpai->dir = auxno->dir;
                    auxpai->dir->pai = auxpai;
                } else {
                    auxpai->esq = auxno->dir;
                    auxpai->dir->pai = auxpai;
                }
                duplamente_negro = auxpai->dir;
            } else {
                *raiz = auxno->dir;
                (*raiz)->pai = NULL;
                suporte_raiz = *raiz;
                duplamente_negro = *raiz;
            }
            free(auxno);
        } else {
            duplamente_negro = externo;
            auxpai = auxno->pai;
            auxraiz = auxpai;
            if (auxpai != NULL) {
                if (auxpai->dir == auxno) {
                    auxpai->dir = externo;
                } else {
                    auxpai->esq = externo;
                }
            } else {
                //Arvore totalmente vazia apos a delecao
                *raiz = externo;
                suporte_raiz = *raiz;
            }
            
            free(auxno);
        }
        
        if (cor_no != rubro) { // o duplamente_negro é usado aqui
            //Balancear
            equilibrar_RN_apos_remocao(&auxpai, duplamente_negro);
            if (suporte_raiz != *raiz) {
                (*raiz) = suporte_raiz;
                
            }
           
        }
    } else {
        return false;
    }
    
    
    return true;
}  

/* faz uma rotaÃ§Ã£o a esquerda no nÃ³ no, na Ã¡rvore apontada por raiz */
void rotacionar_a_esquerda(PNO* raiz, PNO no){
    PNO pai, avo, filho_no_esq;
    bool filho_avo_dir;
    pai = *raiz;
    avo = pai->pai;
   
    if (avo != NULL) {
        if (avo->dir == pai) {
            filho_avo_dir = true;
        } else {
            filho_avo_dir = false; //é filho dir em rot duplas
        }
    }
   
    filho_no_esq = no->esq;    
    no->pai = avo;
    pai->dir = filho_no_esq;
    pai->pai = no;
    no->esq = pai;
   
    if (filho_no_esq != externo) {
        filho_no_esq->pai = pai;
    }
    
    if (avo != NULL) {
        if (filho_avo_dir) {
            avo->dir = no;
        } else {
            avo->esq = no;
        }
    }
    *raiz = no;
}

/* faz uma rotaÃ§Ã£o a direita no nÃ³ no, na Ã¡rvore apontada por raiz */
void rotacionar_a_direita(PNO* raiz, PNO no){
    PNO pai, avo, filho_no_dir;
    bool filho_avo_esq;
    pai = *raiz;
    avo = pai->pai;
    
    if (avo != NULL) {
        if (avo->esq == pai) {
            filho_avo_esq = true;
        } else {
            filho_avo_esq = false; //é filho dir em rot duplas
        }
    }
    
    filho_no_dir = no->dir;    
    no->pai = avo;
    pai->esq = filho_no_dir;
    pai->pai = no;
    no->dir = pai;
    
    if (filho_no_dir != externo) {
        filho_no_dir->pai = pai;
    }
    
    if (avo != NULL) {
        if (filho_avo_esq) {
            avo->esq = no;
        } else {
            avo->dir = no;
        }
    }
    *raiz = no;
}

/* equilibra a Ã©rvore apontada por raiz, assumindo que o nÃ³ problemÃ¡tico Ã© q. */
void equilibrar_RN_apos_remocao(PNO* raiz, PNO q){    
    PNO pai, irmao;
    pai = *raiz;
 
    if (pai != q && pai != NULL && q != NULL && q->cor == negro) { 
        if (pai->esq == q) {
            irmao = pai->dir;
            //Caso de 1-4 duplamente negro como filho ESQUERDO
            if (irmao->cor == rubro) {
             
                //Caso 1 - irmao é rubro, logo pai é negro.
                pai->cor = rubro;
                irmao->cor = negro;               
                rotacionar_a_esquerda(&pai, irmao);
                if (pai->pai == NULL) {
                    *raiz = pai;
                    suporte_raiz = *raiz;
              
                }
                equilibrar_RN_apos_remocao(&pai->esq, q); // o filho do pai virou raiz, entao temos que continuar na mesma raiz

            } else if (irmao->cor == negro && irmao->esq->cor == negro && irmao->dir->cor == negro) {
                //Caso 2 - irmao é negro e seus filhos tbm
               
                irmao->cor = rubro;
                if (pai->cor == negro) { // pai vira duplamente negro, logo tenho que equilibrar ele
                    equilibrar_RN_apos_remocao(&pai->pai, pai);
                } else {
                    pai->cor = negro; // arvore balanceada
                }
              
            } else if (irmao->cor == negro && irmao->esq->cor == rubro && irmao->dir->cor == negro) {
                // Caso 3 - irmao é negro, o filho direito tbm e o esquerdo é rubro.
          
                irmao->cor = rubro;
                irmao->esq->cor = negro;
                rotacionar_a_direita(&irmao, irmao->esq); //transformado em Caso 4
                equilibrar_RN_apos_remocao(&pai, q);
            } else {
      
                // Caso 4 - irmao é negro e filho direito é rubro, nao se sabe a cor do outro filho
                irmao->cor = pai->cor; //nao sabemos a cor do pai
                pai->cor = negro;
                irmao->dir->cor = negro;
                rotacionar_a_esquerda(&pai, irmao);
                if (pai->pai == NULL) {
                    *raiz = pai;
                    suporte_raiz = *raiz;
                }
            }
        } else { // q e filho dir de pai
            irmao = pai->esq;
            //Caso de 1-4 duplamente negro como filho DIREITO
            if (irmao->cor == rubro) {
             
                //Caso 1 - irmao é rubro, logo pai é negro.
                pai->cor = rubro;
                irmao->cor = negro;               
                rotacionar_a_direita(&pai, irmao);
                if (pai->pai == NULL) {
                    *raiz = pai;
                    suporte_raiz = *raiz;
                    
                }
                equilibrar_RN_apos_remocao(&pai->dir, q);

            } else if (irmao->cor == negro && irmao->dir->cor == negro && irmao->esq->cor == negro) {
                //Caso 2 - irmao é negro e seus filhos tbm
     
                irmao->cor = rubro;
                if (pai->cor == negro) { // pai vira duplamente negro, logo tenho que equilibrar ele
                    equilibrar_RN_apos_remocao(&pai->pai, pai);
                } else {
                    pai->cor = negro; // arvore balanceada
                }
                
            } else if (irmao->cor == negro && irmao->dir->cor == rubro && irmao->esq->cor == negro) {
                // Caso 3 - irmao é negro, o filho esquerdo tbm e o direito é rubro.
 
                irmao->cor = rubro;
                irmao->dir->cor = negro;
                rotacionar_a_esquerda(&irmao, irmao->dir); //transformado em Caso 4
                equilibrar_RN_apos_remocao(&pai, q);
            } else {
                // Caso 4 - irmao é negro e filho esquerdo é rubro, nao se sabe a cor do outro filho
       
                irmao->cor = pai->cor; //nao sabemos a cor do pai
                pai->cor = negro;
                irmao->esq->cor = negro;
                rotacionar_a_direita(&pai, irmao);
                if (pai->pai == NULL) {
                    *raiz = pai;
                    suporte_raiz = *raiz;
                }         
            }
        }
    } else {
        if (q != NULL && q->cor == rubro) {
            q->cor = negro;
        }
    }
    
    return;
}
