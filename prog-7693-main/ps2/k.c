#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "k.h"

// user-defined function
void nacitaj_board(struct game *game){
    game->score = 0;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            game->board[i][j] = ' ';
        }
    }
}


void add_random_tile(struct game *game){
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}

// #1
// FUNKCNA
bool is_game_won(const struct game game){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(game.board[i][j] == 'K'){
                return true;
            }
        }
    }
    return false;
}

// user-defined function
void resetuj_pole(int *pole){
    for(int i = 0; i < 11; i++){
        pole[i] = 0;
    }
}

// #2
// FUNKCNA
// zbytocne zlozita, pomylil som si ju uz so zmenou stavu hry...
bool is_move_possible(const struct game game){
    // nasa funckia najprv prejde stlpce, potom prejde riadky
    // ak zachyti 2 rovnake znaky, zacne sa cez iteracie vraciat naspet
    // ak cestou ku rovnakemu charakteru narazi na charakter, ktory sa nerovna ' '
    // vracia hodnotu false
    // ak cestou ku rovaneku charakteru nenarazi na charakter, ktory sa nerovna ' '
    // vracia hodnotu true

    // !!! NEZABUDAJME PLOCHA MOZE BYT VIACEJ AKO 4 !!!!
    
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            // medzera, pohyb existuje
            if(game.board[i][j] == ' '){
                return true;
            }
        }
    }

    // A B C D E F G H I J K
    // counting arrays
    int values[11] = {0};
    int back = 0;

    // stlpce
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            // nieje medzera, pridaj do counting array+1
            if(game.board[i][j] != ' '){
                values[game.board[i][j] - 65]++;
            
                // dane pismeno sa nachadza v array viac ako 2x
                if(values[game.board[i][j] - 65] > 1){
                    back = j-1;
                    while(back >= -1){
                        // move is possible
                        if(game.board[i][back] == game.board[i][j]){
                            return true;
                        }   
                    
                        // neni medzera, neni to hladane cislo, move nemozny hladaj dalej
                        if(game.board[i][back] != ' ' && game.board[i][back] != game.board[i][j]){
                            break;
                        }
                        back--;
                    }
                }
            }
        }
        // set counting array back to 0
        resetuj_pole(values);
    }

    // riadky
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            // nieje medzera, pridaj do counting array+1
            if(game.board[j][i] != ' '){
                values[game.board[j][i] - 65]++;

                // dane pismeno sa nachadzsa v array viac ako 2x
                if(values[game.board[j][i] - 65] > 1){
                   back = j-1;
                   while(back >= -1){
                        // move is possible
                        if(game.board[back][i] == game.board[j][i]){
                            return true;
                        }

                        // neni medzera, neni to kladne cislo, move nemozny hladaj dalej
                        if(game.board[back][i] != ' ' && game.board[back][i] != game.board[j][i]){
                            break;
                        }
                        back--;
                   }
                }
            }
        }
        // set counting array back to 0
        resetuj_pole(values);
    }

    return false;
}


