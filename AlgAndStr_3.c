#include <stdio.h>
#include <stdlib.h>

void fillRandomArr(int*arr,const int size, int sim){
    for(int j=0;j<=size;++j){
        arr[j]=rand()%sim;
    }


}

void printArr(int*arr,const int size,  int sim){
    for(int j=0;j<size;++j){
        printf("%4d",arr[j]);
    }
    printf("\n");
}

void qSort(int*array, int left, int right){
    int pivot;
    int l_hold = left;
    int r_hold = right;
    pivot = array[left];
    while(left < right){
        while((array[right]>=pivot) && (left < right)){
            right--;
        }
        if(left != right){
            array[left]=array[right];
            left++;
        }
        while((array[left] <= pivot) && (left < right)){
            left++;
        }
        if(left != right){
            array[right] = array[left];
            right--;
        }
    }
    array[left] = pivot;
    pivot = left;
    left = l_hold;
    right = r_hold;
    if(left < pivot){
        qSort(array,left,pivot - 1);
    }
    if (right > pivot){
        qSort(array, pivot + 1, right);
    }
}

void blockSort(int*arr,int len){
    const int max = len;
    const int b = 10;
    int block[b][max+1];
    for(int i=0; i<b;++i){
        block[i][max] = 0;
    }
    for(int digit = 1;digit < 1000000000; digit *= 10){
        for(int i=0; i < max; ++i){
            if(arr[i]%2==0){
            int d = (arr[i]/digit) % b;
            block[d][block[d][max]++] = arr[i];
            arr[i] = -1;
            }
        }
        int idx = 0;
        for(int i=0; i < b; ++i){
            for(int j = 0; j < block[i][max];++j){
                while(arr[idx] != -1){
                    idx++;
                }
                arr[idx++] = block[i][j];
            }
            block[i][max] = 0;
        }
    }
}

int main()
{


    const int size=20;
    int arr[size];
    fillRandomArr(arr,size,20);
    printArr(arr,size,3);
    qSort(arr,0,size-1);
    printArr(arr,size,3);
    printf("===================\n");
    fillRandomArr(arr,size,100);
    printArr(arr,size,3);
    blockSort(arr,size);
    printArr(arr,size,3);
    return 0;

}
