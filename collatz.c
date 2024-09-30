// Author:  Angel Penaloza
// CWID:    884700303
// Assignment 4: (Big) Collatz Conjecture

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "cache.h"

//--------- core function: collatz conjecture ---------

unsigned long long collatz(unsigned long long num) {
    if(num == 1) return 0;
    unsigned long long steps = 0;
    while(num != 1) {
        if(num % 2 == 1)
            num = 3 * num + 1;
        else 
            num /= 2;
        steps++;
    }
    return steps;
}
//------------------------------------------------------


int main(int argc, char* argv[]) {

    srand(time(0));                     // seed, so that we get a dif # each time

    if(argc < 6) {                      // make sure 3 values are passed
        printf("invalid.");             // and add 2 for the cache method and size
        return 1;
    }

    const int   N           =   atoi(argv[1]);      // # of times to run
    const int   MIN         =   atoi(argv[2]);      // mininum for the random #
    const int   MAX         =   atoi(argv[3]);      // maximun for the random #
    char*       cache_pol   =   argv[4];            // cache policy
    int         cache_size  =   atoi(argv[5]);      // cache size

    int hash_size = 0;

    hash_table* ht;
    ht->size = 0;
    ht->head = NULL;
    ht->tail = NULL;

    for(int ix = 0; ix < N; ix++) {                 // run function N # of times

        unsigned long long steps = 0;
        unsigned long long random = (rand() % (MAX - MIN + 1)) + MIN;  // generate random # within range
        float cache_pol_hit_percent = 0.0;

        if(random <= 0) {       // make sure number is positive
            printf("invalid range: no negtive numbers");
            return 1;
        }

        if(strcmp(cache_pol, "LRU") != 0 && strcmp(cache_pol, "FIFO") != 0) {
            printf("invalid cache_pol type");
            return 1;
        }


        steps = locate(random, ht);

        if(steps == -1) {
            steps = collatz(random);
            insert(random, steps, ht, cache_size);
        }


        printf("random number: %llu\n", random);

        printf("steps it took: %llu\n\n", steps);
    }

    free_table(ht);

    return 0;
}

