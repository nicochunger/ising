#include "metropolis.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int metropolis(int *lattice, int n, float T)
{
    /* Realiza el algoritmo de metropolis para un estado de la red.
    Toma un sitio al azar, le cambia el spin calcula la diferencia
    de energia entre el estado anterior y el nuevo y acepta el cambio con
    probabilidad exp(-Delta_e/T) */
    int idx, acepta;
    idx = pick_site(lattice,n);
    acepta = flip(lattice, n, T, idx);
    return acepta;
}

int pick_site(int *lattice, int n)
{
    /* Elige un sitio aleatorio de la red. */
    int site;
    site = ((double)rand()/(double)RAND_MAX) * n * n;
    return site;
}

int flip(int *lattice, int n, float T, int idx)
{
    /* Calcula el delta de energia del supuesto cambio y devuelve un 1
    si el cambio se acepta y un 0 si no se acepta. */
    int delta_e;
    int i,j,N,E,S,W;

    // Indices (i,j) del idx
    i = idx/n;
    j = idx%n;

    // Vecinos
    N = (i-1)*n+j;
    E = i*n+j+1;
    S = (i+1)*n+j;
    W = i*n+j-1;
    if(i==n-1) S = j;
    if(j==n-1) E = i*n;
    if(i==0) N = (n-1)*n+j;
    if(j==0) W = i*n + (n-1);

    delta_e = 2*lattice[idx]*(lattice[N]+lattice[E]+lattice[S]+lattice[W]);
    //printf("%d\n", delta_e);

    if(delta_e <= 0){ // Si la diferencia de energia es menor a 0, se acepta
        lattice[idx] *= -1;
        return 1;}
    else if((float)rand()<exp(-(float)delta_e/T)*RAND_MAX){
        lattice[idx] *= -1;
        return 1;}
    else return 0;
}

float energia(int *lattice, int n, float J, float B)
{
    int i,j,E;
    float E_B
    E = 0;
    E_B = 0.0;
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
    for(i=0;i<n*n;i++)
        E_B += lattice[i];
    E_B *= B;
    return -J*E-E_B;
}
