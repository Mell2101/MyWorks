#include <stdio.h>
#include <stdlib.h>

#define colTree 50
#define truee 1 == 1
#define falsee 1 != 1

typedef int boolean;

typedef struct Node{
    int key;
    struct Node* left;
    struct Node* right;
}TreeNode;

boolean BinSearch(TreeNode* tree, int value){
    if(tree == NULL)
        return falsee;
    if(tree->key == value)
        return truee;

    TreeNode* current = tree;
    while(current->key != value){
        if(value < current->key)
            current = current->left;
        else
            current = current->right;
        if(current == NULL)
            return falsee;

    }
}


int check(int balanc){
    int nL;
    int nR;
    if(nL - nR > 1){
        printf("This is tree has not balance \n");
    }else{
        printf("This is tree has balance \n");
    }

}

int balanc(TreeNode *tree){
    int nL;
    int nR;
    if(tree == NULL){
        return 0;
    }else{
      nL = balanc(tree->left);
      nR = balanc(tree->right);
      if(nL <= nR){
         return nR + 1;
      }else{
         return nL + 1;
      }
    }
}

TreeNode* treeInsert(TreeNode *t, int data){
    TreeNode *newNode;
    newNode = (TreeNode*) malloc(sizeof(TreeNode));
    newNode->key = data;
    newNode->left = NULL;
    newNode->right = NULL;
    TreeNode *current = t;
    TreeNode *parent = t;
    if(t == NULL){
        t = newNode;
    }else{
        while(current->key != data){
            parent = current;
            if(current->key > data){
                current = current->left;
                if (current == NULL){
                    parent->left = newNode;
                    return t;
                }
            }else{
                current = current->right;
                if(current == NULL){
                    parent->right = newNode;
                    return t;
                }
            }
        }
    }
    return t;
}

void printTree(TreeNode*root){
    if(root){
        printf("%d", root->key);
        if(root->left || root->right){
            printf("(");
            if(root->left)
                printTree(root->left);
            else
                printf("NULL");
            printf(",");
            if(root->right)
                printTree(root->right);
            else
                printf("NULL");
            printf(")");
        }
    }
}


int main()
{

    for(int j = 0; j < colTree; j++){
        TreeNode* tree = NULL;
        tree = treeInsert(tree,rand()%100);
        for(int i = 0;i <= 1000;++i){
        treeInsert(tree, rand()%1000);
        }
      //  printTree(tree);
        printf("\n");
        check(balanc(tree));
    printf( "Number in tree = %s \n", BinSearch(tree,56) ?  "true" : "false");
    }
    TreeNode* tree2 = NULL;
    tree2 = treeInsert(tree2,50);
    treeInsert(tree2,10);
    treeInsert(tree2,9);
    treeInsert(tree2,68);
    treeInsert(tree2,7);
    treeInsert(tree2,56);
    treeInsert(tree2,49);
    treeInsert(tree2,11);
    printf( "Number in tree = %s \n", BinSearch(tree2,11) ?  "true" : "false");
    printf( "Number in tree = %s \n", BinSearch(tree2,1) ?  "true" : "false");


    printf("\n");
    return 0;

}
