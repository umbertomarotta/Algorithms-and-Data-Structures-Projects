#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <assert.h>
#include <stdarg.h>

#include "mappa.h"
#include "citta.h"
#include "grafo.h"
#include "utils.h"

#define DIM 1000
#define FAST 1
#define MUTE 1

citta* mappa_getCities(mappa map){
    return map->cities;
}

char* mappa_getNomeCitta(mappa map, int i){
    return map->cities[i]->nome;
}

int mappa_getNumCitta(mappa map){
    return map->NumCitta;
}

void mappa_cittaDecr(mappa map){
    map->NumCitta--;
}

int mappa_CancellaCitta(mappa map, int id){
    if(!map && id >= map->NumCitta) return 1;
    int i;
    grafo_RimuoviNodo(map->Voli, id);
    grafo_RimuoviNodo(map->Ferrovie, id);
    grafo_RimuoviNodo(map->Autostrade, id);
    grafo_RimuoviNodo(map->Strade, id);
    citta_Cancella(map->cities[id]);
    map->NumCitta -= 1;
    for (i = id; i < map->NumCitta; i++) map->cities[i] = map->cities[i+1];
    map->cities = realloc(map->cities, sizeof(citta)*(map->NumCitta));
    return 0;
}

int mappa_stampaPercorso(mappa map, lista city, lista mezzi) {
    if(!map || !city || !mezzi) return 1;
    if(!list_size(city)) return printf("Non ci puoi arrivare!\n");
    int curr_city;
    char nomeR[50];

    list_head(city, &curr_city, 1);
    printf("Ti trovi a %s (%d)\n", mappa_getNomeCitta(map, curr_city), curr_city);
    while(list_size(mezzi) && list_size(city))
    {
        list_head(mezzi, &nomeR, 1);
        list_head(city, &curr_city, 1);
        if(!list_size(mezzi)) printf("Infine ");
        printf("Prendi %s per %s (%d)\n", nomeR, mappa_getNomeCitta(map, curr_city), curr_city);
    }
    return 0;
}

grafo grafo_getVoli(mappa map){
    return map->Voli;
}

grafo grafo_getFerrovie(mappa map){
    return map->Ferrovie;
}

grafo grafo_getAutostrade(mappa map){
    return map->Autostrade;
}

grafo grafo_getStrade(mappa map){
    return map->Strade;
}

