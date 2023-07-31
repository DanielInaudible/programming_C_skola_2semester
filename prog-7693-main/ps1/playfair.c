    #include <stdio.h>
    #include <ctype.h>
    #include <string.h>
    #include <stdlib.h>

    // 1 - playfarova sifra
        // 1/1
    char* playfair_encrypt(const char* key, const char* text){
        // empty
        if(key == NULL || text == NULL){
            return NULL;
        }
        
        int ukonc_to = 1;
        // kluc same medzery
        for(int i = 0; i < strlen(key); i++){
            if(key[i] != ' '){
                ukonc_to = 0;
            }
        }
        if(ukonc_to == 1){
            return NULL;
        }

        // check key
        for(int i = 0;i < strlen(key); i++){
            if(key[i] != ' '){
                if(key[i] < 65 || (key[i] > 90 && key[i] < 97) || key[i] > 122){
                    return NULL;
                }
            }
        }

        int key_index = 0;
        int letter = 0;
        char matrix[5][5]; // matrix
        char alphabet_used[25] = {0};   

        // napln matrix key
        int alphabet_used_index = 0;
        while(key[key_index] != '\0'){
            if(isalpha(key[key_index])){ // addition
                if( toupper(key[key_index]) == 'W'){
                    if( strchr( alphabet_used,'V') == NULL ){
                            alphabet_used[alphabet_used_index] = 'V';
                            alphabet_used_index++;
                        }
                    }else if( strchr( alphabet_used,toupper(key[key_index]) ) == NULL){
                        alphabet_used[alphabet_used_index] = toupper(key[key_index]);
                        alphabet_used_index++;
                    }
                }
                key_index++;
            }

            // napln matrix ostatnym
            while(alphabet_used_index < 25){
                // W removal
                if( letter + 65 == 'W'){
                    letter++;
                }

                if( strchr( alphabet_used,letter+65) == NULL ){
                    alphabet_used[alphabet_used_index] = letter + 65;
                    alphabet_used_index++;
                }
                letter++;
            }

            alphabet_used_index = 0;
            // napln matrix
            for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    matrix[i][j] = alphabet_used[alphabet_used_index];
                    alphabet_used_index++;
                }
            }
            
            // previest text na ready-to-encrypt text
            int count_letters = 0;
            for(int i = 0; i < strlen(text); i++){
                if(isalpha(text[i])){
                    count_letters++;
                }
            }

            // ready-to-encrypt copy
            int text_index = 0;
            int ready_to_encrypt_index = 0;
            char* ready_to_encrypt = (char*)calloc(count_letters+1,sizeof(char));
            //ready_to_encrypt[count_letters-1] = '\0';
            while(text[text_index] != '\0'){
                if(isalpha(text[text_index])){
                    if(toupper(text[text_index]) == 'W'){
                        //printf("\ndvojite W\n");
                        ready_to_encrypt[ready_to_encrypt_index] = 'V';
                        ready_to_encrypt_index++;
                    }else{
                        ready_to_encrypt[ready_to_encrypt_index] = toupper(text[text_index]);
                        ready_to_encrypt_index++;
                    }
                }
                text_index++;
            }

            // ready-to-encrypt X-s
            text_index = 0;
            ready_to_encrypt_index = 0;
            char* ready_to_encrypt_with_x = (char*)calloc((count_letters*2)+1,sizeof(char));
            int ready_to_encrypt_with_x_index = 0;
            int i = 0;

            for( i = 0; i < (count_letters); i++){
                if( (ready_to_encrypt[i+1] != '\0' && ready_to_encrypt[i] == ready_to_encrypt[i+1] && ready_to_encrypt[i] != 'X' && i % 2 == 0 )){
                    // duplicitne znaky
                    ready_to_encrypt_with_x[ready_to_encrypt_with_x_index] = ready_to_encrypt[i];
                    ready_to_encrypt_with_x_index++;
                    ready_to_encrypt_with_x[ready_to_encrypt_with_x_index] = 'X';
                    ready_to_encrypt_with_x_index++;
                    ready_to_encrypt_with_x[ready_to_encrypt_with_x_index] = ready_to_encrypt[i+1];

                }else{ 
                    // neduplicitne znaky
                    ready_to_encrypt_with_x[ready_to_encrypt_with_x_index] = ready_to_encrypt[i];
                    ready_to_encrypt_with_x_index++;
                }
            }

            //ready_to_encrypt_with_x[ready_to_encrypt_with_x_index] = '\0';

            if(ready_to_encrypt_with_x_index % 2 != 0){
                ready_to_encrypt_with_x[ready_to_encrypt_with_x_index] = 'X';
                ready_to_encrypt_with_x_index++;
            }

            //ready_to_encrypt_with_x = (char*)realloc(ready_to_encrypt_with_x,ready_to_encrypt_with_x_index);
            //ready_to_encrypt_with_x[ready_to_encrypt_with_x_index-1] = '\0';
            
            // sifrovanie
            int first_x;
            int first_y;
            int second_x;
            int second_y;
            char* encrypted = (char*)calloc(ready_to_encrypt_with_x_index,sizeof(char)); // final output
            //encrypted[ready_to_encrypt_with_x_index-1] = '\0';

            for(int i = 0; i < (ready_to_encrypt_with_x_index); i = i + 2){
                // najdi first a second position
                for(int q = 0; q < 5; q++){
                    for(int t = 0; t < 5; t++){
                        if(ready_to_encrypt_with_x[i] == matrix[q][t]){
                            first_x = t;
                            first_y = q;
                        }

                        if(ready_to_encrypt_with_x[i+1] == matrix[q][t]){
                            second_x = t;
                            second_y = q;
                        }
                    }
                }

                // matematicke parametre
                    // rovnaky riadok
                if(first_y == second_y){          
                    // first
                    if(first_x == 4){
                        encrypted[i] = matrix[first_y][0];
                    }else{
                        encrypted[i] = matrix[first_y][first_x+1];
                    }

                    // second
                    if(second_x == 4){
                        encrypted[i+1] = matrix[second_y][0];
                    }else{
                        encrypted[i+1] = matrix[second_y][second_x+1];
                    }
                }

                    // stlpec
                if(first_x == second_x){
                    // first
                    if(first_y == 4){
                        encrypted[i] = matrix[0][first_x];
                    }else{
                        encrypted[i] = matrix[first_y+1][first_x];
                    }

                    // second
                    if(second_y == 4){
                        encrypted[i+1] = matrix[0][second_x];
                    }else{
                        encrypted[i+1] = matrix[second_y+1][second_x];
                    }
                }

                    // piresecniki
                if(first_x != second_x && first_y != second_y){
                    encrypted[i] = matrix[first_y][second_x];
                    encrypted[i+1] = matrix[second_y][first_x];
                }
            }

            char* final_encrypted = (char*)calloc(ready_to_encrypt_with_x_index+(ready_to_encrypt_with_x_index/2),sizeof(char));
            //final_encrypted[ready_to_encrypt_with_x_index+(ready_to_encrypt_with_x_index/2)-1] = '\0';

            int add_space = 0;
            int final_encrypted_index = 0;
            for(int i = 0; i < ready_to_encrypt_with_x_index; i++){
                if(add_space == 2){
                    final_encrypted[final_encrypted_index] = ' ';
                    final_encrypted_index++;
                    add_space = 0;
                }
                final_encrypted[final_encrypted_index] = encrypted[i];
                add_space++;
                final_encrypted_index++;
            }
            
            free(ready_to_encrypt);
            free(ready_to_encrypt_with_x);
            free(encrypted);

            return final_encrypted;
        }
            // 1/2
        char* playfair_decrypt(const char* key, const char* text){
            // empty
            if(key == NULL || text == NULL){
                return NULL;
            }   
        
            // check key
            for(int i = 0;i < strlen(key); i++){
                if(key[i] != ' '){
                    if(key[i] < 65 || (key[i] > 90 && key[i] < 97) || key[i] > 122){
                        return NULL;
                    }
                }
            }
            
            int ukonc_to = 1;
            // kluc same medzery
            for(int i = 0; i < strlen(key); i++){
                //int ukonc_to = 1;
                if(key[i] != ' '){
                    ukonc_to = 0;
                }
            }
            if(ukonc_to == 1){
                return NULL;
            }

            // modifiable text
            // if text bude aj s medzerami
            int entry_text_modified_index = 0;
            char* entry_text_modified = (char*)calloc(strlen(text)+1,sizeof(char));
            for(int i = 0; i < strlen(text); i++){
                if(text[i] == 'W' || text[i] == 'w'){
                    free(entry_text_modified);
                    return NULL;
                }

                if(text[i] != ' '){
                    entry_text_modified[entry_text_modified_index] = text[i];
                    entry_text_modified_index++;
                }
            }
            //entry_text_modified[strlen(text)] = '\0';

        // MATRIX FILL UP
        int key_index = 0;
        int letter = 0;
        char matrix[5][5]; // matrix
        char alphabet_used[25] = {0};

        // napln matrix key
        int alphabet_used_index = 0;
        while(key[key_index] != '\0'){
            if(isalpha(key[key_index])){ // addition
                if( toupper(key[key_index]) == 'W'){
                    if( strchr( alphabet_used,'V') == NULL ){
                        alphabet_used[alphabet_used_index] = 'V';
                        alphabet_used_index++;
                    }
                }else if( strchr( alphabet_used,toupper(key[key_index]) ) == NULL){
                    alphabet_used[alphabet_used_index] = toupper(key[key_index]);
                    alphabet_used_index++;
                }
            }
            key_index++;
        }

        // napln matrix ostatnym
        while(alphabet_used_index < 25){
            // W removal
            if( letter + 65 == 'W'){
                letter++;
            }

            if( strchr( alphabet_used,letter+65) == NULL ){
                alphabet_used[alphabet_used_index] = letter + 65;
                alphabet_used_index++;
            }
            letter++;
        }

        alphabet_used_index = 0;
        // napln matrix
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                matrix[i][j] = alphabet_used[alphabet_used_index];
                alphabet_used_index++;
            }
        }

        int ready_to_encrypt_with_x_index = strlen(entry_text_modified);
        int first_x,first_y,second_x,second_y;
        char* encrypted = (char*)calloc(strlen(entry_text_modified)+1,sizeof(char));

    for(int i = 0; i < (ready_to_encrypt_with_x_index); i = i + 2){
        // najdi first a second position
        for(int q = 0; q < 5; q++){
            for(int t = 0; t < 5; t++){
                if(entry_text_modified[i] == matrix[q][t]){
                    first_x = t;
                    first_y = q;
                }

                if(entry_text_modified[i+1] == matrix[q][t]){
                    second_x = t;
                    second_y = q;
                }
            }
        }

        // matematicke parametre
            // rovnaky riadok
        if(first_y == second_y){          
            // first
            if(first_x == 0){
                encrypted[i] = matrix[first_y][4];
            }else{
                encrypted[i] = matrix[first_y][first_x-1];
            }

            // second
            if(second_x == 0){
                encrypted[i+1] = matrix[second_y][4];
            }else{
                encrypted[i+1] = matrix[second_y][second_x-1];
            }
        }

            // stlpec
        if(first_x == second_x){
            // first
            if(first_y == 0){
                encrypted[i] = matrix[4][first_x];
            }else{
                encrypted[i] = matrix[first_y-1][first_x];
            }

            // second
            if(second_y == 0){
                encrypted[i+1] = matrix[4][second_x];
            }else{
                encrypted[i+1] = matrix[second_y-1][second_x];
            }
        }

            // piresecniki
        if(first_x != second_x && first_y != second_y){
            // first & second
            encrypted[i] = matrix[first_y][second_x];
            encrypted[i+1] = matrix[second_y][first_x];
        }
    }
    //encrypted[strlen(entry_text_modified)] = '\0';
    free(entry_text_modified);   

    return encrypted;
}
