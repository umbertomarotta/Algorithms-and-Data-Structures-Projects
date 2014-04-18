
typedef struct sjob* job;

job nuovo_job(long id);
long get_id_job(job car);
//pc get_sender_job(job car);
int set_id_job(job car, long id);
int set_dest_job(job car);
int cancella_job(job car);
int stampa_job(job brum);

