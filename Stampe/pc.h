#include "stampe.h"

typedef struct spc* pc;

pc nuovo_pc(int id, int priority, stampa coda);
int get_id_pc(pc car);
int get_priority_pc(pc car);
int set_id_pc(pc car, int id);
int set_priority_job(pc car, int priority);
int cancella_pc(pc car);
int stampa_pc(pc brum);
<<<<<<< HEAD
stampa stampa_pc_ex(pc brum, stampa story, int mute);
=======
>>>>>>> 7cbdc228d3de5c716c6f6928d51215cd2cc37968
void set_coda_pc(pc curr,stampa abr);
stampa get_coda(pc curr);

