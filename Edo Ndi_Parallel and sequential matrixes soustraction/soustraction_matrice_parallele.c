#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
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
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Status status;
    NRPE = ms / p;
    if(rank == 0)
    {
        printf("\n Matrice 1 : \n");
       

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
    }
    for(i=0; i<ms; i++)
    {
        MPI_Bcast(M_b[i], ms*ms, MPI_INT, 0, MPI_COMM_WORLD);
    }
    printf("\n Matrice 2 - Processus %d\n",rank);
    for(x=0; x<ms; ++x)
    {
        for(c=0; c<ms; ++c)
            printf("%5d",M_b[x][c]);
        printf("\n");
    }
    for(i=0; i<p; i++)
    {
        for(j=0; j<ms; j++)
        {
            MPI_Send(&M_a[j], ms*NRPE,MPI_INT,i,0,MPI_COMM_WORLD);
            NRPE++;
        }
    }
    MPI_Recv(M_a, ms*NRPE, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    //declaraton of the fontion time
    starttime = MPI_Wtime();
    for(k=0; k<ms; k++)
    for(i=0; i<ms; i++)
    	{
        M_c[k][i] = 0;
    
            M_c[k][i] = M_c[k][i] + M_a[k][i] - M_b[k][i];
        }
        endtime = MPI_Wtime();
    MPI_Send(&M_c[i][k], ms*ms, MPI_INT, 0, 0, MPI_COMM_WORLD);
    if(rank == 0)
    {
 
        printf("\n Matrice 1 - Matrice 2:\n");
            for(i=0; i<ms; i++)
            {
            printf("\n");
            for(k=0; k<ms; k++)
                printf("%7d" , M_c[i][k]);
            }
            printf("\n\n Temps d'execution parallele: %f s\n", endtime-starttime);
    }
    printf("\n");
    MPI_Finalize();
    return 0;
}

