#ifndef LIBHEAD_INCLUDED
#define LIBHEAD_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#define ARG_LIST "ht:d:l:m:n:i:j:o:r:"


typedef struct Jogadas
{
  char palavra[50];
  int linha;
  int coluna;
  int direcao;
  int pontos;
  struct Jogadas *next;
}jogada;

typedef struct Files
{
  char *dicname;
  char *imp;
  char *playbook_archive;
  char *final_putin;
}files;

void ini_board (char board[15][15],int n);
int imp_board (char board[15][15],int n, char *filename);
void print_board (char board[15][15],int n);
int modo_1 (char board[15][15],int n, int*);
void modo_2(char board[15][15], int n, files ficheiro, int j);
int point_word(char board[15][15], int n, jogada);
jogada *look_word(char board[15][15],int n,int linha,int coluna,int direcao, jogada* play, char *dicname);
void putin_board(char board[15][15], int n, jogada);
char **abrir(FILE* ,int, int*);
jogada*putin_playbook(jogada *play,jogada *lista );
jogada *burn_playbook(jogada *lista);
void print_playbook(jogada* lista, FILE* file);
jogada *snip_playbook(jogada *lista);
void help();

#endif // LIBHEAD_INCLUDED
