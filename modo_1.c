#include "libhead.h"

int modo_1(char board[15][15],int n, int *pontos){

  int coluna,linha,j = 0,k,l = 0,f = 0;
  char x,i = 'A',palavra[20] = {'\0'},direcao, temp = '0';
  int pontos_letras[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

  printf("Faça uma jogada indicando as coordenadas se é vertical ou horizontal e a palavra que se deseja colocar:\n");

  scanf("%c%c%c",&x,&temp,&direcao);

  x = toupper(x);
  direcao = toupper(direcao);

  //passagem das coordenadas da jogada para ints
  if(x=='F' && direcao == 'M'){
    printf("programa terminado. \nPontos totais %d ", *pontos);
    return 3;
  }

  scanf(" %s", palavra);
  while((getchar())!='\n'); //limpeza do buffer para usar o fgets() ao longo do programa
  linha = temp - '0' - 1;
  coluna= (int) x - 'A';
  i=palavra[j];
  if (*pontos == 0 && (direcao != 'H' || linha != n/2)){
    printf("A primeira jogada deve se feita na horizontal na linha do meio.\n");
    return 0;
  }
  if (direcao == 'H'){
    if ( ( strlen(palavra) + coluna) > n){
      printf("jogada invalida\n");
      return 0;
    }
    else {
      for( int g = coluna; g < strlen(palavra) + coluna; g++ ){
        if(board[linha][g] == '#'){
          printf("jogada invalida\n");
          return 0;
        }
      }
    }
  }else{
    if ( (strlen(palavra) + linha) > n){
      printf("jogada invalida\n");
      return 0;
    }
    else {
      for( int g = linha; g < strlen(palavra) + linha; g++ ){
        if(board[g][coluna] == '#'){
          printf("jogada invalida\n");
          return 0;
        }
      }
    }
  }

  while (i!='\0'&& i!='\n'){
    if(board[linha][coluna]=='$'){
      f++;
      k = (int) i - 'a';
      l=l+pontos_letras[k];
    }else if(board[linha][coluna]=='.'||i==board[linha][coluna]){
      k = (int) i - 'a';
      l=l+pontos_letras[k];
    }else if(board[linha][coluna]=='3'){
      k = (int) i - 'a';
      l=l+(pontos_letras[k]*3);
    }else if(board[linha][coluna]=='2'){
      k = (int) i - 'a';
      l=l+(pontos_letras[k]*2);
    }else{
      printf("jogada invalida\n");
      return 0;
    }
    board[linha][coluna]=i;

    j++;
    i=palavra[j];
    if(direcao=='H'){
      coluna++;
    }else{linha++;}
  }
  if ( f != 0 )
    l = l * 2 * f;

  print_board(board,n);
  *pontos = *pontos + l;
  printf("%s", palavra);
  printf(" %d pontos\n",l);
  return 0;
}
