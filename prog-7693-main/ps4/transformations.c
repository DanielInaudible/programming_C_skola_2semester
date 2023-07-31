#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

// user files
#include "transformations.h"
#include "bmp.h"

struct bmp_image* flip_horizontally(const struct bmp_image* image){
    if(image == NULL){
        return NULL;
    }

    // rovno dat do new_bmp_image a alokovat to tam
    int number_of_pixel = ( (image->header->width) * (image->header->height) );

    // original citame od zaciatku
    // flip citame od konca originalu...
    // ziadna magia to nieje \_(:^)_/

    // novy image
    struct bmp_image* new_bmp_image = (struct bmp_image*)calloc(1, sizeof(struct bmp_image));
    // novy header
    struct bmp_header* new_header = (struct bmp_header*)calloc(1, sizeof(struct bmp_header));
    // link new_header to new_bmp_image
    new_bmp_image->header = new_header;
    // skopirujeme copy z originalnu
    memcpy(new_bmp_image->header, image->header, sizeof(struct bmp_header));
    // vytvorime nove pixely
    struct pixel* new_pixel = (struct pixel*)calloc(number_of_pixel, sizeof(struct pixel));
    // priradime nove pixely
    new_bmp_image->data = new_pixel;
    
    
    // zapisujeme do noveho pixely
    for(int i = 0; i < new_bmp_image->header->height; i++){
        for(int j = 0; j < new_bmp_image->header->width; j++){
            // (i*height) + j <-- prve je ako stlpce, druhe je element v riadku
            //new_pixel[(i*height) + j] = &image->data[(i*height) + (width-1)-j];
            memcpy(&new_bmp_image->data[(i*new_bmp_image->header->width) + j], &image->data[(i*new_bmp_image->header->width) + ((new_bmp_image->header->width-1)-j)], sizeof(struct pixel) );
        }
    }
    
    return new_bmp_image;
}

struct bmp_image* flip_vertically(const struct bmp_image* image){
    if(image == NULL){
        return NULL;
    }

    // rovno dat do new_bmp_image a alokovat to tam

    int number_of_pixel = ( (image->header->width) * (image->header->height) );

    // original citame od zaciatku
    // flip citame od konca originalu...
    // ziadna magia to nieje \_(:^)_/

    // novy image
    struct bmp_image* new_bmp_image = (struct bmp_image*)calloc(1, sizeof(struct bmp_image));
    // novy header
    struct bmp_header* new_header = (struct bmp_header*)calloc(1, sizeof(struct bmp_header));
    // link new_header to new_bmp_image
    new_bmp_image->header = new_header;
    // skopirujeme copy z originalnu
    memcpy(new_bmp_image->header, image->header, sizeof(struct bmp_header));
    // vytvorime nove pixely
    struct pixel* new_pixel = (struct pixel*)calloc(number_of_pixel, sizeof(struct pixel));
    // priradime nove pixely
    new_bmp_image->data = new_pixel;

    for(int i = 0; i < new_bmp_image->header->height; i++){
        for(int j = 0; j < new_bmp_image->header->width; j++){
            memcpy(&new_bmp_image->data[(new_bmp_image->header->width*i)+j], &image->data[((new_bmp_image->header->width*new_bmp_image->header->height) - (new_bmp_image->header->width*(i+1))) + j], sizeof(struct pixel));            
        }
    }

    return new_bmp_image;
}


struct bmp_image* rotate_left(const struct bmp_image* image){
    if(image == NULL){
        return NULL;
    }

    // rovno dat do new_bmp_image a alokovat to tam

    int number_of_pixel = ( (image->header->width) * (image->header->height) );

    // original citame od zaciatku
    // flip citame od konca originalu...
    // ziadna magia to nieje \_(:^)_/

    // novy image
    struct bmp_image* new_bmp_image = (struct bmp_image*)calloc(1, sizeof(struct bmp_image));
    // novy header
    struct bmp_header* new_header = (struct bmp_header*)calloc(1, sizeof(struct bmp_header));
    // link new_header to new_bmp_image
    new_bmp_image->header = new_header;
    // skopirujeme copy z originalnu
    memcpy(new_bmp_image->header, image->header, sizeof(struct bmp_header));
    // vytvorime nove pixely
    struct pixel* new_pixel = (struct pixel*)calloc(number_of_pixel, sizeof(struct pixel));
    // priradime nove pixely
    new_bmp_image->data = new_pixel;

