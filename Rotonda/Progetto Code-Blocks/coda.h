
typedef struct scoda* coda;

coda nuova_coda(automobile car);
automobile get_auto_coda(coda brum);
automobile cerca_auto_coda(coda brum, int ID);
coda get_next_coda(coda brum);
coda get_prev_coda(coda inizio, coda fine);
coda accoda_auto_coda(coda brum, automobile car);
coda fine_coda(coda que);
int cancella_coda(coda que);
int cancella_auto_coda(coda parent, coda curr, int ID);
void stampa_coda(coda brum);
void fout_coda(FILE *fp, coda brum);

