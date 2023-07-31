// LIBRARIES
#include <Adafruit_LiquidCrystal.h>
#include <stdlib.h>
#include <string.h>

// PIN DEFINITION
#define BTN_ENTER_PIN   A0 // enter
#define BTN_1_PIN       2  // number UP
#define BTN_2_PIN       3  // number UP
#define BTN_3_PIN       4  // number UP
#define BTN_4_PIN       5  // number UP

#define LED_BLUE_1      6
#define LED_RED_1       7

#define LED_BLUE_2      8
#define LED_RED_2       9

#define LED_BLUE_3      10
#define LED_RED_3       11

#define LED_BLUE_4      12
#define LED_RED_4       13

// RUN-TIME
void setup(){
  	Serial.begin(9600);
  	randomSeed(analogRead(1));

  	pinMode(LED_BLUE_1, OUTPUT);
  	pinMode(LED_RED_1, OUTPUT);
  
  	pinMode(LED_BLUE_2, OUTPUT);
  	pinMode(LED_RED_2, OUTPUT);
  
  	pinMode(LED_BLUE_3, OUTPUT);
  	pinMode(LED_RED_3, OUTPUT);
  
  	pinMode(LED_BLUE_4, OUTPUT);
  	pinMode(LED_RED_4, OUTPUT);
  
  	pinMode(BTN_ENTER_PIN, INPUT);
	pinMode(BTN_1_PIN,INPUT);
  	pinMode(BTN_2_PIN,INPUT);
  	pinMode(BTN_3_PIN,INPUT);
  	pinMode(BTN_4_PIN,INPUT);	
}

// TURN OFF LEDS
void turn_off_leds();

// RENDER LEDS
void render_leds(const int peg_a, const int peg_b);

// LCD_INITIALIZE
void lcd_init();

// LCD_CLEAR
void lcd_clear();

// LCD_SETNI_KURZOR
void lcd_set_cursor(int y, int x);

// LCD_VYPIS
void lcd_print(char *text);

// LCD_VYPIS_NA
void lcd_print_at(int y, int x, char *text);

// GENERATE CODE
char* generate_code(bool repeat, int length);

// GET_SCORE
void get_score(const char* secret, const char* guess, int* peg_a, int* peg_b);

// RENDER HISTORY
void render_history(char* secret, char** history, const int entry_nr);

// RGB MANIPULATION
void br(int blue_pin,int red_pin,int blue_value,int red_value);
Adafruit_LiquidCrystal LCD_DISPLAY(0);

