#include "metropolis.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int metropolis(int *lattice, int n, float T, float J, float J2, float B, float *p_e, int *p_m)
{
    /* Realiza el algoritmo de metropolis para un estado de la red.
    Toma un sitio al azar, le cambia el spin calcula la diferencia
    de energia entre el estado anterior y el nuevo y acepta el cambio con
    probabilidad exp(-Delta_e/T) */
    int idx, acepta;
    idx = pick_site(lattice,n);
    acepta = flip(lattice, n, T, idx, J, J2, B, p_e, p_m);
    return acepta;
}

int pick_site(int *lattice, int n)
{
    /* Elige un sitio aleatorio de la red. */
    int site;
    site = ((double)rand()/(double)RAND_MAX) * n * n;
    return site;
}

int flip(int *lattice, int n, float T, int idx, float J, float J2, float B, float *p_e, int *p_m)
{
    /* Calcula el delta de energia del supuesto cambio y devuelve un 1
    si el cambio se acepta y un 0 si no se acepta. */
    float delta_e;

    delta_e = delta_energia(lattice,n,J,J2,B,idx);

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


float delta_energia(int *lattice, int n, float J, float J2, float B, int idx)
{
    /* Calcula la diferencia de energia que hay cuando se cambia el sentido
    del spin en la posicion idx. Para el caso ferro-antiferro. Donde los
    spines interactuan de forma ferromagnetica con sus primeros vecinos y
    antiferromagnetico con sus segundos vecinos (diagonales) */
    float delta_e;
    int i,j,N,E,S,W,NE,NW,SE,SW;

    // Indices (i,j) del idx
    i = idx/n;
    j = idx%n;

    // Primeros vecinos
    N = (i-1)*n+j;
    E = i*n+j+1;
    S = (i+1)*n+j;
    W = i*n+j-1;

    //Segundos vecinos
    NE = (i-1)*n+(j+1);
    NW = (i-1)*n+(j-1);
    SE = (i+1)*n+(j+1);
    SW = (i+1)*n+(j-1);

    // Condiciones periodicas de contorno
    if(i==n-1){
        S = j;
        SE = (j+1);
        SW = (j-1);}
    if(j==n-1){
        E = i*n;
        NE = (i-1)*n;
        SE = (i+1)*n;}
    if(i==0){
        N = (n-1)*n+j;
        NE = (n-1)*n+(j+1);
        NW = (n-1)*n+(j-1);}
    if(j==0){
        W = i*n + (n-1);
        NW = (i-1)*n+(n-1);
        SW = (i+1)*n+(n-1);}

    // Contribucion primeros vecinos
    delta_e = 2*J*lattice[idx]*(lattice[N]+lattice[E]+lattice[S]+lattice[W])+2*B*lattice[idx];

    // Contribucion segundos vecinos
    delta_e += 2*J2*lattice[idx]*(lattice[NE]+lattice[NW]+lattice[SE]+lattice[SW]);

    return delta_e;
}

float energia(int *lattice, int n, float J, float J2, float B)
{
    /* Calcula la energia total de la red. Tiene en cuenta los primeros
    y segundos vecinos.*/
    int i,j;
    int N,E,W,S,NE,NW,SE,SW;
    float E_J, E_J2, E_B, E_total;
    E_J = 0.0;
    E_J2 = 0.0;
    E_B = 0.0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            // Primeros vecinos
            N = (i-1)*n+j;
            E = i*n+j+1;
            S = (i+1)*n+j;
            W = i*n+j-1;

            // Segundos vecinos
            NE = (i-1)*n+(j+1);
            NW = (i-1)*n+(j-1);
            SE = (i+1)*n+(j+1);
            SW = (i+1)*n+(j-1);

            // Condiciones periodicas de contorno
            if(i==n-1){
                S = j;
                SE = (j+1);
                SW = (j-1);}
            if(j==n-1){
                E = i*n;
                NE = (i-1)*n;
                SE = (i+1)*n;}
            if(i==0){
                N = (n-1)*n+j;
                NE = (n-1)*n+(j+1);
                NW = (n-1)*n+(j-1);}
            if(j==0){
                W = i*n + (n-1);
                NW = (i-1)*n+(n-1);
                SW = (i+1)*n+(n-1);}

            // Casos especiales para las esquinas
            if(i==0 & j==0)
                NW = (n-1)*n+(n-1);
            if(i==0 & j==n-1)
                NE = (n-1)*n;
            if(i==n-1 & j==0)
                SW = (n-1);
            if(i==n-1 & j==n-1)
                SE = 0;

            E_J += lattice[i*n+j]*(lattice[E] + lattice[S]);
            E_J2 += lattice[i*n+j]*(lattice[SE] + lattice[SW]);
            E_B += lattice[i*n+j];

            //printf("%f\n", E_J2);
        }
    }
    printf("%f\n", E_J);
    printf("%f\n", E_J2);
    printf("%f\n\n", E_B);
    E_total = -J*E_J - J2*E_J2 - B*E_B;
    printf("%f\n\n", E_total);
    return E_total;
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
