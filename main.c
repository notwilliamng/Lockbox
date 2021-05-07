#include "msp.h"
#include "LCD.h"
#include "keypad.h"
#include "delay.h"

/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    LCD_init();
    keypad_init();
    int i = 0;
    unsigned char program = 0;
    unsigned char key= keypad_getkey();
    typedef enum {
        locked,
        unlocked,
        set_key
    } state;
    state current_state;
    unsigned char password[4];
    unsigned char attempt[4];
    current_state = set_key;
    while(1){
        switch(current_state){
            case locked :
                LCD_command(CLR_DISP); // clear screen
                LCD_command(0x80|0x00);//set cursor top left
                LCD_write_word("Locked");
                LCD_command(SET_CURSOR | 0x40); // Move cursor to 2nd line
                LCD_write_word("Enter Key:"); // when using string/char * use "" instead of ''

                while(key == 13){key = keypad_getkey();} //wait for button to be pressed
                attempt[0]= key;
                LCD_write(key + 0x30); //changes char to ASCII character for number
                while(key!=13){// wait for button to be released
                     delay_ms(1);
                     key=keypad_getkey();
                 }

                while(key == 13){key = keypad_getkey();}//wait for button press 2
                attempt[1] =key;
                LCD_write(key + 0x30); // writes number to LCD
                while(key!=13){// wait for button to be released
                     delay_ms(1);
                     key=keypad_getkey();
                 }

                while(key == 13){key = keypad_getkey();}//wait for button press 3
                attempt[2]=key;
                LCD_write(key + 0x30); // writes number to LCD
                while(key!=13){// wait for button to be released
                     delay_ms(1);
                     key=keypad_getkey();
                 }

                while(key == 13){key = keypad_getkey();}//wait for button press 4
                attempt[3]= key;
                LCD_write(key + 0x30); // writes number to LCD
                while(key!=13){// wait for button to be released
                     delay_ms(1);
                     key=keypad_getkey();
                 }

                current_state = unlocked;

                 for (i = 0; i <= 3; i++) {
                    if (attempt[i] != password[i]) {
                        current_state = locked;
                        break;
                    }
                }


            break;


            case unlocked:
                LCD_command(CLR_DISP);  // clear screen
                LCD_command(0x80|0x00);//set cursor top left
                LCD_write_word("Unlocked");
                LCD_command(SET_CURSOR | 0x40); // Move cursor to 2nd line
                LCD_write_word("Set Key? Press *"); // when using string/char * use "" instead of ''
                while(key == 13){key = keypad_getkey();} //wait for button to be pressed
                program = key;
                LCD_write(key + 0x30); //changes char to ASCII character for number
                while(key!=13){// wait for button to be released
                     delay_ms(1);
                     key=keypad_getkey();
                 }

                if(program == 10){  // the sTarrrr *
                    current_state = set_key;
                }
                else{
                    current_state = locked;
                }

                break;

            case set_key:
                LCD_command(CLR_DISP);                  // clear screen
                LCD_command(0x80|0x00);//set cursor top left
                LCD_write_word("Set Key");
                LCD_command(SET_CURSOR | 0x40); // Move cursor to 2nd line
                LCD_write_word("Enter Key:"); // when using string/char * use "" instead of ''

                while(key == 13){key = keypad_getkey();} //wait for button to be pressed
                password[0] = key;
                LCD_write(key + 0x30); //changes char to ASCII character for number
                while(key!=13){// wait for button to be released
                     delay_ms(1);
                     key=keypad_getkey();
                 }

                while(key == 13){key = keypad_getkey();}//wait for button press 2
                password[1] = key;
                LCD_write(key + 0x30); // writes number to LCD
                while(key!=13){// wait for button to be released
                     delay_ms(1);
                     key=keypad_getkey();
                 }

                while(key == 13){key = keypad_getkey();}//wait for button press 3
                password[2] = key;
                LCD_write(key + 0x30); // writes number to LCD
                while(key!=13){// wait for button to be released
                     delay_ms(1);
                     key=keypad_getkey();
                 }

                while(key == 13){key = keypad_getkey();}//wait for button press 4
                password[3] = key;
                LCD_write(key + 0x30); // writes number to LCD
                while(key!=13){// wait for button to be released
                     delay_ms(1);
                     key=keypad_getkey();
                 }

                current_state = locked;
            break;

            default: current_state = locked;

            }//switch
    }//while

}//main


