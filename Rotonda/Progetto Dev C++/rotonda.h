#define DIM 15

typedef struct srotonda* rotonda;

/*Inizializzazione*/
rotonda nuova_rotonda();
rotonda cancella_rotonda(rotonda rot);
rotonda random_rotonda(int numauto, int numuscite);

/*Metodi Standard*/
int get_numero_strade(rotonda rot);
int rotonda_nextval(rotonda rot);
char rotonda_nextchar(rotonda rot);
int rotonda_vuota(rotonda rot);

/*Gestione Strade*/
strada cerca_strada(rotonda rot, char nome);
int inserisci_strada(rotonda rot, int i);
int cancella_strada_rotonda(rotonda rot, char nome);
int cancella_auto_rotonda(rotonda rot, int ID);

/*Gestione Auto*/
automobile cerca_auto(rotonda rot, int ID);
int inserisci_auto_strada(rotonda rot, automobile car, char nome);
int accoda_auto_rotonda_random(rotonda rot, int num);

/*Simulazione*/
void step_rotonda(rotonda rot, double secondi);
void stampa_rotonda(rotonda rot);

/*File Load&Store*/
rotonda fleggi_rotatoria(char *nomeF);
void fout_rotatoria(rotonda rot, char* nomeF);
