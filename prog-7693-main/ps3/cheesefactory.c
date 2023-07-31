#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

int main(){
    int holes = 0;
    int slices = 0;

    int x = 0;

    scanf("%d %d",&holes, &slices);

    for(int i = 0; i < holes; i++){
        for(int j = 0; j < 4; j++){
            scanf("%d",&x);
        }
    }

    float result = 100 / (float)slices;

    for(int i = 0; i < slices; i++){
        printf("%.6f\n", result);
    }

    return 0;
}
