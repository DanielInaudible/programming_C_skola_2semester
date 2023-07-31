#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// user files
#include "transformations.h"
#include "bmp.h"

int main(){
    // PRVE 3 ulohy 
    FILE *fp;

    fp = fopen("square.1x1.bmp","rb");
    //fp = fopen("/home/john/git_zadania_2023/prog-7693/ps4/crazy.joe.bmp","rb");

    FILE* fo;
    //fo = fopen("/home/john/git_zadania_2023/prog-7693/ps4/output.bmp", "wb+");
    fo = fopen("output.bmp","wb");

    // TRANSFORMATIONS
    struct bmp_image* image_1 = read_bmp(fp);
    //printf("som tu");

    struct bmp_image* image_2 = rotate_left(image_1);
    
    image_2 = rotate_right(image_1);

    image_2 = scale(image_1, 1.1);
    //printf("som tu.");

    if(image_2 != NULL){
        image_2 = crop(image_2, 0, 0, 0, 0);
    }

    image_2 = flip_horizontally(image_1);

    image_2 = flip_vertically(image_1);

    // BMP
    //struct bmp_image* obrazok = read_bmp(fp);
    
    // TRANSFORMATIONS
    image_2 = extract(image_1, "");
    

    bool written = write_bmp(fo, image_2);
    

    //free_bmp_image(image_1);
    free_bmp_image(image_2);
 
    if(written){
        return 0;
    }

    return 0;
}
