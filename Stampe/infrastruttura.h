#define DIM_I 50

typedef struct sinfrastruttura* infrastruttura;

infrastruttura get_random_system();
void simulate(infrastruttura);
void simulate_fast(infrastruttura system);
void stampa_coda(infrastruttura);
void update_priority_I(infrastruttura);
int dealloca_infr(infrastruttura system);
void insert_job_pc_I(infrastruttura);
void delete_job_I(infrastruttura);
