#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

int get_sum(int number){
    int result = 0;
    while(number > 0){
        result += number % 10;
        number = number / 10;
    }

    return result;
}

int main(){
    int user_input = 0;
    int result = 0;
    scanf("%d",&user_input);
    
    do{
        result = get_sum(user_input);
        user_input = result;
    }while(result > 9);
   
    printf("%d\n",result);

    return 0;
}
