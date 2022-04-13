#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct Jogadas
{
  char palavra[50];
  int linha;
  int coluna;
  int direcao;
  int pontos;
}jogada;

void ini_board (char board[15][15],int n);
void print_board (char board[15][15],int n);
int modo_1 (char board[15][15],int n, int*);
void modo_2(char board[15][15], int n);
int point_word(char board[15][15], int n, jogada);
void bbc(char board[15][15], int n);
jogada look_word(char board[15][15],int n,int linha,int coluna,int direcao);
void putin_board(char board[15][15], int n, jogada);
char **abrir(FILE* ,int, int*);

int main(){
  char board[15][15]; //endereço do board
  int n, f = 0,j, pontos = 0;
  printf(" indique o tamanho do tabuleiro, deve ser impar:\n");
  do{
    scanf("%d",&n);
    while((getchar())!='\n'); //limpeza do buffer para usar o fgets() ao longo do programa
    
    if(n%2==0){
      printf("o tabuleiro tem de ter tamanho impar tente de novo:\n");
    }
  }while((n%2)==0);

  ini_board(board,n);

  do {
    printf("que modo de jogo quer jogar:\n");
    scanf("%d",&j);
  }while(j>5 && j<0);

  while((getchar())!='\n');//limpar o buffer again

  switch(j){
    case 1:
      do{
        f = modo_1(board,n, &pontos);
      }while(f == 0);
      break;

    case 2:
      modo_2(board ,n);
      break;
    case 5:
      bbc(board,n);
      break;
    }
  return 0;
}
//Inicializar o board aos valores requeridos
void ini_board(char board[15][15],int n){
  int i,j,k;
  k=n-1;//usado para o posicionamento dos 2 na board na diagonal invertida

  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      board[i][j]='.';
      if ((i==(n/2)+1&&(j==1||j==n-2)||(i==(n/2)-1&&(j==1||j==n-2))||(j==(n/2)+1&&(i==1||i==n-2)||(j==(n/2)-1&&(i==1||i==n-2))))){ //parametros para o posicionamento do # na matriz do tabuleiro
        board[i][j]='#';
      }else if(i==j){
        board[i][j]='2';//posicionamento dos 2 ao longo das diagoanis
        board[i][k]='2';
        board[k][i]='2';}
    }
    k--;//k é usado para definir a diagonal inferior esquerda como 2
  }
  board[0][0]='$';
  board[n-1][0]='$';
  board[0][n-1]='$';
  board[n-1][n-1]='$';
  board[n/2][0]='3';
  board[0][n/2]='3';
  board[n/2][n-1]='3';
  board[n-1][n/2]='3';

  print_board(board,n);
}
//Imprime o current state do board
void print_board(char board[15][15], int n){

  int i,j;
  char c,letra;
  for(i=0;i<n;i++){
    printf("%d\t",i+1);
    for(j=0;j<n;j++)
      printf("%c ",board[i][j]);
    printf("\n");
  }
  printf("\t");
  c=n-1+'A';
  for(letra='A';letra<=c;++letra){
    printf("%c ",letra);
    }
  printf("\n");
  return;
 }

