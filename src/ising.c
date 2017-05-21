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
    int j;
    int nT = 100;
    int start = 5;
    int stop = 0.1;
    float *T = malloc(nT*sizeof(float)); // Temperatura
    for(j=0;j<nT;j++) T[j] = start + (stop-start)*((float)j/nT);

    float J = 1; // J de la energia
    float B = 0.0; // Campo magnetico
    int nterm = 5000; // Nr de pasos para la pre-termalizacion
    int niter = 50000; // Nr de iteraciones
    int delta_mag; //Cambio de magnetizacion en cada iteracion
    float *ene = malloc(nT*sizeof(float)); //Va guardando energia
    float *mag = malloc(nT*sizeof(float)); //Va guardando magnetizacion
    char nombre[50];

    srand(time(NULL));
    fill_lattice(lattice, n, prob);
    //print_lattice(lattice, n);

    float e = energia(lattice,n,J,B);
    int m = magnetizacion(lattice,n);

    float e_avg; //Energia promedio de todos los niter pasos en cada T
    float m_avg; //Magnetizacion promedio de todos los niter pasos en cada T

    // pre-termalizacion
    for(j=0;j<nterm;j++)
    {
        metropolis(lattice,n,T[0],J,B,&e,&m);
    }

    for(j=0; j<nT; j++)
    {
        e_avg = 0;
        m_avg = 0;
        for (int i = 0; i < niter; i++)
        {
            metropolis(lattice, n, T[j], J, B, &e, &m);
            e_avg += e;
            m_avg += m;
        }
        ene[j] = e_avg/niter;
        mag[j] = m_avg/niter;
    }

    print_lattice(lattice, n);

    sprintf(nombre, "tp2_energia_%d.txt", niter);
    guardar_resultados(ene,nT,nombre);

    sprintf(nombre, "tp2_temp.txt");
    guardar_resultados(T,nT,nombre);


    free(lattice);
    free(ene);
    free(mag);

    return 0;
}
