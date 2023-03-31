#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(void)
{
    int c, d, p, q, m, n, k, a, tot, num = 0;
    double start_time, end_time;
    srand(time(NULL));
    m = 1000;
    n = 1500;
    p = 1500;
    q = 1000;
    int** first=(int**)malloc(m*sizeof(int*));
    for (int i=0;i<m;i++)
        first[i]=(int*)malloc(n*sizeof(int));
    int** second=(int**)malloc(p*sizeof(int*));
    for (int i=0;i<p;i++)
        second[i]=(int*)malloc(q*sizeof(int));
    int** result=(int**)malloc(m*sizeof(int*));
    for (int i=0;i<m;i++)
        result[i]=(int*)malloc(q*sizeof(int));

    for (c=0;c<m;c++) {
        for (d=0;d<n;d++) {
            a=rand()%101;
            first[c][d]=a;
        }
    }

    for (c=0;c<p;c++) {
        for (d=0;d<q;d++) {
            a=rand()%101;
            second[c][d]=a;   
        }
    }
    printf("Computing...\n");
    start_time=omp_get_wtime();
    omp_set_num_threads(4);
#pragma omp parallel for private(c,d,k)
    for (c=0;c<m;c++) {
        for (d=0;d<q;d++) {
            for (k=0;k<p;k++) {
                tot = tot+first[c][k]*second[k][d];
            }
            result[c][d] = tot;
            tot = 0;
        }
    }
    end_time=omp_get_wtime();
    printf("Time taken: %f seconds\n", end_time - start_time);
    return 0;
}
