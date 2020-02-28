#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM 20
int sum; /* this data is shared by the thread(s) */
int arr[NUM] = {7, 11,19,20,4, 3, 2, 5, 6, 8, 25, 31, 15, 4, 9, 1, 10, 78, 23,1000};
struct parameters
{
    int start; //start row
    int end;   //start column
};
void *merge_sort(struct parameters *params)
{
    printf("start=%d\n", params->start);
    printf("end=%d\n", params->end);
    for (int i = params->end-1; i >= params->start; i--)
    {
        for (int j = params->start+1; j <= i; j++)
        {
            if (arr[j - 1] > arr[j])
            {
                //printf("%d, %d\n", arr[j-1], arr[j]);
                int temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void *merge();


int main(int argc, char *argv[])
{
    pthread_t tid_arr[3];       /* the thread identifier */
    pthread_attr_t attr_arr[3]; /* set of thread attributes */
    struct parameters params;
    //First mergeSort
    params.start = 0;
    params.end = (NUM / 2);
    pthread_attr_init(&attr_arr[0]);
    pthread_create(&tid_arr[0], &attr_arr[0], merge_sort, &params);
    pthread_join(tid_arr[0], NULL);
    //printf("end =%d", params.end);
     for(int i=params.start;i<params.end;i++){
        printf("%d, ", arr[i]);
    }
    //First mergeSort
    params.start = (NUM / 2);
    params.end = NUM;
    pthread_attr_init(&attr_arr[1]);
    pthread_create(&tid_arr[1], &attr_arr[1], merge_sort, &params);
    pthread_join(tid_arr[1], NULL);
    //printf("start=%d, ", arr[params.start]);
   

    //Merge
    params.start = 0;
    params.end = NUM;
    pthread_attr_init(&attr_arr[2]);
    pthread_create(&tid_arr[2], &attr_arr[2], merge, NULL);
    pthread_join(tid_arr[2], NULL);
    for(int i=params.start;i<params.end;i++){
        printf("%d, ", arr[i]);
    }
    return 0;
}
/* The thread will begin control in this function */

void *merge()
{
    int i, j, k;
    int l =0;
    int m=NUM/2;
    int r=NUM; 
    int n1 =  m- l; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to 2 temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m +j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
}