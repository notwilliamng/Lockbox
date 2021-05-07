#include "LCD.h"
#include "msp.h"
#include "delay.h"
#include <string.h> // indicates built in library by C: <>

#define RS BIT5     /* P3.5 mask */
#define RW BIT6     /* P3.6 mask */
#define EN BIT7     /* P3.7 mask */

// Define common LCD command functions
#define CLR_DISP      0x01    // Clear display
#define HOME          0x02    // Send cursor to home position
#define MODE_4_BIT    0x20    // LCD Mode options, if we make 0x20 it can be 4 bit
#define MODE_2_LINE   0x28
#define CURSOR_ON     0x0A    // 1010 for Table of commands DCB, display on/off controls
#define CURSOR_BLINK  0x09    // 1001
#define DISPLAY_ON    0x0C    // 1100
#define CURSOR_RIGHT  0x06    // Cursor moves to right
#define CURSOR_LEFT   0x04    // Cursor moves to left
#define SET_CURSOR    0x80    // Set cursor position to SET_CURSOR | ADDRESS


// Function to initialize the LCD display
// 4-bit mode, 2 line, cursor on
void LCD_init(void) {

    // Setup GPIO for P3 and P4 to use LCD
    P3->SEL0 &= ~(RS | RW | EN);
    P3->SEL1 &= ~(RS | RW | EN);
    P4->SEL0 = 0x00;
    P4->SEL1 = 0x00;
    P3->DIR |= RS | RW | EN; // make P3 pins output for control
    P4->DIR = 0xFF;          // make P4 pins output for data

    P3->OUT &- ~EN;           // Set Enable low
    delay_ms(50);             // wait >40 ms for LCD to power up

    LCD_command(MODE_4_BIT | MODE_2_LINE);  // wake up initialization
    LCD_command(MODE_4_BIT | MODE_2_LINE);  // set 4-bit data, 2-line
    LCD_command(DISPLAY_ON | CURSOR_ON);    // display and cursor on
    LCD_command(CLR_DISP);                  // clear screen
    LCD_command(CURSOR_RIGHT);              // move cursor right after each char
}

// Function to send a single command to the LCD in 4-bit mode
void LCD_command(unsigned char command) {
    P3->OUT &= ~(RS | RW);  // RS = 0, RW = 0
    P4->OUT = (command & 0xF0);      // put upper 4b of command on data bus

    P3->OUT |= EN;          // Pulse E for > 460 ns
    delay_us(0);
    P3->OUT &= ~EN;         //sends the data

    P4->OUT = ((command & 0x0F)<<4);      // put lower 4b of command on data bus

    P3->OUT |= EN;          // Pulse E for > 460 ns
    delay_us(0);
    P3->OUT &= ~EN;         //sends the data

    if (command < 4)
        delay_ms(2);         // command 1 and 2 need up to 1.52ms
    else
        delay_us(40);       // all others 37 us
}

// Function to write a single character at the cursor location
void LCD_write(unsigned char letter) {
    P3->OUT |= RS;        // RS = 1
    P3->OUT &= ~RW;       // R/W = 0
    P4->OUT = (letter & 0xF0);     // put letter upper bit on bus
    P3->OUT |= EN;        // pulse E > 460 ns
    delay_us(0);
    P3->OUT &= ~EN;

    P4->OUT = ((letter & 0x0F)<<4);     // put letter lower bit on bus
    P3->OUT |= EN;        // pulse E > 460 ns
    delay_us(0);
    P3->OUT &= ~EN;

    delay_us(2);           // wait for LCD to display
}


void LCD_write_word(char* string) {
    int x = strlen(string);
    int i;
    for(i=0; i<x; i++){
        LCD_write(string[i]);
    };
}
