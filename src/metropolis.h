#ifndef METROPOLIS_H
#define METROPOLIS_H
int metropolis(int *lattice, int n, float T, float J, float B, float *p_e, int *p_m);
int pick_site(int *lattice, int n);
int flip(int *lattice, int n, float T, int idx, float J, float B, float *p_e, int *p_m);
float energia(int *lattice, int n, float J, float B);
float delta_energia(int *lattice, int n, float J, float B, int idx);
int magnetizacion(int *lattice, int n);
void guardar_resultados(float *datos, int n, char nombre[50]);
#endif
