#include "stdlib.h"
#include "stdio.h"
#include "time.h"

#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv)
{
    int n = 32; //Tamano de red
    int *lattice = malloc(n * n * sizeof(int));
    float prob = 0.5; // Probabilidad inicial de llenado
    float T = 1; // Temperatura
    float J = 1; // J de la energia
    float B = 0.0; // Campo magnetico
    int nterm = 2000; // Nr de pasos para la pre-termalizacion
    int niter = 50000; // Nr de iteraciones
    int delta_mag; //Cambio de magnetizacion en cada iteracion
    float *ene = malloc(niter*sizeof(float)); //Va guardando energia
    int *mag = malloc(niter*sizeof(int)); //Va guardando magnetizacion
    srand(time(NULL));
    fill_lattice(lattice, n, prob);
    print_lattice(lattice, n);
    float e = energia(lattice,n,J,B);
    int m = magnetizacion(lattice,n);

    for (int i = 0; i < niter; i++)
    {
        metropolis(lattice, n, T, J, B, &e, &m);
        ene[i] = e;
        mag[i] = m;
        if(i%100==0) printf("%d\t%f\n", mag[i], ene[i]);
    }

    print_lattice(lattice, n);

    free(lattice);
    free(ene);
    free(mag);

    return 0;
}
