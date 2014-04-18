#include <stdio.h>
#include <stdlib.h>
#include "automobile.h"
#include "coda.h"

struct scoda{
    automobile macchina;
    struct scoda* next;
};

automobile get_auto_coda(coda brum){
    if(brum) return brum->macchina;
    else return NULL;
}

coda get_next_coda(coda brum){
    if(brum) return brum->next;
    else return NULL;
}

coda get_prev_coda(coda inizio, coda fine){
    if(!inizio || inizio == fine) return NULL;
    else if (inizio->next == fine) return inizio;
    else return get_prev_coda(inizio->next, fine);
}

coda accoda_auto_coda(coda brum, automobile car){
    if(brum) brum->next = accoda_auto_coda(brum->next, car);
    else return nuova_coda(car);
    return brum;
}

coda nuova_coda(automobile car){
    coda brum = (coda)malloc(sizeof(struct scoda));
    brum->macchina = car;
    brum->next = NULL;
    return brum;
}

coda fine_coda(coda que){
    if (que != NULL){
        if (que->next == NULL) return que;
        else return fine_coda(que->next);
    }
    return NULL;
}

int cancella_coda(coda que){
    if (que == NULL) return 0;
    int ncar = cancella_coda(que->next);
    ncar += cancella_auto(que->macchina);
    free(que);
    return ncar;
}

int cancella_auto_coda(coda parent, coda curr, int ID){
    if ( !curr || !parent ) return 0;
    else if(get_id_auto(curr->macchina) == ID){
        parent->next = curr->next;
        cancella_auto(curr->macchina);
        free(curr);
        if (parent->next == NULL) return 2;
        else return 1;
    }
    else return cancella_auto_coda(curr, curr->next, ID);
}

void stampa_coda(coda brum){
    if (brum == NULL) return;
    printf("< ");
    stampa_auto(brum->macchina);
    printf(" ");
    stampa_coda(brum->next);
}

automobile cerca_auto_coda(coda brum, int ID){
    automobile ptr=NULL;
    if(brum!=NULL)
    {
        if(get_id_auto(brum->macchina)==ID)
            ptr=brum->macchina;
    else ptr=cerca_auto_coda(brum->next, ID);
    }
    return ptr;
}

void fout_coda(FILE *fp, coda brum){
    if (brum != NULL)
    {
        if (brum->macchina != NULL)
        {
            fprintf(fp,"%d %d ", get_id_auto(brum->macchina), get_dest_auto(brum->macchina));
            if(brum->next!=NULL)
                    fprintf(fp,"%c ",'-');
            else fprintf(fp,"%c ",'|');
        }
        if(brum->next) fout_coda(fp,brum->next);
    }
    else fprintf(fp,"%d %d %c ",-1,-1,'|');
}
