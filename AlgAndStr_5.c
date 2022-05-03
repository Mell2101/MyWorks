#include <stdio.h>
#include <string.h>

typedef struct Node{
    int dat;
    struct Node *next;
}Node;

typedef struct{
    Node *head;
    int size;
}List;

void init(List* lst){
    lst->head = NULL;
    lst->size = 0;
}

void ins(List *lst, int data){
    Node *new = (Node*) malloc(sizeof(Node));
    new->dat = data;
    new->next = NULL;

    Node *current = lst->head;
    if(current == NULL){
        lst->head;
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

Node* rm(List *lst, int data){
    Node *current = lst->head;
    Node *parent = NULL;
    if(current == NULL)
        return NULL;
    while(current->next != NULL && current->dat != data){
        parent = current;
        current = current->next;
    }
    if(current->dat != data){
        return NULL;
    }
    if(current == lst->head){
        lst->head = current->next;
        lst->size--;
        return current;
    }
    parent->next = current->next;
    lst->size--;
    return current;
}

void printNode(Node *n){
    if(n == NULL){
        printf("[]");
        return;
    }
    printf("[%d]", n->dat);
}

void printList(List *lst){
    Node *current = lst->head;
    if(current == NULL){
        printNode(current);
    }else{
       do{
            printNode(current);
            current = current->next;
        }while(current != NULL);
    }
    printf(" Size: %d \n", lst->size);
}



int isBalance(const char* s){
    int i, ds[3];
    const char* p;
    const char beg[]="({[";
    const char end[]=")}]";
    memset(ds, 0, sizeof(ds));
    for(;*s;++s){
        if((p = strchr(beg, *s)) != NULL)
            ++ds[p - beg];
            else if(( p = strchr(end, *s)) != NULL){
                if(--ds[p - end] < 0)
                    return 0;
            }
    }
    for(i = 0; i < 3; ++i){
        if(ds[i] > 0)
            return 0;
    }
    return 1;
}
int main()
{
    puts(isBalance(")(, ())({), (, ])}), [(])") ? "yes" : "error");
     puts(isBalance("(), ([])(), {}(), ([{}])") ? "yes" : "error");

    printf("===============\n");
    List *lst =(List*) malloc(sizeof(List));
    init(lst);
    printList(lst);
    ins(lst,1);
    printList(lst);
    ins(lst,55);
    printList(lst);
    return 0;

}
