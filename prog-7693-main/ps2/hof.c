#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#include "hof.h"

int load(struct player list[]){
    // file
    FILE* fread;
    fread = fopen(HOF_FILE,"r");
    
    // no file
    if(!fread){
        return -1;
    }

    // no words
    char letter;
    bool empty = true;
    while((letter = (char)fgetc(fread)) != EOF){
        if(letter != ' ' && letter != '\n' && letter != EOF){
            empty = false;
        }
    }
    fclose(fread);
    if(empty==true){
        return 0;
    }

    // count numb of entries
    int number_of_entries = 0; // 1 pretoze EOF sa taktiez pocita ako nova line
    fread = fopen(HOF_FILE,"r");
    while((letter = (char)fgetc(fread)) != EOF){
        if(letter == '\n'){
            number_of_entries++;
        }
    }
    fclose(fread);

    // number of repetitions
    int repetitions = 0;
    if(number_of_entries > 10){
        repetitions = 10;
    }else{
        repetitions = number_of_entries;
    }

    // STEP 1
    // zoberies prvy score a name, porovnavas s dalsimi, az pokial nedojdes nakoniec
    // do listu zapises meno aj score

    // STEP 2
    // zoberies prvy score a name, porovnavas s dalsimi A ZAROVEN porovnas s uz zapisanim, az pokial nedojdes nakoniec
    struct player hraci[number_of_entries]; // array, kde zapiseme vsetkych hracov
    int index = 0;
    char name[30];
    char number[15];

    fread = fopen(HOF_FILE,"r");
    for(int i = 0; i < number_of_entries; i++){
        // null array
        for(int i = 0; i < 30; i++){
            name[i] = '\0';
        }
        for(int i = 0; i < 15; i++){
            number[i] = '\0';
        }
        
        index = 0;
        // read name
        while((letter = (char)fgetc(fread)) != ' '){
            name[index] = letter;
            index++;
        }
        strcpy(hraci[i].name,name);

        index = 0;
        // read number
        while((letter = (char)fgetc(fread)) != '\n' && letter != EOF){
            number[index] = letter;
            index++;
        }
        int numb = atoi(number);
        hraci[i].score = numb;
    }
    fclose(fread);

    // readout
    /*
    for(int i = 0; i < number_of_entries; i++){
        printf("%d.name = %s\n",i,hraci[i].name);
        printf("%d.score = %d\n",i,hraci[i].score);
    }
    printf("______________\n");
    */

    // sort
    for(int i = 0; i < number_of_entries; i++){
        for(int j = 0; j < number_of_entries-1; j++){
            // j+1 > j, takze switch
            if(hraci[j].score < hraci[j+1].score){
                // SWITCH SCORE
                int temp = hraci[j].score;
                hraci[j].score = hraci[j+1].score;
                hraci[j+1].score = temp;
                // SWITCH NAME
                char temp_m[30];
                strcpy(temp_m,hraci[j].name);
                strcpy(hraci[j].name,hraci[j+1].name);
                strcpy(hraci[j+1].name,temp_m);
            }
        }
    }
    // zapis
    for(int i = 0; i < repetitions; i++){
        list[i].score = hraci[i].score;
        strcpy(list[i].name,hraci[i].name);
    }

    // count lines
    return repetitions;
}

bool save(const struct player list[], const int size){
    FILE* fwrite;
    fwrite = fopen(HOF_FILE,"w+");
    if(!fwrite){
        return false;
    }

    if(size == 0){
        fclose(fwrite);
        return true;
    }

    for(int i = 0; i < size; i++){
        fprintf(fwrite,"%s %d\n",list[i].name,list[i].score);
    }
    // zatvor file
    fclose(fwrite);

    return true;
}

bool add_player(struct player list[], int* size, const struct player player){
    // no entries...
    // 1.1 error
    if(*size == 0){
        list[0].score = player.score;
        strcpy(list[0].name,player.name);
        *size += 1;
        return true;

    }

    // check if he can make it to list
    bool in_hof = false;
    for(int i = 0; i < *size; i++){
        if(player.score >= list[i].score){
            in_hof = true;
        }
    }
    
    // FIX 1.2
    // nieje miesto a zaroven uz je PLNY
    if(in_hof == false && *size == 10){
        return false;
    }

    for(int i = 0; i < *size; i++){
        if(player.score >= list[i].score){
            // same name, same score
            // uz sa tam nachadzsa
            // rovnake skore, porovnaj ci sa posunies dole alebo ostanes na mene
            /*
            if(player.score == list[i].score && strcmp(player.name,list[i].name) < 0){
                i++;
            }
            */
            // zapis
            // prejdi vsetky ale posunute
            // vojde sa, nemusime ziaden entry odstranit
            if(*size < 10){
                *size += 1;
                // od konca
                for(int j = (*size)-1; j > i; j--){
                    // save to temp
                    list[j].score = list[j-1].score;
                    strcpy(list[j].name,list[j-1].name);
                }
                // daj meno hraca
                list[i].score = player.score;
                strcpy(list[i].name,player.name);
                return true;
            }
            // prejdi vsetky, ale list je uz zapisany uplne
            if(*size == 10){
                for(int j = 9; j > i; j--){ 
                    // save to temp
                    list[j].score = list[j-1].score;
                    strcpy(list[j].name,list[j-1].name);
                }
                // daj meno hraca
                list[i].score = player.score;
                strcpy(list[i].name,player.name);
                return true;
            }// POTREBNE TERAZ
        }/*else if(player.score == list[i].score && (strcmp(player.name, list[i].name) == 0 )){
               return true; 
        }
        */
    }

    if(*size < 10){
        list[*size].score = player.score;
        strcpy(list[*size].name, player.name);
        *size += 1;
        return true;
    }
    
    // nikdy tu nepride ale tak whatever...
    return true;
}