// #3
bool update(struct game *game, int dy, int dx){
    bool state_changed = false;

    // invalid values of arguments
    if( (dy == 0 && dx == 0) || (dy != 0 && dx != 0)){
        return false;
    }
    
    // garbage values..
    if( (dy > 1 || dx > 1 ) || (dx < -1 || dy < -1)){
        return false;
    }
    
    // check if any space is free, if yes state_chanfed = true
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(game->board[i][j] == ' '){
                state_changed = true;
            }
        }
    }
    
    // UP-------------------------------------------------
    // first move all letters till, they are all at the top
    // pole[j][i]
    if(dy == -1){
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                // ak pismeno, A NIEJE NA VRCHOLE
                if(game->board[j][i] != ' ' && j != 0){
                    int up = j;
                    while(up != 0 && game->board[up-1][i] == ' '){
                        // policko nad je volne
                        game->board[up-1][i] = game->board[up][i];
                        game->board[up][i] = ' ';
                        up--;
                    }
                }
            }
        }

        // now connect letters together
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE-1; j++){
                if(game->board[j][i] == game->board[j+1][i] && game->board[j][i] != ' '){
                    // ak A->B
                    game->score += (int)(pow(2, game->board[j][i]-'@')*2);
                    game->board[j][i] = (char)(game->board[j][i]+1);
                    game->board[j+1][i] = ' ';
                    state_changed = true;
                }
            }
        }
    
        // again move up...
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                // ak pismeno, A NIEJE NA VRCHOLE
                if(game->board[j][i] != ' ' && j != 0){
                    int up = j;
                    while(up != 0 && game->board[up-1][i] == ' '){
                        // policko nad je volne
                        game->board[up-1][i] = game->board[up][i];
                        game->board[up][i] = ' ';
                        up--;
                    }
                }
            }
        }
    }
     
    // DOWN ----------------------------------------------------
    // pole[j][i]
    if(dy == 1){
        for(int i = 0; i < SIZE; i++){
            for(int j = SIZE; j >= 0; j--){
                // ak pismeno, A NIEJE NA VRCHOLE
                if(game->board[j][i] != ' ' && j != SIZE){
                    int up = j;
                    while(up != SIZE && game->board[up+1][i] == ' '){
                        // policko nad je volne
                        game->board[up+1][i] = game->board[up][i];
                        game->board[up][i] = ' ';
                        up++;
                    }
                }
            }
        }
        // now connect letters together
        for(int i = 0; i < SIZE; i++){
            for(int j = SIZE-1; j > 0; j--){
                if(game->board[j][i] == game->board[j-1][i] && game->board[j][i] != ' '){
                        // ak A->B
                        game->score += (int)(pow(2, game->board[j][i]-'@')*2);
                        game->board[j][i] = (char)(game->board[j][i]+1);
                        game->board[j-1][i] = ' ';
                        state_changed = true;
                    }
                }
        }
    
        // again move up...
        for(int i = 0; i < SIZE; i++){
            for(int j = SIZE; j >= 0; j--){
                // ak pismeno, A NIEJE NA VRCHOLE
                if(game->board[j][i] != ' ' && j != SIZE){
                    int up = j;
                    while(up != SIZE && game->board[up+1][i] == ' '){
                        // policko nad je volne
                        game->board[up+1][i] = game->board[up][i];
                        game->board[up][i] = ' ';
                        up++;
                    }
                }
            }
        }
    }
    

    // DOLAVA-----------------------------------------------------------
    //<-- dx = -1
    if(dx == -1){
        for(int j = 0; j < SIZE; j++){
            for(int i = 0; i < SIZE; i++){
                // ak pismeno, A NIEJE NA VRCHOLE
                if(game->board[j][i] != ' ' && i != 0){
                    int up = i;
                    while(up != 0 && game->board[j][up-1] == ' '){
                        // policko nad je volne
                        game->board[j][up-1] = game->board[j][up];
                        game->board[j][up] = ' ';
                        up--;
                    }
                }
            }
        }

        // now connect letters together
        for(int j = 0; j < SIZE; j++){
            for(int i = 0; i < SIZE-1; i++){
                if(game->board[j][i] == game->board[j][i+1] && game->board[j][i] != ' '){
                    // ak A->B
                    game->score += (int)(pow(2, game->board[j][i]-'@')*2);
                    game->board[j][i] = (char)(game->board[j][i]+1);
                    game->board[j][i+1] = ' ';
                    state_changed = true;
                }
            }
        }
    
        // again move up..
        for(int j = 0; j < SIZE; j++){
            for(int i = 0; i < SIZE; i++){
                // ak pismeno, A NIEJE NA VRCHOLE
                if(game->board[j][i] != ' ' && i != 0){
                    int up = i;
                    while(up != 0 && game->board[j][up-1] == ' '){
                        // policko nad je volne
                        game->board[j][up-1] = game->board[j][up];
                        game->board[j][up] = ' ';
                        up--;
                    }
                }
            }
        }
       
    }
    //DOPRAVA-----------------------------------------------------------
    //--> dx = 1
    if(dx == 1){
        //printf("DOPRAVA\n");
        for(int j = 0; j < SIZE; j++){
            for(int i = SIZE; i >= 0; i--){
                // ak pismeno, A NIEJE NA VRCHOLE
                if(game->board[j][i] != ' ' && i != SIZE){
                    int up = i;
                    while(up != SIZE-1 && game->board[j][up+1] == ' '){
                        // policko nad je volne
                        game->board[j][up+1] = game->board[j][up];
                        game->board[j][up] = ' ';
                        up++;
                    }
                }
            }
        }
        
        // now connect letters together
        for(int j = 0; j < SIZE; j++){
            for(int i = SIZE-1; i > 0; i--){
                if(game->board[j][i] == game->board[j][i-1] && game->board[j][i] != ' '){
                    // ak A->B
                    game->score += (int)(pow(2, game->board[j][i]-'@')*2);
                    game->board[j][i] = (char)(game->board[j][i]+1);
                    game->board[j][i-1] = ' ';
                    state_changed = true;
                }
            }
        }
    
        // again move up...
        for(int j = 0; j < SIZE; j++){
            for(int i = SIZE; i >= 0; i--){
                // ak pismeno, A NIEJE NA VRCHOLE
                if(game->board[j][i] != ' ' && i != SIZE){
                    int up = i;
                    // SIZE-1 TU JE POTENCIALNA CHYBA V HORIZONTALNYCH !!!!!!!!!!!
                    while(up != SIZE-1 && game->board[j][up+1] == ' '){
                        // policko nad je volne
                        game->board[j][up+1] = game->board[j][up];
                        game->board[j][up] = ' ';
                        up++;
                    }
                }
            }
        }
        
    }
 
    return state_changed;
}

