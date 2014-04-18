#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "infrastruttura.h"
#include "utils.h"

int main(){
    printf("cazzo");
    aspetta(1);
    infrastruttura system = get_random_system();
    simulate(system);
    return 0;
}
