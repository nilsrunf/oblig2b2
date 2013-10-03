using namespace std;

#include <iostream>
#include <armadillo>
#include <stdio.h>
#include <time.h>
#include "lib.h"
using namespace arma;

int main(int argc, char** argv)
  {
    int N = 1000;
    int i, j;
    double rho_min = 0.0, rho_max = 2.0;
    double **A, ** Z, *d, *rho, *e, h = (rho_max-rho_min)/N;
    clock_t t;
    mat B(N, N); // generate a symmetric matrix
    vec eigval;
    mat eigvec;
    d = new double[N];
    e = new double[N];
    rho = new double[N];


    for(i = 0; i < N; i++)
           rho[i] = i*h;

    A = (double **) matrix(N, N, sizeof(double));
    Z = (double **) matrix(N, N, sizeof(double));

    // Initialize tridiagonal array
    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            if(i == j)
            {
                A[i][j] = 2.0/(h*h) + rho[i]*rho[i];
                d[i] = A[i][j];
                B(i, j) = d[i];
                Z[i][j] = d[i];
            }
            else if((j-1 == i) || (i-1 == j) )
                {
                   A[i][j] = -1.0/(h*h);
                   e[i] = A[i][j];
                   B(i, j) = e[i];
                }
                else
            {
                A[i][j] = 0.0; Z[i][j] = 0.0;  B(i, j) = 0.0;
            }

    t = clock();
   // eig_sym(eigval, eigvec, B);        // use standard algorithm by default
    tqli(d, e, N, Z);
    t = clock() -t;

    fprintf(stdout, "Execution time %.5f for N=%d\n", (float) t/CLOCKS_PER_SEC, N);

    for(i = 1; i < N; i++)
        fprintf(stdout," %f\n", eigval[i]);

    delete [] d;
    delete [] e;
    free_matrix((void **) A);
    free_matrix((void **) Z);

    return 0;

}
