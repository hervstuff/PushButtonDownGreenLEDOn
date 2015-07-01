#include <msp430.h> 

/*
 * main.c
 */
main(void) {

    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    /*The user must setup, halt, or clear the WDT+ prior to the 32768 cycle reset interval using the DCOCLK.
     *In our case, we purposely write to WDTCTL with an incorrect password but we toggle the WDTHOLD to 1 which halts
     *the watchdog timer. The correct password requires the upper byte of WDTPW to have 05Ah. The purpose of halting
     *the watchdog timer is to save energy.
     */
    
    P1DIR &= ~0x08;  // Port 1 P1.3 (push button) as input, 0 is input
    /*P1DIR is the short form of Port 1 direction read or write register.
     *0x08 is hex for 00001000 in binary.
     *The "~"in front of "0x08" is a logical "NOT" and will invert the bits so it reads 11110111
     *The "&=" is the bitwise "AND EQUALS" and will "AND" P1DIR with what is on the right hand side of the operator.
     *1's mean write out while 0's mean read in.
     *The value 11110111 can be read from right to left with the least significant bit being Port 1.0 and the MSB being Port      *1.7.
     */
    P1DIR |= 0x40;   // Port P1.6 (LED) to output direction, 1 is output
    /*
     *Bitwise logic similar to above.
     */
    P1REN |= 0x08;   // Enable Port 1 P1.3 (push button) pull-up resistor
    /*
     *Bitwise logic.
     *But we enable the pull-up resistor because high current through the LED may burn out the LED so we use a resistor
     *to limit the current through the LED.
     */
    P1SEL &= ~0x08;  // Select Port 1 P1.3 (push button), 0 selects
    /*
     *Bitwise logic similar to above.
     */
    //P1OUT &= ~0x40;  // Set the LED off

    //P1OUT |= 0x01;   // Set the red LED on

    P1OUT = 0xBF;  // Set green led off and red led on
    /*
     *Set the inital state of the LEDs.
     */

    while(1){

    	if((P1IN & 0x08)== 0){  // Push button down when bit 3 == 0

    		P1OUT |= 0x40;  // Set LED on when button down |= 0x40
    		P1OUT &= 0xFE;
    		/*
    		 *0x40 = 01000000, Port 1.0 is LSB so Port 1.6 is where the 1 bit is located. This turns the green LED.
    		 *0xFE = 11111110. When you perform a bitwise "AND EQUALS" with P1OUT you turn off the red LED but you
    		 *leave the green LED on.
    		 */
    		
    	}
    	else{

    		//P1OUT &= ~0x40;  // Set LED off when button off
    		P1OUT = 0xBF;
    	}
    }
	
}
