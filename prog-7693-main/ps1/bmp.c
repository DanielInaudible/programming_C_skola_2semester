#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// 2
char* reverse(const char* text){
    // text is null
    if(!text){
        return NULL;
    }


    char* reversed = (char*)calloc(strlen(text)+1,sizeof(1));
    //reversed[strlen(text)] = '\0';
    for(int i = 0; i < strlen(text); i++){
        // fix to-upper, and other
        if( isalpha(text[strlen(text)-1-i]) ){
            reversed[i] = toupper(text[strlen(text)-1-i]);
        }else{
            reversed[i] = text[strlen(text)-1-i];
        }
    }

    return reversed;
}

// 3
//  3/1
char* vigenere_encrypt(const char* key, const char* text){
    // empty
    if(key == NULL || text == NULL){
        return NULL;
    }

    char* encrypted = (char*)calloc(strlen(text)+1,sizeof(char));
    
    int key_length = strlen(key);
    int key_index = 0;
    for(int i = 0; i < strlen(text); i++){
        if(key_index >= key_length){
            key_index = 0;
        }
        // kluc nieje pismeno
        if(key[key_index] < 65 || (key[key_index] > 90 && key[key_index] < 97) || key[key_index] > 122){
            free(encrypted);
            return NULL;
        }


        if( isalpha(text[i]) && isalpha(key[key_index]) ){
                encrypted[i] = toupper(text[i]) + ( toupper(key[key_index]) - 65 );
            if(encrypted[i] > 90){
                encrypted[i] = (encrypted[i]-90) + 64;
            }
            key_index++;
        }else{
            encrypted[i] = text[i];
        }
    }

    return encrypted;
}

// 3/2
char* vigenere_decrypt(const char* key, const char* text){
    // empty
    if(key == NULL || text == NULL){
        return NULL;
    }

    char* decrypted = (char*)calloc(strlen(text)+1,sizeof(char));
    int key_length = strlen(key);
    int key_index = 0;
    for(int i = 0; i < strlen(text); i++){
        
        if(key_index >= key_length){
            key_index = 0;
        }

        // invalid key value
        if(key[key_index] < 65 || (key[key_index] > 90 && key[key_index] < 97) || key[key_index] > 122){
            free(decrypted);
            return NULL;
        }

        if( isalpha(text[i]) && isalpha(key[key_index]) ){
            decrypted[i] = toupper(text[i]) - ( toupper(key[key_index]) - 65 );
            if(decrypted[i] < 65){
                decrypted[i] = (decrypted[i]+90) - 64;
            }
            key_index++;
        }else{
            decrypted[i] = text[i];
        }
    }

    return decrypted;
}

// 4
//  4/1
unsigned char* bit_encrypt(const char* text){
    // empty
    if(text == NULL){
        return NULL;
    }

    unsigned char* encrypted = (unsigned char*)calloc(strlen(text)+1,sizeof(unsigned char));
    //encrypted[strlen(text)] = '\0';

    for(int i = 0; i < strlen(text); i++){
        encrypted[i] = text[i];
        // 8 & 7
        if (((encrypted[i] & (1 << 7)) >> 7) ^ ((encrypted[i] & (1 << 6)) >> 6))
        {
            encrypted[i] ^= 1 << 7;
            encrypted[i] ^= 1 << 6;
        }

        // 6 & 5
        if (((encrypted[i] & (1 << 5)) >> 5) ^ ((encrypted[i] & (1 << 4)) >> 4))
        {
            encrypted[i] ^= 1 << 5;
            encrypted[i] ^= 1 << 4;
        }

        //printf("\nVysledok swapnutia cisla %d = %d",text[i],encrypted[i]);
        int first = (encrypted[i] & 240);
        int second = ( (encrypted[i] >> 4) ^ (encrypted[i]&15) );

        //printf("\nfirst half = %d",first);
        //printf("\nencrypted[i] >> 4 = %d", (encrypted[i] >> 4)  );
        //printf("\nencrypted >> 4 a XOR = %d",( (encrypted[i] >> 4) ^ (encrypted[i]&15) ) );

        encrypted[i] = first+second;
    }
    return encrypted;
}

//  4/2
char* bit_decrypt(const unsigned char* text){
    // empty
    // text != ""
    if(text==NULL || text[0] == '\0'){
        return NULL;
    }

    int total_length = strlen((char*)text)+1;
    
    char* encrypted = (char*)calloc(total_length,sizeof(char));
    //encrypted[total_length] = '\0';

    int first = 0;
    int second = 0;
    //int temp = 0;

    for(int i = 0; i < total_length; i++){
        first = text[i] >> 4;
        second = text[i] & 15;
        encrypted[i] = text[i] & 240;

        // 7 & 6
        if (((encrypted[i] & (1 << 7)) >> 7) ^ ((encrypted[i] & (1 << 6)) >> 6))
        {
            encrypted[i] ^= 1 << 7;
            encrypted[i] ^= 1 << 6;
        }

        // 5 & 4
        if (((encrypted[i] & (1 << 5)) >> 5) ^ ((encrypted[i] & (1 << 4)) >> 4))
        {
            encrypted[i] ^= 1 << 5;
            encrypted[i] ^= 1 << 4;
        }
        encrypted[i] = encrypted[i] + (first^second);
    }
    return encrypted;
}

// 5
//  5/1
unsigned char* bmp_encrypt(const char* key, const char* text){
    // empty
    if(key == NULL || text == NULL){
        return NULL;
    }
    
    // check key
    for(int i = 0; i < strlen(key); i++){
        if(key[i] < 65 || (key[i] > 90 && key[i] < 97) || key[i] > 122){
            return NULL;
        }
    }

    char* reversed = reverse(text);
    char* encrypted = vigenere_encrypt(key,reversed);
    unsigned char* encrypted_bit = bit_encrypt(encrypted);
    free(reversed);
    free(encrypted);

    return encrypted_bit;
}

//  5/2
char* bmp_decrypt(const char* key, const unsigned char* text){
    // empty
    if(key == NULL || text == NULL){
        return NULL;
    }
    
    // check key
    for(int i = 0; i < strlen(key); i++){
        if(key[i] < 65 || (key[i] > 90 && key[i] < 97) || key[i] > 122){
            return NULL;
        }
    }


    char* decrypted_bit = bit_decrypt(text);
    char* decrypted = vigenere_decrypt(key,decrypted_bit);
    char* normal = reverse(decrypted);
    
    free(decrypted_bit);
    free(decrypted);


    return normal;
}
