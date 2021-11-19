#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ms 4
int main(int argc, char* argv[])
{
    int i,j,k;
    int x,c;
    int M_a[ms][ms];
    int M_b[ms][ms];
    int M_c[ms][ms];
    int rank, p;
    int NRPE;
    double starttime, endtime;
    printf("\n Matrice 1: \n");
       

        for(i=0; i<ms; ++i)
            for(j=0; j<ms; ++j)
                M_a[i][j] =rand() % 10;
        for(i=0; i<ms; ++i)
        {
            for(j=0; j<ms; ++j)
                printf("%5d" , M_a[i][j]);
            printf("\n");
        }
        printf("\n Matrice 2:\n");
        
        for(x=0; x<ms; ++x)
            for(c=0; c<ms; ++c)
                M_b[x][c] = rand() % 10;
        for(x=0; x<ms; ++x)
        {
            for(c=0; c<ms; ++c)
                printf("%5d" , M_b[x][c]);
            printf("\n");
        }
    
    starttime = clock();
    for(k=0; k<ms; k++)
    for(i=0; i<ms; i++)
    	{
        M_c[k][i] = 0;
    
            M_c[k][i] = M_c[k][i] + M_a[k][i] - M_b[k][i];
        }
        endtime = clock();
    printf("\n Matrice 1 - Matrice 2:\n");
            for(i=0; i<ms; i++)
            {
            printf("\n");
            for(k=0; k<ms; k++)
                printf("%7d" , M_c[i][k]);
            }
            printf("\n\n Temps d'execution sequentielle: %f s\n", endtime-starttime);
    return 0;
    }
