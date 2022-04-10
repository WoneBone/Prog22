#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

void ini_board (char board[15][15],int n);//função que define e imprime o tabuleiro inicial
void print_board (char board[15][15],int n);//funçao para ser utilizada durante o programa para ver como está o tabuleiro
int modo_1 (char board[15][15],int n, int*);
void modo_2(char board[15][15], int n);
char **abrir(FILE* ,int);

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

int modo_1(char board[15][15],int n, int * pontos){

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
  int i,j,n2,linha,coluna,centro,r=0;
  char **word,palavra[50];
  srand(time(0));
  FILE *Eng;
  FILE *Pt;
  Eng = fopen("american-menos-mais","r");
  Pt=fopen("pt_PT.dic","r");

  word = abrir(Eng, n);
 
  if (word == NULL){
    printf("Não foi possível abrir o dicionário");
    return;
  }

  do{
    j=rand()%102401;
    strcpy(palavra,word[j]);
    printf("%s",palavra);
    palavra[0]=tolower(palavra[0]);
  }while(strlen(palavra)>n);

  i=0;
  centro=n-(strlen(palavra));
  while(palavra[i]!='\n'){
    if(palavra[i]!='\n'){
    board[n/2][centro]=palavra[i];
    i++;
    centro++;
    }
  }
  print_board(board,n);
  for(linha=0;linha<n;linha++){
      for(coluna=0;coluna<n;coluna++){
        if((board[linha][coluna]<='z')&&(board[linha][coluna]>='a')){
          i=0;
          do{
             j=rand()%102401;
             strcpy(palavra,word[j]);
             palavra[0]=tolower(palavra[0]);
             printf("%s",palavra);
             if( (palavra[0]==board[linha][coluna]) && (strlen(palavra)<=(n-linha))){
                r++;
             }
             }while(r==0);
          while(palavra[i]!='\n'){

                board[linha][coluna]=palavra[i];
                i++;
                linha++;

            }
        }
      }
  }
  print_board(board,n);
  for(i=0;i<=102401;i++){
    free(word[i]);

  }
  fclose(Eng);
  fclose(Pt);
  return;
}
/*Função de abertura de dicionáro modificado do lab 5
  Toma como parâmetro o apontador para o ficheiro a abrir e o tamanho do tabuleiro*/
char** abrir(FILE *run, int n){
  char buffer[100], **linhas;
  int size = 0, i = 0;

  //alocação dinâmica do número de palavras (só pomos em memória as palavras com o tamanho do tauleiro)
  while(!(feof(run) || size > n)){
    size = 0;
    fgets(buffer, 100, run);
    size = strlen(buffer);
    i++;
  }

  linhas = (char**) calloc(i, sizeof(char*));
  i = 0;
  if ( linhas[i] == NULL){
    printf("Erro de memória");
    free(linhas[i]);
    return NULL;
  }

  //alocação dinâmica do tamanho das palavras e armazenamento das mesmas em memória
  while( !(feof(run) || size > n +1)){
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
  }
  return linhas;
}
