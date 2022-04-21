#include "libhead.h"

void modo_2(char board[15][15], int n ){
  int points = 0, linha, coluna, dir = 1;
  jogada *plays;
  plays = look_word(board, n, n/2, n/2, 0, NULL);
  FILE *fp = fopen("merdas.txt", "a");
  if (fp == NULL)
    printf("cry");
  //Primeira jogada na casa central
  putin_board(board, n, *plays);
  print_board(board, n);
  printf("%s, %d\n", plays-> palavra, plays-> pontos);
  points = points + plays->pontos;
  plays = snip_playbook(plays);
  fprintf(fp,"Jogada %d\n", dir);
  print_playbook(plays, fp);
  plays = burn_playbook(plays);
  //Loop. Efetua jogadas até look_word não encontrar uma jogada válida
  while (1){
    for(linha = 0; linha < n; linha++){
      for(coluna = 0; coluna< n; coluna ++){
        if ( board[linha][coluna] >=  'a' &&  board[linha][coluna] <=  'z'){
          plays = look_word(board, n, linha, coluna, dir, plays);
          }
        }
      }

    if (plays == NULL || plays->pontos == 0){
      printf("Jogo acabado com %d pontos\n", points);
      fclose(fp);
      return;
    }
    else{
      putin_board(board, n, *plays);
      print_board(board, n);
      printf("%s com %d pontos\n", plays->palavra, plays->pontos);
      points = points + plays->pontos;
      dir++;
      plays = snip_playbook(plays);
      fprintf(fp,"Jogada %d\n", dir);
      print_playbook(plays, fp);
      plays = burn_playbook(plays);
    }
  }
}
