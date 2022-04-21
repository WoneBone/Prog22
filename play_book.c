#include "libhead.h"

jogada*putin_playbook(jogada *play,jogada *lista){
  jogada *AuxH, *AuxT;

        if(lista == NULL){
            lista = play;
            lista->next = NULL;
        }
        else
        {
           if (lista->pontos < play->pontos)
            {
                play->next = lista;
                lista = play;
            }
            else
            {
				AuxH = lista;
				AuxT = lista->next;
				while((AuxT != NULL) && AuxT->pontos>play->pontos)
				{
					AuxH = AuxT;
					AuxT = AuxT->next;
				}
				play->next = AuxT;
				AuxH->next = play;
			}
        }
		return lista;
}
jogada *burn_playbook(jogada *lista){

    jogada *Aux;
    Aux = lista;
    while( lista != NULL)
    {
        Aux = lista;
        lista = lista->next;
        free(Aux);
    }
    return NULL;
}
void remove_nextin_playbook(jogada*play){
    jogada *AuxH;
    AuxH = play-> next;
    play->next = AuxH->next;
    free(AuxH);
}
void print_playbook(jogada *lista, FILE *file){
    char dir;
    jogada *Aux = lista;
    while(Aux != NULL){
            if (Aux->direcao %2 == 0)
                dir = 'H';
            else
                dir = 'V';
    fprintf(file, "%c%d%c %s %d pontos\n", ((char) Aux->coluna + 'A'), Aux->linha + 1, dir, Aux->palavra, Aux->pontos);
    Aux = Aux->next;
    }
    return;
}
jogada *snip_playbook(jogada *lista){
    int tesoura = lista->pontos/2;
    jogada *Aux = lista;
    while (Aux->next != NULL){
        Aux = Aux->next;
        if(Aux->pontos < tesoura){
            remove_nextin_playbook(Aux);
        }
    }
    free(Aux);

}


