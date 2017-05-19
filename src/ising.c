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
    int niter = 200; // Nr de iteraciones
    int delta_mag; //Cambio de magnetizacion en cada iteracion
    float *ene = malloc((niter+1)*sizeof(float)); //Va guardando energia
    int *mag = malloc((niter+1)*sizeof(int)); //Va guardando magnetizacion
    srand(time(NULL));
    fill_lattice(lattice, n, prob);
    print_lattice(lattice, n);
    ene[0] = energia(lattice,n,J,B);
    mag[0] = magnetizacion(lattice,n);

    for (int i = 0; i < niter; i++)
    {
        delta_mag = metropolis(lattice, n, T, J, B);
        if(delta_mag == 0) mag[i+1] = mag[i];
        else mag[i+1] = mag[i] + 2*(delta_mag/abs(delta_mag));

        if(abs(delta_mag == n*n))
            ene[i+1] = ene[i] + delta_energia(lattice,n,J,B,0);
        else ene[i+1] = ene[i] + delta_energia(lattice,n,J,B,abs(delta_mag));
        printf("%d\t%f\n", mag[i], ene[i]);
    }

    print_lattice(lattice, n);

    free(lattice);
    free(ene);
    free(mag);

    return 0;
}