    uint32_t temp = new_bmp_image->header->width;
    new_bmp_image->header->width = new_bmp_image->header->height;
    new_bmp_image->header->height = temp;
    
    // flip i

    for(int i = 0; i < image->header->width; i++){
        for(int j = 0; j < image->header->height; j++){
            memcpy(&new_bmp_image->data[(i*image->header->height)+j], &image->data[( (image->header->width*image->header->height) - (image->header->width*(j+1)) ) + i],sizeof(struct pixel));
        }
    }

    // teraz budeme menit size a image_size, pretoze ked otocime vysku / sirku, tak sa MOZE PRIDAT PADDING
    int added_size = ((new_bmp_image->header->width*3)%4);
    if(added_size != 0){
        added_size = 4 - added_size;
    }
    // SIZE = offset + width*height + added_size(PADDING)*height;
    new_bmp_image->header->size = new_bmp_image->header->offset + ((new_bmp_image->header->width * new_bmp_image->header->height)*3) + (added_size*new_bmp_image->header->height);
    // IMAGE_SIZE = size - offset
    new_bmp_image->header->image_size = new_bmp_image->header->size - new_bmp_image->header->offset; 
    
    //printf("size = %d\n", new_bmp_image->header->size);
    return new_bmp_image;
}

// DOKONCIT
struct bmp_image* rotate_right(const struct bmp_image* image){
    if(image == NULL){
        return NULL;
    }
    
    // rovno dat do new_bmp_image a alokovat to tam

    int number_of_pixel = ( (image->header->width) * (image->header->height) );

    // original citame od zaciatku
    // flip citame od konca originalu...
    // ziadna magia to nieje \_(:^)_/

    // novy image
    struct bmp_image* new_bmp_image = (struct bmp_image*)calloc(1, sizeof(struct bmp_image));
    // novy header
    struct bmp_header* new_header = (struct bmp_header*)calloc(1, sizeof(struct bmp_header));
    // link new_header to new_bmp_image
    new_bmp_image->header = new_header;
    // skopirujeme copy z originalnu
    memcpy(new_bmp_image->header, image->header, sizeof(struct bmp_header));
    // vytvorime nove pixely
    struct pixel* new_pixel = (struct pixel*)calloc(number_of_pixel, sizeof(struct pixel));
    // priradime nove pixely
    new_bmp_image->data = new_pixel;

    uint32_t temp = new_bmp_image->header->width;
    new_bmp_image->header->width = new_bmp_image->header->height;
    new_bmp_image->header->height = temp;

    int vyska = image->header->height;
    int sirka = image->header->width;
    //rintf("pred flipom\n");
    // flip i
    for(int i = 0; i < image->header->width; i++){
        for(int j = 0; j < image->header->height; j++){
            memcpy(&new_bmp_image->data[ ( (i*vyska)+j ) ], &image->data[ ( (sirka-1)-i) + (sirka*j)], sizeof(struct pixel));
        }
    }
    //printf("som tu");

    int added_size = ((new_bmp_image->header->width*3)%4);
    if(added_size != 0){
        added_size = 4 - added_size;
    }
    // SIZE = offset + width*height + added_size(PADDING)*height;
    new_bmp_image->header->size = new_bmp_image->header->offset + ((new_bmp_image->header->width * new_bmp_image->header->height)*3) + (added_size*new_bmp_image->header->height);
    // IMAGE_SIZE = size - offset
    new_bmp_image->header->image_size = new_bmp_image->header->size - new_bmp_image->header->offset; 
    //printf("size = %d\n",new_bmp_image->header->size);

    return new_bmp_image;
}

