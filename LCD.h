#ifndef LCD_H_
#define LCD_H_


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

void LCD_init(void);
void LCD_command(unsigned char command);
void LCD_write(unsigned char letter);
void LCD_write_word(char* string);


#endif /* LCD_H_ */
