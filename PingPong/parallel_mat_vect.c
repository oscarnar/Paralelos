#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void Read_matrix(float local_A[], int local_m, int n,
             int my_rank, int p, MPI_Comm comm);
void Read_vector(float local_x[], int local_n, int my_rank,
             int p, MPI_Comm comm);
void Parallel_matrix_vector_prod(float local_A[], int m, 
             int n, float local_x[], float global_x[], float local_y[],
             int local_m, int local_n, MPI_Comm comm);

int main(void) {
    int             my_rank;
    int             p;
    float*          local_A; 
    float*          global_x;
    float*          local_x;
    float*          local_y;
    int             m, n;
    int             local_m, local_n;
    MPI_Comm        comm;

    MPI_Init(NULL, NULL);
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &p);
    MPI_Comm_rank(comm, &my_rank);

    if (my_rank == 0) {
        printf("Ingresa el tamaño \n");
        scanf("%d", &m);
        n = m;
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, comm);
    MPI_Bcast(&n, 1, MPI_INT, 0, comm);

    local_m = m/p;
    local_n = n/p;

    local_A = malloc(local_m*n*sizeof(float));
    Read_matrix(local_A, local_m, n, my_rank, p, comm);

    local_x = malloc(local_n*sizeof(float));
    Read_vector(local_x, local_n, my_rank, p, comm);
    local_y = malloc(local_m*sizeof(float));
    global_x = malloc(n*sizeof(float));

    double start,finish;
    start = MPI_Wtime();
    Parallel_matrix_vector_prod(local_A, m, n, local_x, global_x, 
        local_y, local_m, local_n, comm);
    finish = MPI_Wtime();
    if (my_rank == 0) {
        finish = finish - start;
        printf("Tiempo %f segundos\n",finish);
    }

    free(local_A);
    free(local_x);
    free(local_y);
    free(global_x);

    MPI_Finalize();

    return 0;
}

void Read_matrix(
         float      local_A[] /* out */, 
         int        local_m   /* in  */, 
         int        n         /* in  */,
         int        my_rank   /* in  */, 
         int        p         /* in  */,
         MPI_Comm   comm      /* in  */) {

    int     i, j;
    float*  temp;


    if (my_rank == 0) {
        temp = (float*) malloc(local_m*p*n*sizeof(float));
        for (i = 0; i < p*local_m; i++) 
            for (j = 0; j < n; j++)
                temp[i*n+j] = i-j;
        MPI_Scatter(temp, local_m*n, MPI_FLOAT, local_A,
            local_m*n, MPI_FLOAT, 0, comm);
        free(temp);
    } else {
        MPI_Scatter(temp, local_m*n, MPI_FLOAT, local_A,
            local_m*n, MPI_FLOAT, 0, comm);
    }
} 

void Read_vector(
         float    local_x[]  /* out */, 
         int      local_n    /* in  */, 
         int      my_rank    /* in  */,
         int      p          /* in  */,
         MPI_Comm comm       /* in  */) {

    int    i;
    float* temp;

    if (my_rank == 0) {
        temp = malloc(local_n*p*sizeof(float));
        for (i = 0; i < p*local_n; i++) 
            temp[i] = 5;

        MPI_Scatter(temp, local_n, MPI_FLOAT, local_x, local_n, MPI_FLOAT,
            0, comm);
        free(temp);
    } else {
        MPI_Scatter(temp, local_n, MPI_FLOAT, local_x, local_n, MPI_FLOAT,
            0, comm);
    }

}  

void Parallel_matrix_vector_prod(
         float    local_A[]   /* in  */,
         int      m           /* in  */,
         int      n           /* in  */,
         float    local_x[]   /* in  */,
         float    global_x[]  /* in  */,
         float    local_y[]   /* out */,
         int      local_m     /* in  */,
         int      local_n     /* in  */,
         MPI_Comm comm        /* in  */) {

    /* local_m = m/p, local_n = n/p */

    int local_i, j;

    MPI_Allgather(local_x, local_n, MPI_FLOAT,
                   global_x, local_n, MPI_FLOAT,
                   comm);
    for (local_i = 0; local_i < local_m; local_i++) {
        local_y[local_i] = 0.0;
        for (j = 0; j < n; j++)
            local_y[local_i] += local_A[local_i*n+j]*global_x[j];
    }
}  /* Parallel_matrix_vector_prod */
