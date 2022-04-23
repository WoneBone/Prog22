#include "libhead.h"

void modo_2(char board[15][15], int n, files ficheiro, int j ){
  int points = 0, linha, coluna, dir = 1, num = 1, playbook_flg = 0;
  jogada *plays;
  plays = look_word(board, n, n/2, n/2, 0, NULL, ficheiro.dicname);
  FILE *fp;
  if(ficheiro.playbook_archive != NULL){
    fp = fopen(ficheiro.playbook_archive, "a");
    if (fp == NULL){
      printf("cry");
      fflush(stdout);
    }
    else
      playbook_flg = 1;
  }

  //Primeira jogada na casa central
  putin_board(board, n, *plays);
  print_board(board, n);
  printf("%s, %d\n", plays-> palavra, plays-> pontos);
  points = points + plays->pontos;
  plays = snip_playbook(plays);
  if(playbook_flg == 1){
    fprintf(fp,"Jogada 1\n");
    print_playbook(plays, fp);
  }
  plays = burn_playbook(plays);
  //Loop. Efetua jogadas até look_word não encontrar uma jogada válida
  while (num<j || j == -1){
    for(linha = 0; linha < n; linha++){
      for(coluna = 0; coluna< n; coluna ++){
        if ( board[linha][coluna] >=  'a' &&  board[linha][coluna] <=  'z'){
          plays = look_word(board, n, linha, coluna, dir, plays, ficheiro.dicname);
          dir++;
          plays = look_word(board, n, linha, coluna, dir, plays, ficheiro.dicname);
          }
        }
      }

    if (plays == NULL){
      printf("Jogo acabado com %d pontos\n", points);
       if(playbook_flg == 1)
        fclose(fp);
      return;
    }
    else{
      putin_board(board, n, *plays);
      print_board(board, n);
      printf("%s com %d pontos\n", plays->palavra, plays->pontos);
      points = points + plays->pontos;
      num ++;
      if (num != 4)
        plays = snip_playbook(plays);
      if(playbook_flg == 1){
        fprintf(fp,"Jogada %d\n", num);
        print_playbook(plays, fp);
      }
      plays = burn_playbook(plays);
    }
  }
    printf("Jogo acabado com %d pontos\n", points);
    if(playbook_flg == 1)
        fclose(fp);
    return;
}
