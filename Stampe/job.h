
struct sjob{
    //pc sender;
    //char[20] utente;
    int id;
};
typedef struct sjob* job;

job nuovo_job(int id);
int get_id_job(job car);
//pc get_sender_job(job car);
int set_id_job(job car, int id);
int set_dest_job(job car);
int cancella_job(job car);
int stampa_job(job brum);

