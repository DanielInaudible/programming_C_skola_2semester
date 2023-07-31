#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// STRUCT NODE
struct Node{
    int number;
    struct Node* right;
    struct Node* left;
}; 

// FUNCTION TO CREATE A NODE
struct Node* add_node(int numb){
    struct Node* new_node = calloc(1,sizeof(struct Node));
    new_node->number = numb;
    new_node->right = NULL;
    new_node->left = NULL;

    return new_node;
}

// FUNCTON TO CHECK, IF 2 TRES ARE IDENTICAL
// 1 ok
// 0 bad
int equal(struct Node* jedna,struct Node* dva){
    if(!jedna && !dva){
        return 1;
    }

    if(jedna != NULL && dva != NULL){
        return (equal(jedna->left, dva->left) &&  equal(jedna->right, dva->right));
    }

    return 0;
}

// FUNCTION TO FILL UP GIVEN TREE WITH GIVEN NUMBER
// 1 done
// 0 recursive call
int add_number(int numb, struct Node* node){
    // LEFT
    if(node->number > numb){
        // EMPTY
        if(node->left == NULL){
            node->left = add_node(numb);
            //printf("zapisujem left\n");
            return 0;
        }else{
            // RECURSIVE CALL
            //printf("uroven nizzsie left\n");
            add_number(numb, node->left);
            return 0;
        }
    // RIGHT    
    }
    if(node->number < numb){
        // EMPTY
        if(node->right == NULL){
            node->right = add_node(numb);
            //printf("zapisujem right\n");
            return 0;
        }else{
            // RECURSIVE CALL
            //printf("uroven nizzsie right\n");
            add_number(numb, node->right);
            return 0;
        }
    }

    //printf("\n");

    return 0;
}

int main(){
    int trees = 0;
    int layers = 0;
    int input = 0;
    
    scanf("%d %d", &trees, &layers);

    // 2D array, trees
    int** array = (int**)calloc(trees, sizeof(int*));
    // 1D array, layers
    for(int i = 0; i < trees; i++){
        array[i] = (int*)calloc(layers, sizeof(int));
    }

    // napln ich
    for(int i = 0; i < trees; i++){
        for(int j = 0; j < layers; j++){
            scanf("%d",&input);
            array[i][j] = input;
        }
    }

    // vypis
    /*
    for(int i = 0; i < trees; i++){
        for(int j = 0; j < layers; j++){
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
    */
    
    // LIST, KDE BUDU ROOT NODES, SLUZIA AKO STROM
    struct Node* list_of_root_nodes = (struct Node*)calloc(trees, sizeof(struct Node));
    
    // FILL UP ALL NODES
    for(int i = 0; i < trees; i++){
        // ADD ROOT NODE
        list_of_root_nodes[i].number = array[i][0];
        for(int j = 1; j < layers; j++){
            // FILL UP WITH ADD_NUMBER
            //printf("zapisujem %d\n", array[i][j]);
            add_number(array[i][j], &list_of_root_nodes[i]);
        }
    }
    
    int same = 0;

    // COMPARE ALL
    //printf("trees = :%d\n",trees);
    for(int i = 0; i < trees; i++){
        for(int j = i; j < trees - 1; j++){
            //printf("porovnavam: %d - %d\n",i,j+1);
            int result = equal(&list_of_root_nodes[i], &list_of_root_nodes[j+1]);
            if(result == 1){
                same++;
            }
        }
    }

    printf("%d\n",trees-same);
    
    
    //printf("trees : %d\n",trees);
    // FREE ALL
    /*
    for(int i = 0; i < trees; i++){
        printf("freeying tree %d\n",i);
        free_list_of_root(&list_of_root_nodes[i]);
    }
    */

    // free 1D
    for(int i = 0; i < trees; i++){
        free(array[i]);
    }
    // free 2D
    free(array);

    return 0;
}
