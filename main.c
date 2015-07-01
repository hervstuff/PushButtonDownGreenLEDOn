#include <msp430.h> 

/*
 * main.c
 */
main(void) {

    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    P1DIR &= ~0x08;  // Port 1 P1.3 (push button) as input, 0 is input
    P1DIR |= 0x41;   // Port P1.6 (LED) to output direction, 1 is output 0x40 0x41
    P1REN |= 0x08;   // Enable Port 1 P1.3 (push button) pull-up resistor
    P1SEL &= ~0x08;  // Select Port 1 P1.3 (push button), 0 selects
    //P1OUT &= ~0x40;  // Set the LED off

    //P1OUT |= 0x01;   // Set the red LED on

    P1OUT = 0xBF;  // Set green led off and red led on

    while(1){

    	if((P1IN & 0x08)== 0){  // Push button down when bit 3 == 0

    		P1OUT |= 0x40;  // Set LED on when button down |= 0x40
    		P1OUT &= 0xFE;
    	}
    	else{

    		//P1OUT &= ~0x40;  // Set LED off when button off
    		P1OUT = 0xBF;
    	}
    }
	
}