mappa mappa_nuova_hardcode(int numcitta){
    mappa map = (mappa)malloc(sizeof(struct smappa));
    map->Costo_Aereo = 0.20F; //Basato su costo al chilometro di un volo alitalia
    map->Costo_Treno = 0.08F; //Basto sul costo di un treno italo
    map->Costo_Pedaggio = 0.06F; //http://www.autostrade.it/documents/10279/25719/tariffa.gif
    map->Costo_Benzina = 0.09F; //Basato sul consumo di una fiat panda
    map->Vel_Aereo = 850; //Velocità massima di un aribus A320
    map->Vel_Treno = 300; //Velocità frecciarossa
    map->Vel_Autostrade = 120; //Autostrade italiane
    map->Vel_Strade = 50; //strade italiane
    map->NumCitta = numcitta;
    map->cities = calloc(numcitta, sizeof(citta));
    citta* city = map->cities;
    int i, j, li, lj;
    int numpesi = 2;
    for (i=0; i<numcitta; i++) city[i] = citta_Random();
    map->Voli = grafo_Nuovo(numcitta, numpesi);
    map->Ferrovie = grafo_Nuovo(numcitta, numpesi);
    map->Autostrade = grafo_Nuovo(numcitta, numpesi);
    map->Strade = grafo_Nuovo(numcitta, numpesi);
    grafo_Rinomina(map->Voli, "l'aereo");
    grafo_Rinomina(map->Ferrovie, "il treno");
    grafo_Rinomina(map->Autostrade, "l'autostrada");
    grafo_Rinomina(map->Strade, "la strada");
    double tempo, costo, dist;
    int str=0, aut=0, tre=0, vol=0;

    /* DEBUG */
    int work = numcitta*numcitta, done = 0;
    time_t tim = time(NULL);

    for (i=0; i<numcitta; i++){
        for (j=0; j<numcitta; j++){

            /* DEBUG */
            done++;
            if (difftime(time(NULL),tim) >= 1) {
                clear_screen();
                if (!MUTE) printf("CARICAMENTO: %d/%d (%1.2f%%)\n", done, work, (float)(done*100)/work);
                tim = time(NULL);
            }
            if (i==j) continue;
            dist = (double)citta_Distanza(city[i], city[j]);
            li = citta_livello(city[i]);
            lj = citta_livello(city[j]);
            tempo = (dist/map->Vel_Aereo);
            if( FAST || tempo*2 < grafo_raggiunge(map->Voli, i, j))
            if(i > j && ((dist > 1000 && li > 3 && lj > 3) || (dist > 180 && dist < 1000 && li > 2 && lj > 2))){
                costo = (dist*map->Costo_Aereo);
                grafo_AggiungiArco(map->Voli, i, j, 2, tempo, costo);
                grafo_AggiungiArco(map->Voli, j, i, 2, tempo, costo);
                vol++;
            }
            dist = (dist*1.5); //impedimenti Geografici
            tempo = (dist/map->Vel_Treno);
            if( FAST || tempo*2 < grafo_raggiunge(map->Ferrovie, i, j))
            if(i > j && dist > 100 && dist < 500  && li > 1 && lj > 1){
                //printf("Fer\n");
                costo = (dist*map->Costo_Treno);
                grafo_AggiungiArco(map->Ferrovie, i, j, 2, tempo, costo);
                grafo_AggiungiArco(map->Ferrovie, j, i, 2, tempo, costo);
                tre++;
            }
            tempo = (dist/map->Vel_Autostrade);
            if( FAST || tempo*2 < grafo_raggiunge(map->Autostrade, i, j))
            if(i > j && dist > 50 && dist < 300  && li > 0 && lj > 0 ){
                //printf("Auto\n");
                costo = (dist*(map->Costo_Pedaggio + map->Costo_Benzina));
                grafo_AggiungiArco(map->Autostrade, i, j, 2, tempo, costo );
                grafo_AggiungiArco(map->Autostrade, j, i, 2, tempo, costo );
                aut++;
            }
            tempo = dist/map->Vel_Strade;
            if( FAST || tempo*2 < grafo_raggiunge(map->Strade, i, j))
            if(i > j && dist < 50){
                //printf("Str\n");
                costo = dist*map->Costo_Pedaggio;
                grafo_AggiungiArco(map->Strade, i, j, 2, tempo, costo);
                grafo_AggiungiArco(map->Strade, j, i, 2, tempo, costo);
                str++;
            }
        }
    }

    /* DEBUG */
    clear_screen();
    if(!MUTE){
        printf("Numero Citta: %d\n", numcitta);
        printf("Strade Interurbane: %d\n", str);
        printf("Tratte Autostradali: %d\n", aut);
        printf("Tratte Ferroviarie: %d\n", tre);
        printf("Voli: %d\n", vol);
        printf("\n");
    }
    return map;
}

mappa mappa_nuova_hardcore(int numcitta){
    mappa map = (mappa)malloc(sizeof(struct smappa));
    map->Costo_Aereo = 0.20F; //Basato su costo al chilometro di un volo alitalia
    map->Costo_Treno = 0.08F; //Basto sul costo di un treno italo
    map->Costo_Pedaggio = 0.06F; //http://www.autostrade.it/documents/10279/25719/tariffa.gif
    map->Costo_Benzina = 0.09F; //Basato sul consumo di una fiat panda
    map->Vel_Aereo = 850; //Velocità massima di un aribus A320
    map->Vel_Treno = 300; //Velocità frecciarossa
    map->Vel_Autostrade = 120; //Autostrade italiane
    map->Vel_Strade = 50; //strade italiane
    map->NumCitta = numcitta;
    map->cities = calloc(numcitta, sizeof(citta));
    citta* city = map->cities;
    int i;
    //int numpesi = 2;
    for (i=0; i<numcitta; i++) city[i] = citta_Random();

    map->Voli = mappa_CoperturaMin(city, numcitta, map->Costo_Aereo, map->Vel_Aereo, 200, 1000, 3);
    map->Ferrovie = mappa_CoperturaMin(city, numcitta, map->Costo_Treno, map->Vel_Treno, 30, 400, 2);
    map->Autostrade =  mappa_CoperturaMin(city, numcitta, (map->Costo_Pedaggio + map->Costo_Benzina), map->Vel_Autostrade, 20, 100, 1);
    map->Strade = mappa_CoperturaMin(city, numcitta, map->Costo_Benzina, map->Vel_Strade, 0, 100, 0);
    grafo_Rinomina(map->Voli, "Voli");
    grafo_Rinomina(map->Ferrovie, "Ferrovie");
    grafo_Rinomina(map->Autostrade, "Autostrade");
    grafo_Rinomina(map->Strade, "Strade");


    return map;
}

