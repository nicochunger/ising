#include "metropolis.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define e 2.71828           // Constante matematica e

int metropolis(int *lattice, int n, float T)
{
    /* Realiza el algoritmo de metropolis para un estado de la red.
    Toma un sitio al azar, le cambia el spin calcula la diferencia
    de energia entre el estado anterior y el nuevo y acepta el cambio con
    probabilidad exp(-Delta_e/T) */
    int idx, acepta;
    idx = pick_site(lattice,n);
    acepta = flip(lattice, n, T, idx);

    // Si acepta = 0, el cambio no se acepta.
    // Como el cambio ya se habia hecho, hay que volver a cambiarlo.
    // Si acepta = 1, no se hace nada porque el cambio ya estaba hecho.
    if(acepta==0)
        lattice[idx] *= -1;

    return 0;
}

int pick_site(int *lattice, int n)
{
    /* Elige un sitio aleatorio de la red. */
    int site;
    double rdom = ((double)rand()/(double)RAND_MAX);
    site = rdom * n * n;
    return site;
}

int flip(int *lattice, int n, float T, int idx)
{
    /* Calcula el delta de energia del supuesto cambio y devuelve un 1
    si el cambio se acepta y un 0 si no se acepta. */
    int en0, en1, delta_e;
    float probabilidad;
    en0 = energia(lattice,n);
    lattice[idx] *= -1;
    en1 = energia(lattice,n);
    delta_e = en1 - en0;

    probabilidad = pow(e,-delta_e/T);
    if(probabilidad > 1) // Si la probabilidad calculada es mayor a 1 se corta en 1
        probabilidad = 1;

    // El cambio se acepta con la probabilidad calculada
    double rdom = ((double)rand()/(double)RAND_MAX);
    if(rdom>probabilidad)
        return 0;
    else
        return 1;
}

int energia(int *lattice, int n)
{
    int i,j,E;
    E = 0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i==n-1 && j==n-1) //Esquina inferior derecha
                E += lattice[i*n+j]*lattice[i*n] + lattice[i*n+j]*lattice[j];
            else if(j==n-1) //Lado derecho
                E += lattice[i*n+j]*lattice[i*n] + lattice[i*n+j]*lattice[(i+1)*n+j];
            else if(i==n-1)
                E += lattice[i*n+j]*lattice[i*n+(j+1)] + lattice[i*n+j]*lattice[j];
            else //resto
                E += lattice[i*n+j]*lattice[i*n+(j+1)] + lattice[i*n+j]*lattice[(i+1)*n+j];
        }
    }
    return -E;
}