void play_game(char *secret){
  	// LCD INTRODUCTION
  	lcd_init();
  	lcd_print_at(0,0,"You Are Playing");
  	lcd_print_at(1,0,"Mastermind...");
  	delay(750);
  	lcd_clear();
  
  	// HISTORY INITIALIZATION
  	char **history = (char **)calloc(11, sizeof(char *));
    for (int i = 0; i < 10; i++) {
        history[i] = (char *)calloc(5, sizeof(char));
    }
  
  	// BUTTONS INITIALIZATION
  	int num0 = 0;
  	bool edge0 = 0;
  	bool button0 = 0;
  
  	int num1 = 0;
	bool edge1 = 0;
	bool button1;

	int num2 = 0;
	bool edge2 = 0;
	bool button2;

	int num3 = 0;
	bool edge3 = 0;
	bool button3;

	int num4 = 0;
	bool edge4 = 0;
	bool button4;
  
  	lcd_print_at(1,0,"Your Guess: 0000");
  	//Adafruit_LiquidCrystal LCD_DISPLAY(0);
  
  	bool victory = false;
  	int pokusy = 0;
  	char* guess = "0000";
  	int peg_a = 0;
  	int peg_b = 0;
  	int history_max = 0;
  	int current_history =0;
  	char temp_secret[4];
  	
  	temp_secret[0] = secret[0];
  	temp_secret[1] = secret[1];
  	temp_secret[2] = secret[2];
  	temp_secret[3] = secret[3];
  
 	while((pokusy < 10) && (victory == false)){
      	if(secret == NULL || secret[0] != temp_secret[0] || secret[3] != temp_secret[3]){
          	free(secret);
          	secret = (char*)calloc(5,sizeof(char));
      		secret[0] = temp_secret[0];
  			secret[1] = temp_secret[1];
            secret[2] = temp_secret[2];
            secret[3] = temp_secret[3];
          	secret[4] = '\0';
      	}
      
      	lcd_print_at(1,12,guess);
      	Serial.print("secret = ");
      	Serial.print(secret);
      	Serial.print("\n");
      
      	Serial.print("max_history = ");
      	Serial.print(history_max);
      	Serial.print("\n");
      
      	Serial.print("current_history = ");
      	Serial.print(current_history);
      	Serial.print("\n");
  
        // BUTTON PRESSING
        button0 = digitalRead(BTN_ENTER_PIN);
      	button1 = digitalRead(BTN_1_PIN);
        button2 = digitalRead(BTN_2_PIN);
        button3 = digitalRead(BTN_3_PIN);
        button4 = digitalRead(BTN_4_PIN);
      	
        if(button1 != edge1 && edge1 == 1){
          if(num1 == 9){
            num1 = 0;
          }else{
            num1++;
          }
          guess[0] = (num1 + '0');
        }
        edge1 = button1;

        if(button2 != edge2 && edge2 == 1){
          if(num2 == 9){
            num2 = 0;
          }else{
            num2++;
          }
          guess[1] = (num2 + '0');
        }
        edge2 = button2;

        if(button3 != edge3 && edge3 == 1){
          if(num3 == 9){
            num3 = 0;
          }else{
            num3++;
          }
          guess[2] = (num3 + '0');
        }
        edge3 = button3;

        if(button4 != edge4 && edge4 == 1){
          if(num4 == 9){
            num4 = 0;
          }else{
            num4++;
          }
          guess[3] = (num4 + '0');
        }
        edge4 = button4;
      	
      	// ENTER
      	if(button0 != edge0 && edge0 == 1){
          delay(200);
          
          button0 = digitalRead(BTN_ENTER_PIN);
      	  button1 = digitalRead(BTN_1_PIN);
          button2 = digitalRead(BTN_2_PIN);
          button3 = digitalRead(BTN_3_PIN);
          button4 = digitalRead(BTN_4_PIN);
          
          // historia dozadu
          if(button2 == 1){
            Serial.print("back\n");
            if(history_max > 0){
              if(current_history == 0){
              	current_history = history_max;
              }else{
              	current_history--;
              }
            }
            get_score(secret,&history[current_history][0],&peg_a,&peg_b); //zisti skore
            render_history(secret,history,current_history);
            turn_off_leds();
            render_leds(peg_a, peg_b);
            delay(750);
            button1 = 0;
          }else if(button4 == 1){
            Serial.print("foward\n");
            if(history_max > 0){
              if(current_history == history_max){
              	current_history = 0;
              }else{
              	current_history++;
              }
            }
            get_score(secret,&history[current_history][0],&peg_a,&peg_b); //zisti skore
            render_history(secret,history,current_history);
            turn_off_leds();
            render_leds(peg_a, peg_b);
            delay(750);
            button4 = 0;
          }else{
            Serial.write("\nenter");
            pokusy++;
            history_max = pokusy-1;
            current_history = history_max;
            get_score(secret,guess,&peg_a,&peg_b);
            turn_off_leds();
            render_leds(peg_a, peg_b);
            Serial.write("\npeg_a :");
            Serial.print(peg_a);
            Serial.write("\npeg_b :");
            Serial.print(peg_b);
            memcpy(&history[history_max][0],guess,4);
            render_history(secret,history,current_history);

            num1 = 0;
            num2 = 0;
            num3 = 0;
            num4 = 0;
            guess[0] = '0';
            guess[1] = '0';
            guess[2] = '0';
            guess[3] = '0';

            if(peg_a == 4){
              victory = true;
              break;
            }
          }	
        }
        edge0 = button0;
  	}
  
  // victory screen
  if(peg_a == 4){
  	lcd_clear();
    turn_off_leds();
    lcd_print_at(0,0,"You won!");
    lcd_print_at(1,0,"Another round :)");
    //lcd_print_at(1,0,secret);
    delay(200);
  }else{ // defeat screen
  	lcd_clear();
    turn_off_leds();
    lcd_print_at(0,0,"You lost!");
    lcd_print_at(1,0,"Try again...");
    //lcd_print_at(1,0,secret);
    delay(200);
  }
  
  // release history
  for(int i = 0; i < 11; i++){
  	free(history[i]);
  }
  free(history);
}

// MAIN LOOP
void loop(){
  	
  	char* secret = generate_code(false,4);
  	Serial.print("\n");	
  	Serial.print(secret);
  	Serial.print("\n");
  
  	play_game(secret);
  
  	free(secret);
}

// TURN OFF LEDS
void turn_off_leds(){
	br(LED_BLUE_1,LED_RED_1,0,0);
  	br(LED_BLUE_2,LED_RED_2,0,0);
  	br(LED_BLUE_3,LED_RED_3,0,0);
  	br(LED_BLUE_4,LED_RED_4,0,0);
}

// RENDER LEDS
void render_leds(const int peg_a, const int peg_b){
	int nahodne = 0;
  	int counting_array[4] = {0};
  
  	// peg_a
    for(int i = 0; i < peg_a; i++){
        nahodne = random(0,4);
        if(counting_array[nahodne] != 0){
            while(counting_array[nahodne] != 0){
                nahodne = random(0,4);
            }
        }
        counting_array[nahodne]++;
      	if(nahodne == 0){
      		br(LED_BLUE_1,LED_RED_1,0,1);
      	}
      	if(nahodne == 1){
      		br(LED_BLUE_2,LED_RED_2,0,1);
      	}
      	if(nahodne == 2){
      		br(LED_BLUE_3,LED_RED_3,0,1);
      	}
      	if(nahodne == 3){
      		br(LED_BLUE_4,LED_RED_4,0,1);
        }
    }
      
    // peg_b
    for(int i = 0; i < peg_b; i++){
        nahodne = random(0,4);
        if(counting_array[nahodne] != 0){
            while(counting_array[nahodne] != 0){
                nahodne = random(0,4);
            }
        }
        counting_array[nahodne]++;
      	if(nahodne == 0){
      		br(LED_BLUE_1,LED_RED_1,1,0);
      	}
      	if(nahodne == 1){
      		br(LED_BLUE_2,LED_RED_2,1,0);
      	}
      	if(nahodne == 2){
      		br(LED_BLUE_3,LED_RED_3,1,0);
      	}
      	if(nahodne == 3){
      		br(LED_BLUE_4,LED_RED_4,1,0);
    	}
    }
}