int mappa_stampa(mappa map){
    if(!map) return 1;
    grafo_Stampa(map->Voli);
    printf("\n\n");
    grafo_Stampa(map->Ferrovie);
    printf("\n\n");
    grafo_Stampa(map->Autostrade);
    printf("\n\n");
    grafo_Stampa(map->Strade);
    printf("\n\n");
    return 0;
}

int mappa_getCostoMezzo(int vel_media, int tempo, int costo_mezzo){
    return (vel_media*tempo)*costo_mezzo;
}

int mappa_StampaCitta(mappa map){
    if(!map) return 1;
    int res = 10;
    int i, j, x, y;
    int matr[res][res];
    for(i=0; i<res; i++) for(j=0; j<res; j++) matr[i][j] = -1;
    for(i=0; i<map->NumCitta; i++){
        printf("ID: %04d ", i);
        x = ((map->cities[i]->posX)*res)/WORLD_SIZE;
        y = ((map->cities[i]->posY)*res)/WORLD_SIZE;
        matr[res-1-y][x] = i;
        citta_stampa(map->cities[i]);
        printf("\n");
    }
    printf("\nMappa: %d Km^2\n_", WORLD_SIZE*WORLD_SIZE);
    for(i=0; i<res; i++) printf("_____");
    printf("_\n|");
    for(i=0; i<res; i++){
        for(j=0; j<res; j++){
            if (matr[i][j] != -1) printf("%4d ", matr[i][j]);
            else printf("     ");
        }
        printf("|\n|");
    }
    for(i=0; i<res; i++) printf("_____");
    printf("|\n");
    return 0;
}

grafo mappa_CoperturaMin(citta* cities, int numc, float cost, int vel, int distmin, int distmax, int lmin){
    if(!cities || numc <= 0) return NULL;
    int i, j, start = 0;

    //cerco la citta' piu' grande
    for(i = 0; i<numc; i++) if(cities[i]->livello > cities[start]->livello) start = i;

    //Costruisco grafo delle distanze
    int matr[numc][numc], w;
    for(i = 0;  i< numc; i++){
        for(j = 0; j < numc; j++){
            w = citta_Distanza(cities[i], cities[j]);
            if(i!=j && w >= distmin && w <= distmax && cities[i]->livello >= lmin && cities[j]->livello >= lmin){
                    matr[i][j] = w;
                    matr[j][i] = w;
            }
            else{
                matr[i][j] = 0;
                matr[j][i] = 0;
            }
            printf("%4d ", matr[i][j]);
        }
        printf("\n");
    }
     printf("\n\n");
    int num = 0;
    int pres[numc];
    for(i = 0; i<numc; i++) pres[i] = 0;

    grafo G = grafo_Nuovo(numc, 2);
    pres[start] = 1;
    int min[2] = {start , 0};
    if(pres[min[1]]) min[1]++;

    while (num != numc){
        for(i = 0; i<numc; i++){
            for(j = 0; j<numc; j++) {
                if(matr[i][j] && pres[i] && !pres[j] && matr[i][j] < matr[min[0]][min[1]]){
                    min[0] = i;
                    min[1] = j;
                }
            }
        }
        if(matr[min[0]][min[1]]){
            grafo_AggiungiArco(G,  min[0], min[1], 2, 1., 1.);
            grafo_AggiungiArco(G,  min[1], min[0], 2, 1., 1.);
        }
        pres[min[1]] = 1;
        for(i = 0; i<numc; i++){
            if(!pres[i]){
                min[1] = i;
                break;
            }
        }
        num++;
    }
    return G;

}

