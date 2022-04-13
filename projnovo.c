#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

void ini_board (char board[15][15],int n);
void print_board (char board[15][15],int n);
int modo_1 (char board[15][15],int n, int*);
void modo_2(char board[15][15], int n);
int point_word(char board[15][15],char palavra[50],int n,int linha,int coluna,int direcao);
void bbc(char board[15][15], int n);
void look_word(char board[15][15],int n,int linha,int coluna,int direcao);
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
  int i,j,k,linha,coluna,centro,r=0,point=0,point2=1,direcao=0,a=0,linha2=0,coluna2=0, sizeOfDic = 0;
  char **word,palavra[50],palavra2[50],l;
  FILE *Eng;
  if((Eng = fopen("american_menos_mais","r"))==NULL){
    printf("fds nao consegui abrir a merda do eng");
  }

  word = abrir(Eng, n, &sizeOfDic);

  for(i=0;i<sizeOfDic;i++){
       linha=0;
       coluna=0;

       strcpy(palavra,word[i]);
       for ( j=0;j<strlen(palavra); ++j) {
        palavra[j]=tolower( palavra[j]);
       }

       if(strlen(palavra)<=n){
         point=point_word(board,palavra,n,linha,coluna,direcao);

         if(point>point2){
            point2=point;
            strcpy(palavra2,palavra);

             }
         }
  }
  printf("%s",palavra2);
  palavra2[0]=tolower(palavra2[0]);
  centro=(((n/2)-(strlen(palavra2)/2))+1);
  i=0;

  while(palavra2[i]!='\n'){
    if(palavra2[i]!='\n'){
    board[(n/2)][centro]=palavra2[i];
    i++;
    centro++;
    }
  }
  print_board(board,n);
  printf("%s fez %d pontos",palavra2,point2);
  direcao++;

  for(i=0;i<sizeOfDic;i++){
    free(word[i]);}

  fclose(Eng);
  return;
}
int point_word(char board[15][15],char palavra[50],int n,int linha,int coluna,int direcao){
  int pontos_letras[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
  int a=0,points=0,k=0,f=0,j=1;
  char i;
  i=palavra[a];
  while(i!='\n'&&i!='\0'){
    if(board[linha][coluna]=='#' || ( i >  'z')||( i < 'a')){
      return 0;
    }else if(board[linha][coluna]=='$'){
      f++;
      k = (int) palavra[a] - 'a';
      points=points+pontos_letras[k];

    }else if(board[linha][coluna]=='.'){
      k = (int) palavra[a] - 'a';
      points=points+pontos_letras[k];
    }else if(board[linha][coluna]=='3'){
      k = (int) palavra[a] - 'a';
      points=points+(pontos_letras[k]*3);
    }else if(board[linha][coluna]=='2'){
      k = (int) palavra[a] - 'a';
      points=points+(pontos_letras[k]*2);
    }else if(board[linha][coluna]>='a'&&board[linha][coluna]<='z'){
         if(board[linha][coluna]!=palavra[a]){
            return 0;
         }
    }
    if((direcao%2)==0){
        coluna++;
    }else{
        linha++;
          }
    a++;
    i=palavra[a];
    }
    while(f>0){
        points=points*2;
        f--;
    }

    return points;
}
void bbc(char board[15][15], int n){
    int point=0,linha=n/2,coluna=4,direcao=0;
    char palavra[50];
    printf("diga as coordenadas estrubilho\n");
    scanf("%d",&linha);
    scanf("%d",&coluna);
    scanf("%d",&direcao);

    look_word( board, n, linha, coluna, direcao);

    return;
}
void look_word(char board[15][15],int n,int linha,int coluna,int direcao){
  char **word,palavra[50],palavra2[50];
  int length,i,r,point=0,point2=1,point3=2, sizeOfDic = 0;
  FILE *Eng;
  if((Eng = fopen("american_menos_mais","r"))==NULL){
    printf("fds nao consegui abrir a merda do eng");
  }

  word = abrir(Eng, n, &sizeOfDic);
  for(i=0;i<sizeOfDic;i++){
    strcpy(palavra,word[i]);
    for ( int j=0;j<strlen(palavra); ++j) {
        palavra[j]=tolower( palavra[j]);
       }
    length=strlen(palavra);
    if(length>=(n/2)){
        r=n-length;
        if((direcao%2)==0){
             coluna=0;
        }else{linha=0;}
        while(r>=0){
             if((direcao%2)==0){
                point=point_word(board,palavra,n,linha,coluna,direcao);
                coluna++;
             }else{
                 point=point_word(board,palavra,n,linha,coluna,direcao);
                 linha++;
             }
             r--;
             if(point2<point){
                point2=point;
             }
        }
     if(point3<point2){
        point3=point2;
        strcpy(palavra2,palavra);
     }
    }

}
printf("%s com %d",palavra2,point3);
return;
}
/*Função de abertura de dicionáro modificado do lab 5
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

  return linhas;
}
