// system
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

// user
#include "hof.h"

#ifndef _K_H
#include "k.h"
#endif

#ifndef K_UI_H
#include "ui.h"
#endif


int main(){
// values of variables before add_player() is called

struct player player = {.name="Samuel", .score=347};
int size=10;
struct player hof[10] = {
    {.score= 1625, .name="Samuel"},
    {.score= 1373, .name="Bill"},
    {.score= 1231, .name="John"},
    {.score= 1230, .name="John"},
    {.score= 1212, .name="John"},
    {.score= 1206, .name="Manager"},
    {.score=  639, .name="John"},
    {.score=  620, .name="Manager"},
    {.score=  490, .name="Samuel"},
    {.score=  347, .name="John"}
};

    printf("size before : %d\n",size);
    add_player(hof,&size,player);
    printf("size after : %d\n",size);

    for(int i = 0; i < size; i++){
        printf("%d name = %s\n",i,hof[i].name);
        printf("%d score = %d\n",i,hof[i].score);
    }

    
    struct player list[10];
    int answer = load(list);
    if(answer != -1){
        for(int i = 0; i < answer; i++){
            printf("%d.name = %s\n",i,list[i].name);
            printf("%d.score = %d\n",i,list[i].score);
        }
    }else{
        printf("fail...\n");
    }

    bool answer_save = save(list, answer);
    if(answer_save){
        printf("save succesfull!\n");
    }else{
        printf("unsucsesfull save...\n");
    }
    
    struct player hrac;
    strcpy(hrac.name,"Boris");
    hrac.score = 15000;

    bool answer_add = add_player(list, &answer, hrac);
    if(answer_add){
        for(int i = 0; i < answer; i++){
            printf("%d.name = %s\n",i,list[i].name);
            printf("%d.score = %d\n",i,list[i].score);
        }

    }else{
        printf("nepodarilo sa pridat...");
    }

    // struct creation
    struct game herne_pole;
    // struct initialization
    nacitaj_board(&herne_pole);
    herne_pole.board[0][0] = 'A';
    herne_pole.board[0][1] = ' ';
    herne_pole.board[0][2] = ' ';
    herne_pole.board[0][3] = 'A';

    herne_pole.board[1][0] = 'A';
    herne_pole.board[1][1] = 'E';
    herne_pole.board[1][2] = ' ';
    herne_pole.board[1][3] = 'C';

    herne_pole.board[2][0] = 'A';
    herne_pole.board[2][1] = ' ';
    herne_pole.board[2][2] = ' ';
    herne_pole.board[2][3] = 'D';

    herne_pole.board[3][0] = ' ';
    herne_pole.board[3][1] = 'A';
    herne_pole.board[3][2] = 'D';
    herne_pole.board[3][3] = 'D';

    
    if(is_move_possible(herne_pole) ){
        printf("Existuje tah!\n");
    }else{
        printf("Neexistuje dalsi tah...\n");
    }

    render(herne_pole);
    add_random_tile(&herne_pole);

    bool mozny_tah = update(&herne_pole,0,1561);
    if(mozny_tah){
        printf("dalsi tah je mozny!\n");
    }else{
        printf("dalsi tah neexistuje...\n");
    }
    
    // vypis
    render(herne_pole);

    mozny_tah = update(&herne_pole,0,1);
    if(mozny_tah){
        printf("dalsi tah je mozny!\n");
    }else{
        printf("dalsi tah neexistuje...\n");
    }
    
    // vypis
    render(herne_pole);

    
    // victory clause
    if(is_game_won(herne_pole)){
        printf("\nVyhrali ste !\n");
    }else{
        printf("\nPrehrali ste...\n");
    }
    
    
    return 0;
}
