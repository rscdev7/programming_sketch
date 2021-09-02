#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define LEN 10
#define SEED 20

void print (int* v, int start, int len) {
        printf ("[ ");

        for (int i=start;i<len;i++) {
                if (i==len-1) {
                        printf ("%d",v[i]);
                }else{
                        printf ("%d , ",v[i]);

                }
        }

        printf (" ] ");
}

int partition (int* v, int start, int end) {
        int pivot = v[end];
        int i = start-1;
        int tmp=0;

        for (int j=start;j< end;j++) {
                if (v[j] <= pivot) {
                        i=i+1;
                        tmp=v[i];
                        v[i]=v[j];
                        v[j]=tmp;
                }
        }
        tmp=v[i+1];
        v[i+1]=v[end];
        v[end]=tmp;

        return i+1;
}



void quick_sort (int* v, int start, int end) {
        if (start<end) {
                int splitter = partition (v,start,end);
                quick_sort(v,start,splitter-1);
                quick_sort(v,splitter+1,end);
        }
}

void init (int* v, int len) {
        srand (SEED);
        for (int i=0;i<len;i++) {
                v[i]=(int)(rand()%10000+1);
        }
}

void verify (int* v) {
        for (int i=0;i<LEN-1;i++) {
                if (v[i]>v[i+1]) {
                        printf ("Mismatch [i = %d] e [j = %d] <---> %d > di %d \n",i,i+1,v[i],v[i+1]);
                        break;
                }
        }
        printf ("OK \n");
}

int main () {

        int* v;
        v=malloc (LEN*sizeof(int));

        init (v,LEN);
        quick_sort(v,0,LEN-1);
        verify (v);

}
