#include "libhead.h"

int main(int argc, char *argv[]){
  char board[15][15],c2,letra;
  files ficheiros = {"/usr/share/dict/words", NULL, NULL, NULL};
  int opt = 0, n = 9, f = 0,j = 0, pontos = 0, flag = 0, trash = 0,l=0,c=0, numeroJogadas = -1;
  FILE *board_out=NULL;

while((opt = getopt(argc, argv, ARG_LIST)) != -1){
  switch(opt){

  case ':':
    printf("Argumento em falta.\nUse -h para ajuda com a linha de comandos\n");
    return -1;
    break;
  case 'h':
    help();
    return 0;
    break;
  case 't':
    if (optarg == NULL){
      printf("Argumento em falta.\nUse -h para ajuda com a linha de comandos\n");
      return -1;
    }
    sscanf(optarg,"%dx%d", &n,&trash);
    if(n%2 == 0){
      printf("o tabuleiro tem de ter tamanho impar\n");
      return -1;
    }
    if (n < 6 || n > 15){
      printf("Tamanho de tabuleiro inválido.\n");
      return -1;
    }
    break;
  case'i':
    ficheiros.imp = optarg;
    n = imp_board(board, n, ficheiros.imp);
    printf("%d\n",n);
    print_board(board,n);
    flag = 1;
    break;
  case 'j':
    j = atoi(optarg);
    if (j > 4 || j < 1){
      printf("Modo de jogo inisistente\n");
      return -1;
    }
    break;
  case 'd':
    ficheiros.dicname = optarg;
    break;
  case 'r':
    ficheiros.playbook_archive = optarg;
    break;
  case 'o':
    ficheiros.final_putin=optarg;
    break;
  case 'n':
    numeroJogadas = atoi(optarg);
    break;

  case('?'):
    printf("Argumento não reconhecido");
    break;
  }
}
  if (flag == 0){
    ini_board(board, n);
  }
  switch(j){
    case 1:
      do{
        f = modo_1(board,n, &pontos);
      }while(f == 0);
      break;

    case 2:
      modo_2(board ,n, ficheiros, numeroJogadas);
      break;
    case 5:
      //bbc(board,n);
      break;
    }
   if(ficheiros.final_putin!=NULL){
      board_out=fopen(ficheiros.final_putin,"w");
      for(l=0;l<n;l++){
        fprintf(board_out,"%d\t",l+1);
        for(c=0;c<n;c++){
            fprintf(board_out,"%c ",board[l][c]);
        }
        fprintf(board_out,"\n");
        }
      fprintf(board_out,"\t");
      c2=n-1+'A';
      for(letra='A';letra<=c2;++letra){
        fprintf(board_out,"%c ",letra);
        }
      printf("\n");
      fclose(board_out);
      }
 return 0;
}


void help(){
  printf( "-h\t ajuda para o utilizador\n\
-t lxc\t dimensões do tabuleiro (linha x coluna).\n\
-d filename1\t nome do ficheiro de dicionário a utilizar\n\
-l filename\t nome do ficheiro com letras a usar nas jogadas\n\
-m 5-20\t número de letras que um jogador pode ter na sua mão para jogar\n\
-n nn\t número de jogadas máximo a realizar\n\
-i filename\t define ficheiro com o tabuleiro a usar em alternativa a jogar num tabuleiro vazio\n\
-j 1-4\tmodo de jogo 1 a 4\n\
-o filename\tdefine ficheiro onde escrever o tabuleiro final.\n\
-r filename\tdefine ficheiro para registo de todas as jogadas possíveis\n");
return;
}
