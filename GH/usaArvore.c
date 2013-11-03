/******************************************************************************
         usaArvore.c
  Este programa interage com o usuario para o gerenciamento de uma arvore
  para o armazenamento de numeros.
******************************************************************************/
#include "arvoreDecaria.c"

void inserir(Arvore t){
  int numero;
  scanf("%i",&numero);
  if (inserirNumero(t,numero)){
    printf("Numero inserido com sucesso.\n");
  }else{
    printf("Nao foi possivel inserir o numero: %i\n", numero);
  }
}

void buscar(Arvore t){
  int numero;
  scanf("%i",&numero);
  if (buscaNumero(t,numero)){
     printf("Numero encontrado: %i\n", numero);
  } else {
    printf("Numero nao encontrado: %i\n", numero);
  }
}

void exibir(Arvore t){
  imprimirNumeros(t);
}

void meuLog(Arvore t){
  printf("Quantidade de numeros na arvore: %i, numero de nos: %i, altura: %i\n",quantidadeDeNumerosDaArvore(t), numeroDeNosDaArvore(t), alturaArvore(t));
}

void help(){
  printf("Comandos validos: \n");
  printf("  i <numero> : inserir elemento na arvore\n");
  printf("  b <numero> : buscar um numero definido pelo usuario\n");
  printf("  p : imprimir os numeros validos em pre-ordem\n");
  printf("  l : exibir log de utilizacao da arvore\n");
  printf("  h : exibir esta mensagem de ajuda\n");
  printf("  q : sair do programa\n");
}

int main(){
  Arvore arvore;
  inicializarArvore(&arvore);
  /* help(); */
  char comando = ' ';
  scanf("%c",&comando);
  while (comando != 'q'){
    switch (comando) {
      case 'i' : inserir(arvore); break;
      case 'p' : exibir(arvore); break;
      case 'l' : meuLog(arvore); break;
      case 'b' : buscar(arvore); break;
      case 'h' : help(); break;
      default: {while (comando != '\n') scanf("%c",&comando);};
    }
    scanf("%c",&comando);
  }
  return 0;
}
