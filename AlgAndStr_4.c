#include <stdio.h>
#include <stdlib.h>


#define true 1 == 1
#define false 1 != 1
#define SZ 1000
#define size 10
#define T int

typedef int boolean;

int cursor = -1;
T Stack[SZ];


boolean push(T data){
    int v = 1024;
     for(int i = 1; i <=16 ; i++)
     {
             if(data >= v)
             {
                    printf("1");
                    data -= v;
             }
             else
                 printf("0");
             v /= 2;
     }
     printf(" ");
    if(cursor < SZ){
        Stack[++cursor] = data;
        return true;
    }else{
        printf("%s \n","Stack overflow");
        return false;
    }

}

T pop(){
    if(cursor != -1){
        return Stack[cursor--];
    }else{
        printf("%s \n", "Stack empty");
        return -1;
    }
}

typedef struct{
    int pr;
    int dat;
}
Node;

Node* arr[size];
int head;
int tail;
int items;

void init(){
    for(int i = 0; i < size;++i){
        arr[i] = NULL;
    }
    head = 0;
    tail = 0;
    items = 0;

}

void ins(int pr, int dat){
    Node *node = (Node*) malloc(sizeof(Node));
    node->dat = dat;
    node->pr = pr;
    int flag;
    if(items == 0){
        arr[tail++] = node;
        items++;
    } else if(items == size){
        printf("%s \n", "Queue is full");
        return;
    } else{
        int i = 0;
        int idx =0;
        Node *tmp;
        for(i = head; i < tail; ++i){
            idx = i % size;
            if(arr[idx]->pr > pr)
                break;
            else
                idx++;
        }
        flag = idx % size;
        i++;
        while(i <= tail){
            idx = i % size;
            tmp = arr[idx];
            arr[idx] = arr[flag];
            arr[flag] = tmp;
            i++;
        }
        arr[flag] = node;
        items++;
        tail++;
    }
}

Node* rem(){
    if(items == 0){
        return NULL;
    }else{
        int idx = head++ % size;
        Node *tmp = arr[idx];
        arr[idx] = NULL;
        items--;
        return tmp;
    }
}

void printQueue(){
    printf("[");
    for(int i = 0; i < size;++i){
        if(arr[i] == NULL)
            printf("[*, *]" );
            else
                printf("[%d, %d]",arr[i]->pr,arr[i]->dat);
    }
    printf("]\n");
}


int main()
{
    init();
    ins(1, 11);
    ins(2, 12);
    ins(3, 13);
    ins(4, 14);
    ins(5, 15);
    ins(6, 16);
    ins(7, 17);
    ins(8, 18);
    ins(9, 19);
    ins(10, 20);
    printQueue();
    for(int i = 0; i < 7; ++i){
        Node* n = rem();
        printf("pr=%d, dat=%d \n", n->pr, n->dat);
    }
    printQueue();

    ins(1,200);
    ins(5, 9);
    ins(3,7);
    printQueue();
    printf("======================\n");
    push(1000);
    push(1100);
    push(900);
    push(800);
    push(1000);
    push(950);

    return 0;
}
