#include <stdio.h>

unsigned int vecinos(unsigned char *a, unsigned int i, unsigned int j, unsigned int M, unsigned int N){
    unsigned int n, x, y, index;
    int k, l;
    n = 0;
    for (k = -1; k <= 1; k++){
        for (l = -1; l <= 1; l++){
            if ((k == 0) && (l == 0))
                continue;
            x = (M+i+k) % M;
            y = (N+j+l) % N;
            index = N*x+y;
            if (a[index] == 1)
                n++;
        }
    }
    return n;
}
