#include<stdio.h>
#include<stdlib.h>
#define HAVE_STRUCT_TIMESPEC
#include<pthread.h>
#include <time.h>

#define NUM_THREADS 4

int m=1000;
int n=1500;
int p=1500;
int q=1000;
int** first;
int** second;
int** result;

void* matrixmulti(void* arg)
{
    int thread_id=*(int*)arg;
    int block_size =m/NUM_THREADS;
    int start =thread_id*block_size;
    int end =(thread_id==NUM_THREADS-1)?m:(thread_id+1)*block_size;

    for (int c=start;c<end;c++) {
        for (int d=0;d<q;d++) {
            int tot=0;
            for (int k=0;k<p;k++) {
                tot=tot+first[c][k]*second[k][d];
            }
            result[c][d]=tot;
        }
    }

    pthread_exit(NULL);
}

int main(void)
{
    first=(int**)malloc(m*sizeof(int*));
    for (int i=0;i<m;i++)
        first[i]=(int*)malloc(n*sizeof(int));
    second=(int**)malloc(p * sizeof(int*));
    for (int i=0;i<p;i++)
        second[i]=(int*)malloc(q*sizeof(int));
    result=(int**)malloc(m*sizeof(int*));
    for (int i=0;i<m;i++)
        result[i]=(int*)malloc(q*sizeof(int));

    for (int c=0;c<m;c++) {
        for (int d=0;d<n;d++) {
            int a=rand()%101;
            first[c][d]=a;
        }
    }

    for (int c=0;c<p;c++) {
        for (int d=0;d<q;d++) {
            int a=rand()%101;
            second[c][d]=a;
        }
    }

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    clock_t start = clock();
    for (int i=0;i<NUM_THREADS;i++) {
        thread_ids[i]=i;
        pthread_create(&threads[i],NULL,matrixmulti,&thread_ids[i]);
    }

    for (int i=0;i<NUM_THREADS;i++) {
        pthread_join(threads[i],NULL);
    }
    clock_t end = clock();
    double elapsed_time=(double)(end - start)/CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", elapsed_time);
    return 0;
}
