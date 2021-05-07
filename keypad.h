/*
 * keypad.h
 *
 *  Created on: Apr 19, 2021
 *      Author: William
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define col_mask (BIT5|BIT6|BIT7)
#define row_mask (BIT0|BIT1|BIT2|BIT3)

void keypad_init(void);
unsigned char keypad_getkey(void);

#endif /* KEYPAD_H_ */