int modo_1(char board[15][15],int n, int *pontos){

  int coluna,linha,j = 0,k,l = 0,f = 0;
  char x,i = 'A',palavra[20] = {NULL},direcao, temp = '0';
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

void modo_2(char board[15][15], int n){
  int i,j,k,linha,coluna,centro,r=0,point=0,a=0,linha2=0,coluna2=0, sizeOfDic = 0;
  char **dic;
  jogada play, try;
  play.pontos = 1;
  play.direcao = 0;

  FILE *Eng;
  if((Eng = fopen("american_menos_mais","r"))==NULL){
    printf("fds nao consegui abrir a merda do eng");
  }

  dic = abrir(Eng, n, &sizeOfDic);
  
  for(i=0;i<sizeOfDic;i++){
  try.linha=0;
  try.coluna=0;

  strcpy(try.palavra,dic[i]);
  for ( j=0;j<strlen(try.palavra); ++j) {
    try.palavra[j]=tolower( try.palavra[j]);
  }
  if(strlen(try.palavra)<=n){
    point = point_word(board, n, try);
    if(point> play.pontos){
      play.pontos=point;
      strcpy(play.palavra,try.palavra);
      }
    }
  }
  printf("%s",play.palavra);
  centro=(((n/2)-(strlen(play.palavra)/2))+1);
  i=0;

  while(play.palavra[i]!='\n'){
    if(play.palavra[i]!='\n'){
    board[(n/2)][centro]=play.palavra[i];
    i++;
    centro++;
    }
  }
  print_board(board,n);
  printf("%s fez %d pontos",play.palavra,play.pontos);

  for(i=0;i<sizeOfDic;i++)
    free(dic[i]);
  return;
}

void bbc(char board[15][15], int n){
    int point=0,linha=n/2,coluna=4,direcao=0;
    jogada play;
    printf("diga as coordenadas estrubilho\n");
    scanf("%d",&linha);
    scanf("%d",&coluna);
    scanf("%d",&direcao);

    play = look_word( board, n, linha, coluna, direcao);
    putin_board(board, n, play);
    print_board(board, n);
    return;
}

void putin_board(char board[15][15], int n, jogada play ){
  int linha = play.linha, coluna = play.coluna, i = 0;
  play.pontos = point_word(board, n, play);
  if(play.pontos == 0){
    printf("Jogada inválida");
    return;
  }
  while(!(play.palavra[i] == '\n' ||play.palavra[i] == '\0')){
    board[linha][coluna] = play.palavra[i];
    if ((play.direcao%2) == 0 )
      coluna++;
    else 
      linha ++;
    i++;
  }
  return;
}

int point_word(char board[15][15],int n, jogada play){
  int pontos_letras[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
  int a=0,points=0,k=0,f=0,j=1, linha = play.linha, coluna= play.coluna;
  char i;
  i=play.palavra[a];
  while(i!='\n'&&i!='\0'){
    if(board[linha][coluna]=='#' || ( i >  'z')||( i < 'a')){
      return 0;
    }else if(board[linha][coluna]=='$'){
      f++;
      k = (int) play.palavra[a] - 'a';
      points=points+pontos_letras[k];

    }else if(board[linha][coluna]=='.'){
      k = (int) play.palavra[a] - 'a';
      points=points+pontos_letras[k];
    }else if(board[linha][coluna]=='3'){
      k = (int) play.palavra[a] - 'a';
      points=points+(pontos_letras[k]*3);
    }else if(board[linha][coluna]=='2'){
      k = (int) play.palavra[a] - 'a';
      points=points+(pontos_letras[k]*2);
    }else if(board[linha][coluna]>='a'&&board[linha][coluna]<='z'){
         if(board[linha][coluna]!=play.palavra[a]){
            return 0;
         }
    }
    if((play.direcao%2)==0){
        coluna++;
    }else{
        linha++;
          }
    a++;
    i=play.palavra[a];
    }
    while(f>0){
        points=points*2;
        f--;
    }

    return points;
}

jogada look_word(char board[15][15],int n,int linha,int coluna,int direcao){
  char **word;
  jogada play = {"\0", linha, coluna, direcao, 0}, try1 = {"\0", linha, coluna, direcao, 0}, try2 = {"\0", linha, coluna, direcao, 0};
  int length,i,r, sizeOfDic = 0;
  FILE *Eng;
  if((Eng = fopen("american_menos_mais","r"))==NULL){
    printf("fds nao consegui abrir a merda do eng");
  }

  word = abrir(Eng, n, &sizeOfDic);

  for(i=0;i<sizeOfDic;i++){
    strcpy(try1.palavra,word[i]);
    for ( int j=0;j<strlen(try1.palavra); ++j) {
      try1.palavra[j]=tolower(try1.palavra[j]);
    }
    length = strlen(try1.palavra);
    if(length >= (n/2)){
      r=n-length;
      if((direcao%2)==0)
        try1.coluna=0;
      else 
        try1.linha=0;
      try2 = try1;
      for(r; r >= 0; r--){
        try2.pontos = point_word(board,n,try2);
        if(try1.pontos<try2.pontos)
          try1 = try2;        
        if((direcao%2)==0)
          try2.coluna++;
        else
          try2.linha++;
      }
     if(play.pontos<try1.pontos)
      play = try1; 
    } else{
      for(r; r >= 0; r--){
        try2.pontos = point_word(board,n,try2);
        if(try1.pontos<try2.pontos)
          try1 = try2;        
        if((direcao%2)==0)
          try2.coluna--;
        else
          try2.linha--;
        if(play.pontos<try1.pontos)
          play = try1; 
      }
    }
  }
printf("%s com %d\n",play.palavra,play.pontos);
return play;
}

/*Função de abertura de dicionáro modificada do lab 5
  Toma como parâmetro o apontador para o ficheiro a abrir e o tamanho do tabuleiro*/
char** abrir(FILE *run, int n, int *sizeOfFile){
  char buffer[100], **linhas;
  int size = 0, i = 0;
  *sizeOfFile = 0;

  //alocação dinâmica do número de palavras (só pomos em memória as palavras com o tamanho do tauleiro)
  while(!(feof(run) || size > n + 1)){
    size = 0;
    fgets(buffer, 100, run);
    size = strlen(buffer);
    *sizeOfFile = *sizeOfFile + 1;
  }
  linhas = (char**) calloc(*sizeOfFile, sizeof(char*));
  if ( linhas == NULL){
    printf("Erro de memória");
    free(linhas);
    return NULL;
  }

  //colocar stream no início do ficheiro
  fseek(run, 0, SEEK_SET);

  //alocação dinâmica do tamanho das palavras e armazenamento das mesmas em memória
  do{
    size = 0;
    fgets(buffer, 100, run);
    size = strlen(buffer) + 1;
    linhas[i] = (char*) calloc(size, sizeof(char));
    if ( linhas[i] == NULL){
      printf("Erro de memória");
      free(linhas[i]);
      return NULL;
    }
    else{
      strcpy(linhas[i], buffer);
    }
    i++;
  }while( !(feof(run) || size > n + 2));

  fclose(run);

  return linhas;
}
