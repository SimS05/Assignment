#include<stdio.h>
#include<stdlib.h>
#include <time.h>

int main(void)
{
    int c, d, p, q, m, n, k, a, tot = 0;
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
    clock_t start = clock();
    for (c=0;c<m;c++) {
        for (d=0;d<q;d++) {
            for (k=0;k<p;k++) {
                tot=tot+first[c][k]*second[k][d];
            }
            result[c][d]=tot;
            tot=0;
        }
    }
    clock_t end=clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", elapsed_time);
    return 0;
}
