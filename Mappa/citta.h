#ifndef __CITY_H
#define __CITY_H
#define WORLD_SIZE 300

struct scitta{
    int posX;
    int posY;
    char* nome;
    int livello;
    int fazione;
    int isola;
};

typedef struct scitta* citta;
citta citta_Nuova(char* nome, int posx, int posy, int liv);
citta citta_Random();
citta citta_fromString(char* s);
char* citta_toString(citta c1);
int citta_Cancella(citta city);

int citta_Distanza(citta c1, citta c2);
int citta_livello(citta c1);
int citta_stampa(citta c1);

#endif
