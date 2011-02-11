/*
    Eye-Blink - Eyes for paintball loader
    Copyright (C) 2011 Wojciech Todryk (wojciech@todryk.pl)
    Copyright (C) 2011 Sławomir Bednarczyk

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

	$Id:$
*/

#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "main.h"

volatile uint8_t clock_100ms = TICKS;
volatile uint8_t clock_led = TICKS_LED;
volatile uint8_t motor_run_timer = MOTOR_RUNNING_TIME;

/** Inicjalizacja urządzeń wejścia / wyjścia.
*/
void ioinit(void) {

	OVERRIDE_DDR &= ~_BV(OVERRIDE_PIN);
	OVERRIDE_PORTOUT |= _BV(OVERRIDE_PIN);

	MOTOR_DDR |= _BV(MOTOR_PIN);
	LED_DDR |= _BV(LED_PIN);
	EYE_DDR |= _BV(EYE_PIN);

	OCR0A = TAU;                         // przy zegarze 1Mhz/1024/TAU daje nam w przybliżeniu 100ms
	TCCR0A |= _BV(WGM01);                // CTC mode
	TCCR0B |= _BV(CS02) | _BV(CS00);     // CLK/1024
	TIMSK |= _BV(OCIE0A);                // enable interrupt on OCR0A match

	ACSR |= _BV(ACBG) | _BV(ACIE);
	DIDR0 |= _BV(AIN1D);

}

/** Przerwanie na porównanie timera0
*/
ISR (TIM0_COMPA_vect) {
	if(motor_run_timer) {
		led_toggle();
	} else {
		if (!(--clock_led)) {
			clock_led = TICKS_LED;
			led_toggle();
		}
	}
	if (!(--clock_100ms)) { 				//############### minęła sekunda
    	clock_100ms = TICKS;
    	if (motor_run_timer) {
    		motor_run_timer--;
		}
	}
}

/** Przerwanie spowodowane zmianą na komparatorze analogowym
*/
ISR (ANA_COMP_vect ) {
	motor_run_timer = MOTOR_RUNNING_TIME;
}

int main(void) {

    ioinit();

    motor_on();
    eye_on();

	wdt_enable(WDTO_60MS);

    sei();

    for(;;) {

		wdt_reset();

		if (!(OVERRIDE_PORTPIN & _BV(OVERRIDE_PIN))) {
			motor_run_timer = MOTOR_RUNNING_TIME;
		}

		if (motor_run_timer) {
			motor_on();
		} else {
			motor_off();
		}

    }

    return 0;
}
