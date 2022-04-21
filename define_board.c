#include "libhead.h"

//Inicializar o board aos valores requeridos
void ini_board(char board[15][15],int n){
  int i,j,k;
  k=n-1;//usado para o posicionamento dos 2 na board na diagonal invertida

  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      board[i][j]='.';
      if (((i==(n/2)+1 && (j==1||j==n-2))||(i==(n/2)-1&&(j==1||j==n-2))||(j==(n/2)+1&&(i==1||i==n-2)||(j==(n/2)-1&&(i==1||i==n-2))))){ //parametros para o posicionamento do # na matriz do tabuleiro
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
  fflush(stdout);
  return;
 }

int imp_board(char board[15][15],int n, char *filename){
    FILE *imp =  fopen(filename,"r");;
    int i=0,j,linha=0,coluna=0,k=0;
    char *imps[35],palavra[35],palavra2[35];
    for(i=0;i<=35;i++){
        imps[i]= (char*) malloc(1000*sizeof(char));
    }
    if(imp==NULL){
        printf("falha a abrir o tabuleiro");
        return 0;
    }

    for(i=0;i<20;i++){
        fgets(imps[i],100,imp);
    }
    i=0;
    do{
    strcpy(palavra,imps[i]);
    printf("%s",palavra);

    for(j=3;j<20;j++){
       if(palavra[j]!=' '){
         palavra2[k]=palavra[j];
         k++;
       }
    }
    printf("%s",palavra2);
    for(k=0;k<15;k++){
        board[linha][coluna]=palavra2[k];
        coluna++;
    }
    linha++;

    k=0;
    coluna=0;
    i++;
    }while(strchr(imps[i],'A')==NULL&&linha!=15);

    for(i=0;i<20;i++){
        free(imps[i]);
    }
    fclose(imp);
    return linha;
 }

