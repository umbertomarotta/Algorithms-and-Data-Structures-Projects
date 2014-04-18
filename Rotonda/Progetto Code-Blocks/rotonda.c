#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "automobile.h"
#include "coda.h"
#include "strada.h"
#include "rotonda.h"

struct srotonda{
    automobile posizione[DIM];
    strada incrocio[DIM];
    int inizio;
    int n_car;
    int n_road;
    int carseq;
    char roadseq;
};

int get_numero_strade(rotonda rot){
    return rot->n_road;
}

rotonda nuova_rotonda(){
    rotonda rot = (rotonda)malloc(sizeof(struct srotonda));
    int i=0;
    for (i=0; i<DIM; i++){
        rot->posizione[i] = NULL;
        rot->incrocio[i] = NULL;
    }
    rot->inizio = 0;
    rot->n_car = 0;
    rot->n_road = 0;
    rot->carseq = 0;
    rot->roadseq = 'A';
    return rot;
}

rotonda cancella_rotonda(rotonda rot){
    if (rot == NULL) return NULL;
    int i;
    for(i=0; i<DIM; i++){
        cancella_strada(rot->incrocio[i]);
        cancella_auto(rot->posizione[i]);
    }
    free(rot);
    return NULL;
}

int accoda_auto_rotonda_random(rotonda rot, int num){
    if ( rot == NULL || !(rot->n_road) ) return 0;
    int i;
    rot->n_car += num;
    printf("check");
    while(num){
        i=rand()%DIM;
        if(rand()%10 > 5 && rot->incrocio[i] != NULL){
            accoda_auto_strada(rot->incrocio[i], nuova_auto(rand()%(rot->n_road), rotonda_nextval(rot)));
            num--;
        }
    }
    return 1;
}

int cancella_strada_rotonda(rotonda rot, char nome){
    int i;
    if(rot == NULL) return 0;
    for(i=0; i < DIM; i++){
        if(rot->incrocio[i] != NULL && get_nome_strada(rot->incrocio[i]) == nome){
            rot->n_car -= cancella_strada(rot->incrocio[i]);
            rot->n_road -= 1;
            rot->incrocio[i] = NULL;
            return 1;
        }
    }
    return 0;
}

int rotonda_nextval(rotonda rot){
    int ret = rot->carseq;
    rot->carseq += 1;
    return ret;
}

char rotonda_nextchar(rotonda rot){
    int ret = rot->roadseq;
    rot->roadseq += 1;
    return ret;
}

int inserisci_strada(rotonda rot, int i){
    if (rot->incrocio[i%DIM] != NULL) return 0;
    rot->incrocio[i] = nuova_strada(rotonda_nextchar(rot), NULL);
    rot-> n_road += 1;
    return 1;
}

rotonda random_rotonda(int numauto, int numuscite){
    rotonda rot = nuova_rotonda();
    int i = rot->inizio;
    int destmax = numuscite;
    int autofuori = 0;
    if (numuscite)
        autofuori = numauto - (rand()%(numauto+1));
    int autodentro = numauto - autofuori;
    if (autodentro > DIM){
        if (numuscite)
            autofuori = autofuori + (autodentro - DIM);
        autodentro = DIM;
    }
    if (numuscite > DIM) numuscite = DIM;
    rot->n_car = autodentro + autofuori;
    rot->n_road = numuscite;
    while(autodentro)
    {
        if(rand()%10 > 5 && rot->posizione[i] == NULL)
        {
            rot->posizione[i] = nuova_auto(rand()%(destmax-1), rotonda_nextval(rot));
            autodentro--;
        }
        i = (i+1)%DIM;

    }
    i=rot->inizio;
    while(numuscite){
        if(rand()%10 > 5 && rot->incrocio[i] == NULL){
            rot->incrocio[i] = nuova_strada(rotonda_nextchar(rot), NULL);
            numuscite--;
        }
        i = (i+1)%DIM;
    }
    i=rot->inizio;
    while(autofuori){
        if(rand()%10 > 5 && rot->incrocio[i] != NULL){
            accoda_auto_strada(rot->incrocio[i], nuova_auto(rand()%(destmax-1), rotonda_nextval(rot)));
            autofuori--;
        }
        i = (i+1)%DIM;
    }
    return rot;
}

void stampa_rotonda(rotonda rot){
    if(rot!=NULL){
        int i=rot->inizio;
        int j=0;
        printf("\n |.......|\n");
        for (j=0; j<DIM; j++){
        //for (j=DIM-1; j>=0; j--){
            //if(rot->posizione[i] != NULL) {
            printf(" | ");
            stampa_auto(rot->posizione[i]);
            printf(" ");
            //}
            //else printf(" |   ");
            if(rot->incrocio[j]!= NULL){
                printf("= %c ", get_nome_strada(rot->incrocio[j]) );
                if (get_inizio_strada(rot->incrocio[j]) != NULL) stampa_coda(get_inizio_strada(rot->incrocio[j]));
                //else printf("vuota");
            }
            else printf("|");
            printf("\n |   |   |\n");
            i=(i+1)%DIM;
        }
        printf(" |.......|\n");
        printf("\nNumero auto: %d\n",rot->n_car);
        printf("\nNumero strade: %d\n",rot->n_road);
    }
}

