#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "job.h"
//#include "stampe.h"
//#include "pc.h"
//#include "heap.h"
#include "infrastruttura.h"
#include "utils.h"

int main(){
    srand(time(NULL));
    //aspetta(1);
    //printf("0");
    infrastruttura system = get_random_system();
    //printf("1");
    simulate(system);
    return 0;
}
