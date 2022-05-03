#include <stdio.h>
#include <stdlib.h>

#define true 1==1
#define false 1!=1
#define T int

typedef int boolean;
typedef int K;
typedef int htIndex;


typedef struct Node{
    int dat;
    struct Node* next;
}Node;

typedef struct{
    Node *head;
    int size;
}List;

void init(List* lst){
    lst->head;
    lst->size = 0;
}

void ins(List* lst, int data){
    Node *new = (Node*) malloc(sizeof(Node));
    new->dat;
    new->next = NULL;

    Node *current = lst->head;
    if(current == NULL){
        lst->head = new;
        lst->size++;
        return;
    }else{
        while(current->next != NULL){
            current = current->next;
        }
        current->next = new;
        lst->size++;
    }
}


int htSize;

htIndex hash(T data ){

    return data % htSize;
}

boolean insertNode(Node **table, K data){
    Node *p, *p0;

    htIndex bucket = hash(data);
    p = (Node*) malloc(sizeof(Node));
    if(p == NULL){
        printf("Out of memory! \n");
        return false;
    }

    p0 = table[bucket];
    table[bucket] = p;
    p->next = p0;
    p->dat = data;
    return true;
}

Node* findNode(Node** table, K data){
    Node* p = table[hash(data)];
    while(p && !(p->dat == data))
        p = p->next;
    return p;
}

void printTable(Node** table,int size){
    Node *p;
    for(int i = 0; i < size;++i){
        p = table[i];
        while(p){
            printf("%5d", p->dat);
            p = p->next;
        }
        printf("\n");
    }
    printf("\n");
}

void fillRandom(int* arr, int len,int border){
    for(int i = 0;i < len; ++i){
        *(arr+i) =  rand()%border;
    }
}

int fillChar(){
    int sum = 0;
    char str[100] = "My program";
    char arr[100] = { 'M','y',' ','p','r','o','g','r','a','m' };
    for(int i = 0; i < 100; ++i){
        sum = sum + str[i];
    }

   // printf("%d \n", sum);
    return sum;
}


void coins(){
    int mas[6] = {1,2,5,10,50}, x = 98,i = 4, temp;
    while(x > 0){
        if( x >= mas[i]){
            temp = 0;
            while(x >= mas[i]){
                temp++;
                x -= mas[i];
            }
            printf("Coins = %d \n", mas[i]);
            printf("Number = %d \n", temp);
        }
        i--;
    }
    return 0;

}


int main()
{

    htSize = 16;
    int* arr;
    const int SZ = 20;
    arr = (int*) malloc(sizeof(int)*SZ);
    fillRandom(arr, SZ,100);

    Node** hashTable = (Node**) calloc(htSize, sizeof(Node));
    /*
    for(int i = 0; i < SZ; ++i){
       insertNode(hashTable, arr[i]);
    }
    */
    insertNode(hashTable, fillChar());
    printTable(hashTable,htSize);
    printf("================== \n");
    coins();
    return 0;

}
