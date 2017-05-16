#ifndef METROPOLIS_H
#define METROPOLIS_H
int metropolis(int *lattice, int n, float T);
int pick_site(int *lattice, int n);
int flip(int *lattice, int n, float T, int idx);
float energia(int *lattice, int n, float J, float B);
#endif
