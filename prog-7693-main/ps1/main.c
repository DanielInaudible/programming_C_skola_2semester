#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
// user defined library
#include "bmp.h"
#include "playfair.h"

int main(){
    
    // 1
    char* a = playfair_encrypt("af", "Ach poveda ci vam je nedobre doma ze sa chcete do sveta pustat");
    if(a){
        printf("PLAYFAIR ENCRYPTED : %s\n",a);
    }
    
    if(a){
        char* b = playfair_decrypt("Hostinsky prehral stavku a suhajovi dobre padlo co mu kralova dcera poslala",a);
        if(b){
            printf("PLAYFAIR DECRYPTED : %s\n",b);
            free(b);
        }
        free(a);
    }
    
    
     
    // 2
    char* reversed = reverse("!aaa23oimrpiom1#f!");
    if(reversed){
        printf("REVERSED ENCRYPTED : %s\n", reversed);
        free(reversed);
    }
    
    
    // 3
    char* encrypted = vigenere_encrypt("CoMPuTeR", "Hello world!");
    if(encrypted){
        printf("VIGENERE ENCRYPT : %s\n", encrypted);
    }
    if(encrypted){
        char* decrypted = vigenere_decrypt("Computer",encrypted);
        if(decrypted){
            printf("VIGENERE DECRYPT : %s\n", decrypted);
            free(decrypted);
        }
        free(encrypted);
    }
   
    

    // 4
    unsigned char* encrypted_a = bit_encrypt("Hello World!");
    if(encrypted_a){
        printf("BIT ENCRYPT : ");
        for(int i=0; i < 12;i++) {
            printf("%x ", encrypted_a[i]);
            //80 9c 95 95 96 11 bc 96 b9 95 9d 10
        }
        printf("\n");
        free(encrypted_a);
    }

    char* temp_2 = "";
    const unsigned char* temp = (unsigned char*)temp_2;
    
    char* decrypted_a = bit_decrypt(temp);
    if(decrypted_a){
        printf("BIT DECRYPT : %s\n",decrypted_a);
    }
    free(decrypted_a);

    // 5
    
    unsigned char* encrypted_b = bmp_encrypt("hello","hello world!");
    if(encrypted_b){
        printf("BMP ENCRYPT : ");
        for(int i=0; i < 12;i++) {
            printf("%x ", encrypted_b[i]);
        }
        printf("\n");
    }

    
    if(encrypted_b){
        char* decrypted_b = bmp_decrypt("hello",encrypted_b);
        if(decrypted_b){
            printf("BMP DECRYPTED : %s",decrypted_b);
            printf("\n");
            free(decrypted_b);
        }
        free(encrypted_b);
    }
    
    
    return 0;
}
