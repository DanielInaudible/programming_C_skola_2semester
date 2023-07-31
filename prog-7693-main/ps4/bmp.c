#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// user files
#include "bmp.h"

#define BMP_FORMAT 0x4D42

// otvarat FILE* stream, musime este pred funkciou, kedze tam nepasujeme nazov nasho suboru

// NACITA HEADER
struct bmp_header* read_bmp_header(FILE* stream){
    // DRY RUN
    if(stream == NULL){
        return NULL;
    }

    // create new_header on heap
    struct bmp_header* new_header = (struct bmp_header*)calloc(1,sizeof(struct bmp_header));
    
    // na zaciatok filu
    fseek(stream, 0, SEEK_SET);
    // precitame
    fread(new_header,sizeof(struct bmp_header),1,stream);

    // WIDTH AND HEIGHT TEST
    if(new_header->width < 1 || new_header->height < 1){
        free(new_header);
        return NULL;
    }

    // ZLY TYPE
    if(new_header->type != BMP_FORMAT){
        free(new_header);
        return NULL;
    }

    int nulte_znaky = (new_header->width*3)%4;
    if(nulte_znaky != 0){
        nulte_znaky = 4 - nulte_znaky;
    }

    //printf("nulte znaky = %d\n", nulte_znaky);

    new_header->image_size = ((new_header->width*new_header->height)*sizeof(struct pixel)) + (new_header->height*nulte_znaky);
    //printf("image_size = %d\n",new_header->image_size);
    //new_header->size = new_header->image_size + new_header->offset;

    // pixely = (width*height)
    // size = offset + pixely*3 + nulte znaky
    // image_size = pixely*3 + nulte znaky
    
    return new_header;
}
// NACITA PIXELY
struct pixel* read_data(FILE* stream, const struct bmp_header* header){
    // DRY RUN
    if(stream == NULL || header == NULL){
        return NULL;
    }

    // skip 54 bytes // header
    fseek(stream, 0, SEEK_SET);
    fseek(stream, 54, SEEK_SET);
    
    // vytvor height*pixel pixelov
    struct pixel* new_pixel = (struct pixel*)calloc(header->width*header->height, sizeof(struct pixel));
    int nulte_znaky = (header->width*3)%4;
    if(nulte_znaky != 0){
        nulte_znaky = 4 - nulte_znaky;
    }

    int skip = 0;

    int vyska = header->height;
    int sirka = header->width;

    for(int i = 0; i < (vyska*sirka); i++){
        if(nulte_znaky != 0){
            if(skip == sirka){
                // posun sa o 1 poziciu tolkokrat kolko je nultych znakov
                for(int j = 0; j < nulte_znaky; j++){
                    fseek(stream, 1, SEEK_CUR);
                    //printf("nulty znak ");
                }
                skip = 0;
                //printf("\n");
            }
        }
        fread(&new_pixel[i], sizeof(struct pixel), 1, stream);
        //printf("pixel %d ",i);
        skip++;
    }
    // VIZUALIZACIA KONCOVYCH NULTYCH ZNAKOV
    /*
    if(nulte_znaky != 0){
        for(int j = 0; j < nulte_znaky; j++){
            printf("nulty znak ");
        }
        printf("\n");
    }
    */
    
    return new_pixel;
}

// KOMPLETNY OBRAZOK
struct bmp_image* read_bmp(FILE* stream){   
    if(stream == NULL){
        return NULL;
    }

    struct bmp_image* new_bmp_image = (struct bmp_image*)calloc(1, sizeof(struct bmp_image));
    
    new_bmp_image->header = read_bmp_header(stream);
    if(new_bmp_image->header == NULL){
        free(new_bmp_image);
        printf("Error: This is not a BMP file.");
        return NULL;
    }
    new_bmp_image->data = read_data(stream, new_bmp_image->header);
    if(new_bmp_image->data == NULL){
        free(new_bmp_image->header);
        free(new_bmp_image);
        // POTENCIALNA CHYBA
        printf("Error: Corrupted BMP file.");
        return NULL;
    }


    return new_bmp_image; 
}

// ZAPIS NA OUTPUT
bool write_bmp(FILE* stream, const struct bmp_image* image){
    // do stream teraz zapisujeme
    if(stream == NULL || image == NULL){
        return false;
    }
    // hodime si to na zaciatok
    fseek(stream, 0, SEEK_SET);

    // zapisat hlavicku
    fwrite(image->header, sizeof(struct bmp_header), 1, stream);
    
    // nulte znaky
    int nulte_znaky = ((image->header->width*3)%4);
    if(nulte_znaky != 0){
        nulte_znaky = 4 - nulte_znaky;
    }
    
    int skip = 0;

    int vyska = image->header->height;
    int sirka = image->header->width;

    for(int i = 0; i < (vyska*sirka); i++){
        if(nulte_znaky != 0){
            if(skip == sirka){
                // posun sa o 1 poziciu tolkokrat kolko je nultych znakov
                for(int j = 0; j < nulte_znaky; j++){
                    fwrite(PADDING_CHAR, 1, 1, stream);
                    //printf("nulty znak ");
                }
                skip = 0;
                //printf("\n");
            }
        }
        fwrite(&image->data[i], sizeof(struct pixel), 1, stream);
        //printf("pixel %d ",i);
        skip++;
    }
    // VIZUALIZACIA KONCOVYCH NULTYCH ZNAKOV
    
    if(nulte_znaky != 0){
        for(int j = 0; j < nulte_znaky; j++){
            fwrite(PADDING_CHAR, 1, 1, stream);
            //printf("nulty znak ");
        }
        //printf("\n");
    }

    return true;
}

void free_bmp_image(struct bmp_image* image){
    if(image == NULL){
        return;
    }

    // free pixels
    /*
    for(int i = 0; i < (image->header->image_size/3); i++){
        free(&image->data[i]);
    }
    */
    if(image->data != NULL){
        free(image->data);
    }

    // free header
    if(image->header != NULL){
        free(image->header);
    }

    // free image
    free(image);
}
