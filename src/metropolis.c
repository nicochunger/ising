#include "metropolis.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int metropolis(int *lattice, int n, float T, float J, float B, float *p_e, int *p_m)
{
    /* Realiza el algoritmo de metropolis para un estado de la red.
    Toma un sitio al azar, le cambia el spin calcula la diferencia
    de energia entre el estado anterior y el nuevo y acepta el cambio con
    probabilidad exp(-Delta_e/T) */
    int idx, acepta;
    idx = pick_site(lattice,n);
    acepta = flip(lattice, n, T, idx, J, B, p_e, p_m);
    return acepta;
}

int pick_site(int *lattice, int n)
{
    /* Elige un sitio aleatorio de la red. */
    int site;
    site = ((double)rand()/(double)RAND_MAX) * n * n;
    return site;
}

int flip(int *lattice, int n, float T, int idx, float J, float B, float *p_e, int *p_m)
{
    /* Calcula el delta de energia del supuesto cambio y devuelve un 1
    si el cambio se acepta y un 0 si no se acepta. */
    float delta_e;

    delta_e = delta_energia(lattice,n,J,B,idx);

    if(delta_e <= 0) // Si la diferencia de energia es menor o igual a 0, se acepta
    {
        lattice[idx] *= -1;
        *p_m = *p_m + 2*lattice[idx];
        *p_e = *p_e + delta_e;
        return 1;
    }
    else if((float)rand()<exp(-(float)delta_e/T)*RAND_MAX)
    {
        lattice[idx] *= -1;
        *p_m = *p_m + 2*lattice[idx];
        *p_e = *p_e + delta_e;
        return 1;
    }
    else return 0;
}

float delta_energia(int *lattice, int n, float J, float B, int idx)
{
    /* Calcula la diferencia de energia que hay cuando se cambia el sentido
    del spin en la posicion idx. */
    float delta_e;
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

    delta_e = 2*J*lattice[idx]*(lattice[N]+lattice[E]+lattice[S]+lattice[W])+2*B*lattice[idx];
    return delta_e;
}

float energia(int *lattice, int n, float J, float B)
{
    /* Calcula la energia total de la red. */
    int i,j,E;
    float E_B;
    E = 0;
    E_B = 0.0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            E_B += lattice[i*n+j];
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
    E_B *= B;
    return -J*E-E_B;
}

int magnetizacion(int *lattice, int n)
{
    /* Calcula la magnetizacion total de la red */
    int i, M;
    M = 0;
    for(i=0;i<n*n;i++)
    {
        M += lattice[i];
    }
    return M;
}

void guardar_resultados(float *datos, int n, char nombre[50])
{
	/*
	Esta funcion toma un vector con datos y los guarda todos en un archivo de texto
	*/

	int i;
    char path[100];
    sprintf(path, "/home/nunger/Documents/ising/res/%s", nombre);

	FILE *fp; // Declaro el puntero que va a ir al archivo (FILE es un tipo)

	fp = fopen(path,"w"); // "r": read  "w": write   "a": append

	for(i=0;i<n;i++)
	{
		fprintf(fp,"%f\n",datos[i]); //Escribo todos los datos en una linea nueva
	}

	fclose(fp);
}
