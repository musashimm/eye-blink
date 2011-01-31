/*
    Eye-Bink Eyes for paintball loader
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

#define STRINGIFY2(x) #x
#define STRINGIFY(x) STRINGIFY2(x)

#define GLUE(a, b)     a##b
#define PORT(x)        GLUE(PORT, x)
#define PIN(x)         GLUE(PIN, x)
#define DDR(x)         GLUE(DDR, x)
#define pin(x)         GLUE(pin, x)

#define MOTOR_PIN 4
#define MOTOR_PORT B
#define MOTOR_PORTOUT PORT(MOTOR_PORT)
#define MOTOR_DDR DDR(MOTOR_PORT)

#define	LED_PIN 3
#define LED_PORT B
#define LED_PORTOUT PORT(LED_PORT)
#define LED_DDR DDR(LED_PORT)

#define motor_on() MOTOR_PORTOUT |= _BV(MOTOR_PIN)
#define motor_off() MOTOR_PORTOUT &= ~_BV(MOTOR_PIN)
#define led_on() LED_PORTOUT |= _BV(LED_PIN)
#define led_off() LED_PORTOUT &= ~_BV(LED_PIN)

