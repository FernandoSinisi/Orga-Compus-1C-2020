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
            /*
            * Explicacion: uso (M+i+k) y (N+j+l) en vez de solo (i+k) y (j+l) porque la operacion
            * modulo de C funciona mal con numeros negativos (por ejemplo cuando tengo la posicion 
            * 0,0 y quiero revisar a la izquierda me queda -1,0). Por eso le sumo M y N respectivamente
            * asi no es negativo y el modulo da lo mismo. En stack overflow esta explicado por que el
            * modulo da mal con numeros negativos.
            */
            index = N*x+y;
            if (a[index] == 1)
                n++;
        }
    }
    return n;
}