int mappa_mapToFile(mappa map, char* nomeF)
{
    FILE* fp = fopen(nomeF,"w+");
    int i=0;
    char* s;
    if(fp!=NULL)
    {

        fprintf(fp,"%d ",map->NumCitta);
        fprintf(fp,"%.2f %.2f ",map->Costo_Aereo, map->Costo_Treno);
        fprintf(fp,"%.2f %.2f ",map->Costo_Pedaggio, map->Costo_Benzina);
        fprintf(fp,"%d %d ",map->Vel_Aereo, map->Vel_Treno);
        fprintf(fp,"%d %d\n",map->Vel_Autostrade, map->Vel_Strade);
        s = grafo_toString(map->Voli);
        fprintf(fp,"%s\n", s);
        free(s);
        s = grafo_toString(map->Ferrovie);
        fprintf(fp,"%s\n", s);
        free(s);
        s = grafo_toString(map->Autostrade);
        fprintf(fp,"%s\n", s);
        free(s);
        s = grafo_toString(map->Strade);
        fprintf(fp,"%s\n", s);
        free(s);
        while(i<map->NumCitta){
            s = citta_toString(map->cities[i]);
            fprintf(fp,"%s\n", s);
            free(s);
            i++;
        }
        fclose(fp);
        return 1;
    }
    fclose(fp);
    return 0;
}

mappa mappa_mapFromFile(char* nomeF)
{
    FILE* fp = fopen(nomeF,"r");
    citta* city=NULL;
    int i=0;
    char* strgrafo;
    char citta[100];
    mappa map=NULL;
    if(fp!=NULL)
    {
        map = (mappa)malloc(sizeof(struct smappa));
        fscanf(fp,"%d ",&(map->NumCitta));
        strgrafo = (char*)malloc(sizeof(char)*((map->NumCitta*map->NumCitta)*2)*100);
        fscanf(fp,"%f %f ", &(map->Costo_Aereo), &(map->Costo_Treno));
        fscanf(fp,"%f %f ", &(map->Costo_Pedaggio), &(map->Costo_Benzina));
        fscanf(fp,"%d %d ", &(map->Vel_Aereo), &(map->Vel_Treno));
        fscanf(fp,"%d %d\n", &(map->Vel_Autostrade), &(map->Vel_Strade));
        fscanf(fp,"%[^\n]\n",strgrafo);
        //fgets(strgrafo,INT_MAX,fp);
        map->Voli = grafo_fromString(strgrafo);
        fscanf(fp,"%[^\n]\n",strgrafo);
        //fgets(strgrafo,INT_MAX,fp);
        map->Ferrovie = grafo_fromString(strgrafo);
        fscanf(fp,"%[^\n]\n",strgrafo);
        //fgets(strgrafo,INT_MAX,fp);
        map->Autostrade = grafo_fromString(strgrafo);
        fscanf(fp,"%[^\n]\n",strgrafo);
        //fgets(strgrafo,INT_MAX,fp);
        map->Strade = grafo_fromString(strgrafo);
        map->cities = calloc(map->NumCitta, sizeof(citta));

        city = map->cities;
        for (i=0; i < map->NumCitta; i++){
            fscanf(fp,"%[^\n]\n", strgrafo);
            //fgets(citta,INT_MAX,fp);
            city[i] = citta_fromString(strgrafo);
        }
        free(strgrafo);
        fclose(fp);
        return map;
    }
    fclose(fp);
    return NULL;
}

int mappa_cancella(mappa map){
    if(!map) return 1;
    int i;
    for (i=0; i < map->NumCitta; i++) citta_Cancella(map->cities[i]);
    free(map->cities);
    grafo_Cancella(map->Voli);
    grafo_Cancella(map->Ferrovie);
    grafo_Cancella(map->Autostrade);
    grafo_Cancella(map->Strade);
    return 1;
}

int mappa_AggiungiCitta(mappa map, char* nome, int posx, int posy, int liv){
    if(!map) return 1;
    map->NumCitta += 1;
    if(map->NumCitta == 1) map->cities = calloc(map->NumCitta, sizeof(citta));
    else map->cities = realloc(map->cities, sizeof(citta)*map->NumCitta);
    map->cities[map->NumCitta-1] = citta_Nuova(nome, posx, posy, liv);
    grafo_AggiungiNodi(map->Voli, 1);
    grafo_AggiungiNodi(map->Ferrovie, 1);
    grafo_AggiungiNodi(map->Autostrade, 1);
    grafo_AggiungiNodi(map->Strade, 1);
    return 0;
}






