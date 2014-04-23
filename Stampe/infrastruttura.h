#define DIM_I 50

typedef struct sinfrastruttura* infrastruttura;

infrastruttura get_random_system();
void simulate(infrastruttura);
void stampa_coda(infrastruttura);
void update_priority_I(infrastruttura);