void step_rotonda(rotonda rot, double secondi){
    time_t tim = time(NULL);
    rot->inizio = (rot->inizio + 1)%DIM; //Scorre su
    //rot->inizio = (rot->inizio - 1); if (rot->inizio < 0) rot->inizio = DIM - 1; //Socorre giù
    int j=0, i=rot->inizio, mod = 0;
    for (j=0; j<DIM; j++){
    //for (j=DIM-1; j>=0; j--){
        mod = (i+j)%DIM;
        if(rot->posizione[mod] == NULL && rot->incrocio[j] != NULL) //L'auto entra
        {
            rot->posizione[mod] = decoda_auto_strada(rot->incrocio[j]);
        }
        else if(rot->posizione[mod] != NULL && rot->incrocio[j] != NULL) //L'auto passa un uscite
            {
            set_dest_auto(rot->posizione[mod], get_dest_auto(rot->posizione[mod])-1);
            if (get_dest_auto(rot->posizione[mod]) < 0) //L'auto esce
            {
                free(rot->posizione[mod]);
                rot->n_car--;
                rot->posizione[mod] = decoda_auto_strada(rot->incrocio[j]);

            }
        }
    }
    while(difftime(time(NULL),tim) < secondi); //consente di fare lo step nel mentre
}

int rotonda_vuota(rotonda rot){
    if(rot->n_car==0) return 1;
    else return 0;
}

strada cerca_strada(rotonda rot, char nome){
    int i;
    if(rot != NULL){
        for(i=0; i < DIM; i++){
            if(rot->incrocio[i] != NULL && get_nome_strada(rot->incrocio[i]) == nome)
                return rot->incrocio[i];
        }
    }
    return NULL;
}

int inserisci_auto_strada(rotonda rot, automobile car, char nome){
    strada brum = NULL;
    brum = cerca_strada(rot, nome);
    if (brum && car){
        accoda_auto_strada(brum, car);
        rot->n_car += 1;
        return 1;
    }
    return 0;
}

automobile cerca_auto(rotonda rot, int ID){
    int i;
    automobile tmp = NULL;
    if(rot!=NULL)
    {
        for(i=0;i<DIM;i++)
        {
            if(rot->posizione[i]!=NULL)
                if( get_id_auto(rot->posizione[i]) == ID)
                    return rot->posizione[i];
                if(rot->incrocio[i]!=NULL)
                {
                    tmp=cerca_auto_coda( get_inizio_strada(rot->incrocio[i]),ID);
                    if(tmp!=NULL) return tmp;
                }
        }

    }
    return tmp;
}

rotonda fleggi_rotatoria(char *nomeF){
    char c, roadseq = 'A';
    int ID, dest;
    rotonda rot = nuova_rotonda();
    int i = 0;
    FILE *fp = fopen(nomeF,"r");
    if (fp == NULL){
        return NULL;
    }
    while(fscanf(fp,"%d %d %c ",&ID,&dest,&c)!=EOF && i<DIM)
    {
        if(ID!=-1 && dest!=-1)
        {
            rot->posizione[i] = nuova_auto(dest, ID);
            rot->n_car++;
            if(rot->carseq < ID) rot->carseq = ID;
        }
        if(c<='Z' && c >= 'A')
        {
            if(c > roadseq) roadseq = c;
            rot->incrocio[i] = nuova_strada(c,NULL);
            rot->n_road++;
            while(c!='|')
            {
                fscanf(fp,"%d %d %c ", &ID, &dest, &c);
                if(ID != -1 || dest != -1)
                {
                    accoda_auto_strada(rot->incrocio[i],nuova_auto(dest,ID));
                    rot->n_car++;
                    if(rot->carseq < ID) rot->carseq=ID;
                }
            }
        }
        i++;
    }
    while(roadseq != rotonda_nextchar(rot));
    fclose(fp);
    return rot;
}

void fout_rotatoria(rotonda rot, char* nomeF){
    FILE *fp = fopen(nomeF,"w+");
    int i=0;
    int j=rot->inizio;
    for(i=0;i<DIM;i++)
    //int i=rot->inizio;
    //for(i=rot->inizio; i<DIM+rot->inizio; i=(i+1)%DIM)
    {
        if(rot->posizione[j]!=NULL && rot->incrocio[i]!=NULL)
        {
            fprintf(fp,"%d %d %c ", get_id_auto(rot->posizione[j]), get_dest_auto(rot->posizione[j]), get_nome_strada(rot->incrocio[i]));
            fout_coda(fp,get_inizio_strada(rot->incrocio[i]));
        }
        else if(rot->posizione[j]==NULL && rot->incrocio[i]!=NULL)
        {
            fprintf(fp,"%d %d %c ",-1,-1,get_nome_strada(rot->incrocio[i]));
            fout_coda(fp,get_inizio_strada(rot->incrocio[i]));
        }
        else if(rot->posizione[j]!=NULL && rot->incrocio[i]==NULL)
            fprintf(fp,"%d %d %c ",get_id_auto(rot->posizione[j]), get_dest_auto(rot->posizione[j]),'|');
        else if(rot->posizione[j]==NULL && rot->incrocio[i]==NULL)
                fprintf(fp,"%d %d %c ", -1, -1, '|');
        j=(j+1)%DIM;
    }
    fclose(fp);
}

int cancella_auto_rotonda(rotonda rot, int ID){
    int i;
    for(i=0;i<DIM;i++){
        if(get_id_auto(rot->posizione[i])==ID){
            cancella_auto(rot->posizione[i]);
            rot->posizione[i]=NULL;
            rot->n_car--;
            return 1;
        }
        if(cancella_auto_strada(rot->incrocio[i],ID)){
            rot->n_car--;
            return 1;
        }
    }
return 0;
}


