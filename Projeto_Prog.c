#include <stdio.h>
#include <stdlib.h>
void print_board (char board[15][15],int n);//função que define e imprime o tabuleiro inicial
void check_board (char board[15][15],int n);//funçao para ser utilizada durante o programa para ver como está o tabuleiro
void write_board (char board[15][15],int n);
int main()
{   char board[15][15]; //endereço do board
    int n;
      printf(" indique o tamanho do tabuleiro, deve ser impar:\n");
      do{
         scanf("%d",&n);
         while((getchar())!='\n'); //limpeza do buffer para usar o fgets() ao longo do programa

         if(n%2==0){
            printf("o tabuleiro tem de ter tamanho impar tente de novo:\n");
         }
         }while((n%2)==0);
    print_board(board,n);

    write_board(board,n);

    return 0;
}
void print_board(char board[15][15],int n){
      int i,j,k;
      char letra,c;
       k=n-1;//usado para o posicionamento dos 2 na board na diagonal invertida

         for(i=0;i<n;i++){
            for(j=0;j<n;j++){
            board[i][j]='.';
           if ((i==0&&j==0)||(i==n-1&&j==0)||(i==0&&j==n-1)||(i==n-1&&j==n-1)){
                    board[i][j]='$';//definir $ nos cantos do tabuleiro
           }else if((i==n/2&&j==0)||(j==n/2&&i==0)||(j==n-1&&i==n/2)||(j==n/2&&i==n-1)){//parametros para o posicionamento do 3 na matriz do tabuleiro
                          board[i][j]='3';
            }else if ((i==(n/2)+1&&(j==1||j==n-2)||(i==(n/2)-1&&(j==1||j==n-2))||(j==(n/2)+1&&(i==1||i==n-2)||(j==(n/2)-1&&(i==1||i==n-2))))){ //parametros para o posicionamento do # na matriz do tabuleiro
                                 board[i][j]='#';
            }else if(i==j){
                                      board[i][j]='2';//posicionamento dos 2 ao longo das diagoanis
                                      board[i][k]='2';
                                      board[k][i]='2';}}
           k--;}//k é usado para definir a diagonal inferior esquerda como 2
      check_board(board,n);
      return ;}

void write_board(char board[15][15],int n){

     int coluna,linha,j,k;
     char x,y,i,palavra[20],direcao,jogada[20];
     j=0;
     i='A';
     printf("Faça uma jogada indicando as coordenadas se é vertical ou horizontal e a palavra que se deseja colocar:\n");


     scanf("%c%d%c %s",&x,&linha,&direcao,palavra);
     //passagem das coordenadas da jogada para ints

     linha--;
     coluna= (int) x - 'A';
     i=palavra[j];
     while (i!='\0'&& i!='\n'){

      board[linha][coluna]=i;

      j++;
      i=palavra[j];
      if(direcao=='H'){
        coluna++;
      }else{linha++;}
     }

     check_board(board,n);


}

void check_board(char board[15][15], int n){

         int i,j;
         char c,letra;
         for(i=0;i<n;i++){
            if(i<=9){printf("%d  ",i+1);}else{

            printf("%d ",i+1);
            }
        for(j=0;j<n;j++){

           printf("%c ",board[i][j]);}

            printf("\n");
        }
      printf("   ");

      c=n-1+'A';

      for(letra='A';letra<=c;++letra){
        printf("%c ",letra);}
      printf("\n");
      return;
}