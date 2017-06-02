#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "math.h"

#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv)
{
    int n = 32; //Tamano de red
    int *lattice = malloc(n * n * sizeof(int));
    float prob = 0.5; // Probabilidad inicial de llenado
    int i,j,k,l;
    int nT = 260;
    int start = 5;
    int fino1 = 3;
    int fino2 = 2;
    int stop = 0.1;
    float *T = malloc(nT*sizeof(float)); // Temperatura
    for(j=0;j<80;j++) T[j] = start + (fino1-start)*((float)j/80);
    for(j=80;j<180;j++) T[j] = fino1 + (fino2-fino1)*(((float)j-80)/100);
    for(j=180;j<nT;j++) T[j] = fino2 + (stop-fino2)*(((float)j-180)/80);

    int t_corr = 5000;

    float J = 1; // J de la energia
    float J2 = -1; // J para los segundos vecinos
    float B = 0; // Campo magnetico
    int nterm = 10000; // Nr de pasos para la pre-termalizacion
    int niter = 5000000; // Nr de iteraciones
    int delta_mag; //Cambio de magnetizacion en cada iteracion
    float *ene = malloc(nT*sizeof(float)); //Energia media vs T
    float *mag = malloc(nT*sizeof(float)); //Magnetizacion media vs T
    float *e_iter = malloc((niter/t_corr)*sizeof(float)); //Energia en todos los niter
    float *m_iter = malloc((niter/t_corr)*sizeof(float)); //Magnet en todos los niter
    float *var_e = malloc(nT*sizeof(float)); //Variacion de la energia
    float *var_m = malloc(nT*sizeof(float)); //Variacion de la magnetizacion

    char nombre[50];

    srand(time(NULL));
    fill_lattice(lattice, n, prob);
    //print_lattice(lattice, n);

    float e = energia(lattice,n,J,B);
    int m = magnetizacion(lattice,n);

    float e_avg; //Energia promedio de todos los niter pasos en cada T
    float m_avg; //Magnetizacion promedio de todos los niter pasos en cada T
    float e_2_avg;
    float m_2_avg;
    float vme_k;

    // Pre-termalizacion
    for(j=0;j<nterm;j++)
    {
        metropolis(lattice,n,T[0],J,J2,B,&e,&m);
    }

    for(j=0; j<nT; j++)
    {
        e_avg = 0;
        m_avg = 0;
        for (i = 0; i < niter; i++)
        {
            metropolis(lattice, n, T[j], J, J2, B, &e, &m);
            // Solo guardo resultados cada t_corr pasos
            if(i%t_corr == 0)
            {
                e_iter[i/t_corr] = e;
                m_iter[i/t_corr] = m;
                e_avg += e;
                m_avg += m;
            }
        }
        e_avg /= (niter/t_corr); //Valor medio de energia
        m_avg /= (niter/t_corr); //Valor medio de magnetizacion

        ene[j] = e_avg/n/n;
        mag[j] = m_avg/n/n;

        // Variacion
        var_e[j]=0;
        for(i=0;i<(niter/t_corr);i++)
        {
            var_e[j] += (e_iter[i] - e_avg)*(e_iter[i] - e_avg);
            var_m[j] += (m_iter[i] - m_avg)*(m_iter[i] - m_avg);
        }
        var_e[j] = sqrt(var_e[j]/(niter/t_corr))/n/n;
        var_m[j] = sqrt(var_m[j]/(niter/t_corr))/n/n;

    }

    print_lattice(lattice, n);


    sprintf(nombre, "tp2_energia_aferro.txt");
    guardar_resultados(ene,nT,nombre);

    sprintf(nombre, "tp2_varene_aferro.txt");
    guardar_resultados(var_e,nT,nombre);

    sprintf(nombre, "tp2_mag_aferro.txt");
    guardar_resultados(mag,nT,nombre);

    sprintf(nombre, "tp2_varmag_aferro.txt");
    guardar_resultados(var_m,nT,nombre);

    sprintf(nombre, "tp2_temp_%d.txt", nT);
    guardar_resultados(T,nT,nombre);

    /*
    sprintf(nombre, "tp2_mag_t237.txt");
    guardar_resultados(m_iter,niter/t_corr,nombre);
    */
    free(lattice);
    free(ene);
    free(mag);
    free(T);
    free(var_e);
    free(var_m);
    free(e_iter);
    free(m_iter);

    return 0;
}
