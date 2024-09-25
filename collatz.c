#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[]) {

    srand(time(0));                     // seed, so that we get a dif # each time

    if(argc < 4) {                      // make sure 3 values are passed
        printf("invalid.");
        return 1;
    }

    const int N = atoi(argv[1]);        // # of times to run
    const int MIN = atoi(argv[2]);      // mininum for the random #
    const int MAX = atoi(argv[3]);      // maximun for the random #
    
    for(int ix = 0; ix < N; ix++) {     // run function N # of times

        unsigned long long steps = 0;
        unsigned long long random = (rand() % (MAX - MIN + 1)) + MIN;  // generate random # within range

        if(random <= 0) {
            printf("invalid range: no negtive numbers");
            return 1;
        }

        printf("random number: %llu\n", random);

//--------- core function: collatz conjecture ---------
        while(random != 1) {
            if(random % 2 == 1) 
                random = 3 * random + 1;
            else 
                random /= 2;
            steps++;
        }
//------------------------------------------------------

        printf("steps it took: %llu\n\n", steps);
    }

    return 0;
}
