#include "stdlib.h"
#include "stdio.h"
#include "time.h"

#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv)
{
    int n = 30; //Tamano de red
    int *lattice = malloc(n * n * sizeof(int));
    float prob = 0.5; // Probabilidad inicial de llenado
    float T = 1; // Temperatura
    float J = 1.0; // J de la energia
    float B = 0.0; // Campo magnetico
    int nterm = 1000; // Nr de pasos para la pre-termalizacion
    int niter = 1000; // Nr de iteraciones
    int delta_mag; //Cambio de magnetizacion en cada iteracion
    float *energia = malloc((niter+1)*sizeof(float));
    int *magnetizacion = malloc((niter+1)*sizeof(int));
    srand(time(NULL));
    fill_lattice(lattice, n, prob);
    print_lattice(lattice, n);
    energia[0] = energia(lattice,n,J,B);
    magnetizacion[0] = magnetizacion(lattice,n);

    for (int i = 0; i < niter; i++)
    {
        delta_mag = metropolis(lattice, n, T);
        magnetizacion[i+1] = magnetizacion[i] + 2*delta_mag;
        
    }

    print_lattice(lattice, n);

    free(lattice);
    free(energia);
    free(magnetizacion);

    return 0;
}
