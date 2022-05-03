#include <stdio.h>
#include <stdlib.h>


#define true 1 == 1
#define false 1 != 1
#define num 6
#define num1 100

typedef boolean;
int cursor = -1;


int mat1[num][num] = {
    {0, 1, 0, 0, 0, 0}, //0
    {0, 0, 1, 0, 0, 0}, //1
    {0, 0, 0, 1, 0, 0}, //2
    {0, 0, 0, 0, 1, 0}, //3
    {0, 0, 0, 0, 0, 1}, //4
    {1, 0, 0, 0, 0, 0}, //5
};



 int mat[num][num] = {
    {0, 1, 1, 0, 0, 0}, //0
    {0, 0, 0, 1, 1, 1}, //1
    {0, 0, 0, 0, 0, 1}, //2
    {1, 0, 0, 0, 0, 0}, //3
    {0, 1, 1, 0, 0, 0}, //4
    {0, 1, 1, 0, 1, 0}, //5
};

int visited[num] = {0};
int Stack[num1];


int used[num];



void dfs(int v){
    int i;
    used[v] = 1;
    printf("%d", v );
    for( i = 0; i < num; ++i){
        if( mat1[v][i] = 1 && !used[i])
            dfs(i);
    }
}



boolean push(int depthTravers){
    if(cursor < num1){
        Stack[++cursor] = depthTravers;
        return true;

    }else{
        printf("%d \n", " Stack is over");
        return -1;
    }

}

int pop(){
    if(cursor != -1){
        return Stack[cursor--];
    }else{
        printf("%d \n", "Stack is empty");
        return -1;
    }
}

int depthTravers(int st){
    int r;
    printf("%d ", st);
    visited[st] = 1;
    for(r = 0; r < num; ++r ){
        if(mat[st][r] == 1 && !visited[r]){
            if(cursor < num1){
            Stack[++cursor] = r;
            }
            depthTravers(r);
        }
    }

}

int resetArr(){
    for(int i = 0; i < num; ++i){
        visited[i] = 0;
    }
}



int main()
{
    dfs(0);




    printf("===========\n");
    depthTravers(0);
    while(cursor != -1){
        printf("%d", pop());
    }


    return 0;

}
