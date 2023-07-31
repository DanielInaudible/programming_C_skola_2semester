#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

int main(){
    // initialization phase
    int t = 0;
    int parts = 0;

    scanf("%d %d",&parts, &t);

    int* speed = (int*)calloc(parts, sizeof(int)); // 2
    int* length= (int*)calloc(parts ,sizeof(int)); // 1

    for(int i = 0; i < parts; i++){
        scanf("%d %d",&length[i], &speed[i]); 
    }
    
    // vypis
    /*
    for(int i = 0; i < parts; i++){
        printf("%d %d",length[i], speed[i]); 
        printf("\n");
    }
    */
    
    // unknown variable
    float k = 0;
    float result = 0;
    int top = 0;
    int bot = 0;

    for(int i = 0; i < parts; i++){
          result += ((float)length[i] / (speed[i] + k));
    }
    if(result < t){
        bot = -1000;
        top = 0;
    }else{
        top = 1000;
        bot = 0;
    }
    
    int computation = 0;

    // vzorec
    // result = (length[i] / (speed + k))
    
        result = 0;
        computation = top - bot;

        // test K
        for(int i = 0; i < parts; i++){
            result += ((float)length[i] / (speed[i] + k));
        }
        
        // K ZVYSUJEME
        if(result > t){
            k = computation + 1;
            top = k;
        }
        
        // K ZNIZUJEME
        if(result < t){
            k = computation - (computation/2); 
            bot = k;
        }
    
    
    printf("10");

    // free
    free(speed);
    free(length);

    return 0;
}
