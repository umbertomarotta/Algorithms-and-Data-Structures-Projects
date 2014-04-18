
typedef struct spc* pc;

pc nuovo_pc(int id, int priority, stampa coda);
int get_id_pc(pc car);
pc get_priority_pc(pc car);
int set_id_pc(pc car, int id);
int set_priority_job(pc car, int priority);
int cancella_pc(pc car);
int stampa_pc(pc brum);

