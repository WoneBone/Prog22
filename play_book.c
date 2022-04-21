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
    int tesoura = (lista->pontos)/2;
    jogada *Aux1 = lista, *Aux2 = lista->next;
    while (Aux2->next != NULL && Aux2->pontos >= tesoura){
        Aux1 = Aux2;
        Aux2 = Aux1->next;
    }
    while (Aux1->next != NULL)
    {
        Aux1->next = Aux2->next;
        Aux2->next =NULL;
        free(Aux2);
        Aux2 = Aux1->next;
    }
    return lista;
}