void lcd_init() {
  LCD_DISPLAY.begin(16, 2);		// inicializuje na 2 riadky, 1 znakov
  LCD_DISPLAY.setBacklight(1);	// backlight zasvieti
}

// LCD_CLEAR
void lcd_clear() {
  LCD_DISPLAY.clear();			// clearne LCD
}

// LCD_SETNI_KURZOR
void lcd_set_cursor(int y, int x) { 
  LCD_DISPLAY.setCursor(x, y); 	// setne kurzor na LCD
}

// LCD_VYPIS
void lcd_print(char *text) {
  LCD_DISPLAY.print(text);		// printne text na LCD
}

// LCD_VYPIS_NA
void lcd_print_at(int y, int x, char *text) {
  lcd_set_cursor(y, x);	// setne kurzor na LCD poziciu
  lcd_print(text);		// printne text na LCD
}

// NON VISUAL FUNCTIONS
// GENERATE CODE
char* generate_code(bool repeat, int length){
    // too short...
    if(length < 1){
        return NULL;
    }

    // pretoze nevieme vypisat viac ako 10 cisiel od 0-9
    if(repeat == false && length > 10){
        return NULL;
    }

    // length+1 pretoze na nulty znak, a velkost 1, pretoze char ma size of 1 byte
    char *kod = (char*)calloc(length+1,sizeof(char));
    int nahodne = 0;
    int counting_array[10] = {0};

    // naplnujeme pre no-repeat
    if(repeat == true){
        for(int i = 0; i < length; i++){
            nahodne = random(0,10);
            // random + '0', v ASCII tabulke na poziciu 0 a plus int hodnota cisla, dostaneme vysledne cislo v char, velmi sikovne :)
            kod[i] = nahodne + '0';
            //printf("random = %d\n",random);
        }
        return kod;
    }

    if(repeat == false){
        for(int i = 0; i < length; i++){
            nahodne = random(0,10);
            //printf("random = %d\n",random);
            if(counting_array[nahodne] != 0){
                while(counting_array[nahodne] != 0){
                    nahodne = random(0,10);
                    //printf("OPAKUJUCI SA random = %d\n",random);
                }
            }
            counting_array[nahodne]++;
            kod[i] = nahodne + '0';
        }
        return kod;
    }

    // tu sa to nikdy nedostane...
    return NULL;
}

// GET_SCORE
void get_score(const char* secret, const char* guess, int* peg_a, int* peg_b){
    // pravidlo, length secret = length guess
    // este by sa dalo, ze v guess by sa nejak dostalo pismeno, ale nemozne pri nasom zapojeni...
    // invalid arguemnts
    // vynuluj
    *peg_a = 0;
    *peg_b = 0;
  	Serial.print("secret:");
  	Serial.print(secret);
  	Serial.print("\n");
  	Serial.print("guess:");
  	Serial.print(guess);
  	Serial.print("\n");

    int* counting_array = (int*)calloc( strlen(secret)+1 ,sizeof(int));
  	Serial.print("scanning...\n");  
    // najdi rovnake znaky
    for(int i = 0; i < strlen(secret); i++){
      	//Serial.print("i = ");
      	//Serial.print(i);
      	//Serial.print("\n");
        // rovnaka pozicia, peg_a
        if(secret[i] == guess[i]){
            *peg_a = *peg_a+1;
            counting_array[i] = 1;
        }else{
            for(int j = 0; j < strlen(secret); j++){
                //Serial.print("j = ");
      			//Serial.print(j);
      			//Serial.print("\n");
              	if( (secret[i] == guess[j]) && counting_array[j]!=1){
                    counting_array[j]++;
                    *peg_b = *peg_b+1;
                    break;
                }
            }
        }
    }
    free(counting_array);
    return;
}

// RENDER HISTORY
void render_history(char* secret, char** history, const int entry_nr){
    // podmienky
    if( secret == NULL || history == NULL || (entry_nr < 0 && entry_nr > 9) ){
        return;
    }
  	char* num = (char*)calloc(1,1);
  	*num = (entry_nr + '0');
  	lcd_print_at(0, 0, num);
  	lcd_print_at(0, 1, ".zaznam=");
  	lcd_print_at(0, 9, &history[entry_nr][0]);
  
    return;
}

// USER-DEFINED
// RGB MANIPULATION
void br(int blue_pin,int red_pin,int blue_value,int red_value)
{
  // DIGITAL NIE ANALOG !!!
  digitalWrite( red_pin, red_value);
  digitalWrite( blue_pin, blue_value);
  
  return;
}
