#include <stdbool.h>

typedef int TIPOCHAVE;
typedef enum{rubro, negro} COR;

typedef struct aux{
  TIPOCHAVE chave;
  struct aux *esq;
  struct aux *dir;
  struct aux *pai;
  COR cor;
} NO;

typedef NO* PNO;

/* no especial que ira representar todos os nos externos (folhas). Este no eh criado na funcao inicializar_arvoreRB */
extern PNO externo;

/* inicializa uma arvore vazia */
void inicializar_arvoreRB(PNO* raiz);

/* imprime em pre-ordem*/
void imprime_arvoreRB(PNO raiz);

/* cria um novo (aloca memoria e preenche valores) no com chave=ch e retorna 
   seu endereco */
PNO criar_novo_no(TIPOCHAVE ch);

/* verifica e acerta o equilibrio de um no  apÃ³s uma inserÃ§Ã£o. */
void rotacionar(PNO* raiz, PNO filho, PNO atual, PNO pai, PNO avo, char* controle);

/* insere sem repeticao um novo no com chave = x, atual, pai e avo apontam, respectivamente, para o no corrente da busca, seu pai e seu avo, e controle controla a chamada da funcao rotacionar. Retorna true se inserir com sucesso e false caso contrario (se ja existir um no com a chave x). */
bool inserir_RN(PNO* raiz, TIPOCHAVE x, PNO* atual, PNO pai, PNO avo, char* controle);
 
/* retorna true se a arvore rubro negra estiver vazia e false caso contrario */
bool arvoreRN_vazia(PNO raiz);

/* Busca o nÃ³ com  chave = x. 
   Retorna o ponteiro para o nÃ³.
   VocÃª pode utilizar o no "externo" como sentinela. */
PNO buscar_no(PNO raiz, TIPOCHAVE x);

/* retorna um ponteiro para o nÃ³ que Ã© o menor descendente direito de "no" (que nÃ£o seja o externo). */
PNO menor_descendente_direito(PNO no);

/* remove a chave x da arvore com raiz apontada por raiz. 
   Retorna true se removeu com sucesso e false caso contrario (se nao havia um no com a chave x). */
bool remover_RN(PNO* raiz, TIPOCHAVE x);

/* faz uma rotaÃ§Ã£o a esquerda no nÃ³ no, na Ã¡rvore apontada por raiz */
void rotacionar_a_esquerda(PNO* raiz, PNO no);

/* faz uma rotaÃ§Ã£o a direita no nÃ³ no, na Ã¡rvore apontada por raiz */
void rotacionar_a_direita(PNO* raiz, PNO no);

/* equilibra a Ã©rvore apontada por raiz, assumindo que o nÃ³ problemÃ¡tico Ã© q. */
void equilibrar_RN_apos_remocao(PNO* raiz, PNO q);
