#include "libhead.h"

//Função de escrita de uma dada jogada
void putin_board(char board[15][15], int n, jogada play ){
  int linha = play.linha, coluna = play.coluna, i = 0;
  //Verificação que a jogada é válida
  play.pontos = point_word(board, n, play);
  if(play.pontos == 0){
    printf("Jogada inválida\n");
    return;
  }
  //Loop de escrita
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

//Função de cálculo dos pontos duma dada jogada
int point_word(char board[15][15],int n, jogada play){
  int pontos_letras[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
  int a=0,points=0,k=0,f=0, linha = play.linha, coluna= play.coluna, flg = 0;
  char i=play.palavra[a];
  while(i!='\n'&&i!='\0'){
    if(board[linha][coluna]=='#' || ( (int) i > (int) 'z')||( (int) i < (int) 'a') || strlen(play.palavra) < 2 ){
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
         else{
            k = (int) play.palavra[a] - 'a';
            points=points+pontos_letras[k];
            flg++;
         }
    }
    if((play.direcao%2)==0){
      coluna++;
      if (coluna > n)
        return 0;
    }
    else{
      linha++;
      if(linha > n)
        return 0;
    }
    a++;
    i=play.palavra[a];
    }
    if(flg == strlen(play.palavra))
        return 0;
    while(f>0){
        points=points*2;
        f--;
    }

    return points;
}

//Função que procura para uma dada posição a palavra que vale mais pontos de acordo com as específicações dadas no enunciado
jogada *look_word(char board[15][15],int n,int linha,int coluna,int direcao, jogada *lista, char *dicname){
  char **word;
  jogada play = {"\0", linha, coluna, direcao, 0, NULL}, *buffer = NULL;
  int length,i,r, sizeOfDic = 0;
  FILE *Dic;
  if((Dic = fopen(dicname,"r"))==NULL){
    printf("fds nao consegui abrir a merda do eng");
  }

  word = abrir(Dic, n, &sizeOfDic);

//começar procura pelo dicionário
  for(i = 0 ;i<sizeOfDic;i++){

    strcpy(play.palavra,word[i]);
    length = strlen(play.palavra);
    play.linha = linha;
    play.coluna = coluna;
    //palaras maiores que n/2
    if(length >= ((n + 1)/2)){
      r= n-length;
      if((direcao%2)==0)
        play.coluna=r;
      else
        play.linha=r;
      for(; r >= 0; r--){
        play.pontos = point_word(board,n,play);
        if (play.pontos > 0){
          //printf("malloc teu cu %p", buffer);
            buffer = malloc(sizeof(struct Jogadas));
            //printf("malloc teu cu %p", buffer);
            strcpy(buffer->palavra, play.palavra);
            buffer->linha = play.linha;
            buffer->coluna = play.coluna;
            buffer->direcao = play.direcao;
            buffer->pontos = play.pontos;
            lista = putin_playbook(buffer, lista);
        }
        if((direcao%2)==0)
            play.coluna++;
        else
            play.linha++;
      }
    }
    //palavras menores que n/2
    else{
      r = length ;

      for(; r > 0; r--){
        play.pontos = point_word(board,n,play);
        if(play.pontos > 0 ){
          //printf("malloc meu cu %p", buffer);
            buffer = malloc(sizeof(struct Jogadas));
            //printf("malloc meu cu %p", buffer);
            strcpy(buffer->palavra, play.palavra);
            buffer->linha = play.linha;
            buffer->coluna = play.coluna;
            buffer->direcao = play.direcao;
            buffer->pontos = play.pontos;
            lista = putin_playbook(buffer, lista);
        }
        if((direcao%2)==0)
          if(play.coluna <= 0)//Garantir que a palavra não é shifted para fora do tabuleiro
            break;
          else
            play.coluna--;
        else
          if(play.linha <= 0)//Garantir que a palavra não é shifted para fora do tabuleiro
            break;
          else
            play.linha--;
      }
    }
    //cópia de palavra e pocição respetiva caso a pontuação seja maior que a última palavra guardada
  }

for(i=0;i<sizeOfDic;i++){
  free(word[i]);
}
return lista;
}


/*Função de abertura de dicionáro modificada do lab 5
  Toma como parâmetro o apontador para o ficheiro a abrir e o tamanho do tabuleiro*/
char** abrir(FILE *run, int n, int *sizeOfFile){
  char *buffer = malloc(100*sizeof(char)), **linhas;
  int size = 0, i = 0;
  *sizeOfFile = 0;

  //alocação dinâmica do número de palavras (só pomos em memória as palavras com o tamanho do tauleiro)
  while(!feof(run)){
    size = 0;
    fgets(buffer, 100, run);
    size = strlen(buffer) + 1;
    for(i = 0; i < size; i++){
        if(buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n' || buffer[i] == '/'){
            buffer[i] = '\0';
            break;
        }
    }
    size = strlen(buffer);
    if (size > n)
      continue;
    else
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
  for(i = 0; i < *sizeOfFile; i++){
    size = 0;
    fgets(buffer, 100, run);

    size = strlen(buffer) + 1;
    for(int j = 0; j < size; j++){
        if(buffer[j] == ' ' || buffer[j] == '\t' || buffer[j] == '\n' || buffer[j] == '/'){
            buffer[j] = '\0';
            break;
        }
    }
    size = strlen(buffer) +1;
    if (size > n + 1){
      i--;
      continue;
    }
    linhas[i] = (char*) calloc(size, sizeof(char));
    if ( linhas[i] == NULL){
      printf("Erro de memória");
      free(linhas[i]);
      return NULL;
    }
    else{
      strcpy(linhas[i], buffer);
    }
  }

  fclose(run);
  return linhas;
}