// ZMENIT IBA METADATA
// OTOCIT, SIZE, 
struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width){ 
    int vyska = image->header->height;
    int sirka = image->header->width;
    
    // chybne vstupy
    if(image == NULL || start_y < 0 || start_y > vyska || start_x < 0 || start_x > sirka){
        return NULL;
    }

    if(height < 1 || height > vyska || width < 1 || width > sirka){
        return NULL;
    }
    
    
    // rovno dat do new_bmp_image a alokovat to tam

    //int number_of_pixel = ( (image->header->width) * (image->header->height) );

    // original citame od zaciatku
    // flip citame od konca originalu...
    // ziadna magia to nieje \_(:^)_/

    // novy image
    
    struct bmp_image* new_bmp_image = (struct bmp_image*)calloc(1, sizeof(struct bmp_image));
    // novy header
    struct bmp_header* new_header = (struct bmp_header*)calloc(1, sizeof(struct bmp_header));
    // link new_header to new_bmp_image
    new_bmp_image->header = new_header;
    // skopirujeme copy z originalnu
    memcpy(new_bmp_image->header, image->header, sizeof(struct bmp_header));

    // upravime hodnoty
    //new_bmp_image->header->height = height;
    //new_bmp_image->header->width = width;
    /*
    int nulove = ((width*3)%4);
    if(nulove != 0){
        nulove = 4 - nulove;
    }
    */
    
    // padding
    //new_bmp_image->header->image_size = (width*height) + (nulove*height);
    //new_bmp_image->header->size = image->header->offset + new_bmp_image->header->image_size;
    
    /*
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            memcpy(&new_bmp_image->data[j+(i*height)], &image->data[j*(i*height)], sizeof(struct pixel) );
        }
    }
    */
    
    // vytvorime nove pixely
    struct pixel* new_pixel = (struct pixel*)calloc( (image->header->width*image->header->height), sizeof(struct pixel));
    // priradime nove pixely
    new_bmp_image->data = new_pixel;
    
    for(int i = 0; i < image->header->height; i++){
        for(int j = 0; j < image->header->width; j++){
            memcpy(&new_bmp_image->data[ (i*width) + j ], &image->data[(i*width) + j], sizeof(struct pixel));
        }
    }
    
    
    return new_bmp_image;
}

struct bmp_image* scale(const struct bmp_image* image, float factor){
    return NULL;
}

struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep){
    if(image == NULL || colors_to_keep == NULL){
        return NULL;
    }

    int red = 0;
    int green = 0;
    int blue = 0;
    //int prazdny = 0;
    char temp = 'a';
    int index = 0;

    while((temp = colors_to_keep[index]) != '\0'){
        if(temp != 'r' && temp != 'g' && temp != 'b'){
            return NULL;
        }else{
            if(temp == 'r'){
                red = 1;
            }

            if(temp == 'g'){
                green = 1;
            }

            if(temp == 'b'){
                blue = 1;
            }
        }

        index++;
    }

    /*
    if(red == 0 && green == 0 && blue == 0){
        return NULL;
    }
    */

    // rovno dat do new_bmp_image a alokovat to tam
    int number_of_pixel = ( (image->header->width) * (image->header->height) );

    // original citame od zaciatku
    // flip citame od konca originalu...
    // ziadna magia to nieje \_(:^)_/

    // novy image
    struct bmp_image* new_bmp_image = (struct bmp_image*)calloc(1, sizeof(struct bmp_image));
    // novy header
    struct bmp_header* new_header = (struct bmp_header*)calloc(1, sizeof(struct bmp_header));
    // link new_header to new_bmp_image
    new_bmp_image->header = new_header;
    // skopirujeme copy z originalnu
    memcpy(new_bmp_image->header, image->header, sizeof(struct bmp_header));
    // vytvorime nove pixely
    struct pixel* new_pixel = (struct pixel*)calloc(number_of_pixel, sizeof(struct pixel));
    // priradime nove pixely
    new_bmp_image->data = new_pixel;

    for(int i = 0; i < number_of_pixel; i++){
        memcpy(&new_bmp_image->data[i], &image->data[i], sizeof(struct pixel));

        if(red == 0){
            new_bmp_image->data[i].red = 0;
        }

        if(blue == 0){
            new_bmp_image->data[i].blue = 0;
        }

        if(green == 0){
            new_bmp_image->data[i].green = 0;
        }
    }

    return new_bmp_image;
}

