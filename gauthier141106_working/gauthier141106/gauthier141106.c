/*
 * gauthier141106.c
 *
 * Created: 06.11.2014 19:32:40
 * Author: 25mmHg
 * 
 *
 *  .----------------------------------o---o--o--o-------o--------Vcc5V red
 *  |                                  |   |  |  |       |
 *  |          DB25E_15 black          |  .-..-..-.      |
 *  |          |           .------.    |  | || || |      |
 *  |          |  ___      |RST 5V|    |  | || || |      |
 *  '--o-------)-|___|-----o      o----'  '-''-''-'      |
 *     |       |  ___      |D0 SCL|        |  |  |       |   ___
 *     |    _  '-|___|-----o      o--------)--)--)-------)--|___|-DIRXX_2 white
 *     |   | |    ___      |D1MISO|        |  |  |       |   ___
 *  .--)--|| ||--|___|-----o      o--------)--)--)-------)--|___|-DB25X_3 gray
 *  |  |   |_|             |A1MOSI|        |  |  |       |   ___
 *  |  |                ---o      o--------)--)--)-------)--|___|-DIRYY_4 pink
 *  |  |                   |A0  B4|        |  |  |       |   ___
 *  |  |                ---o      o--------)--)--)-------)--|___|-DB25Y_5 brown
 *  |  |  XMLED   ___      |D2  B3|        |  |  |       |   ___
 *  o--)----|<---|___|--rt-o      o--------)--)--)-------)--|___|-DIRZZ_6 yellow
 *  |  |  YMLED   ___      |D3  B2|        |  |  |       |   ___
 *  o--)----|<---|___|---2-o      o--------)--)--)-------)--|___|-DB25Z_7 violet
 *  |  |  ZMLED   ___      |D4  B1|        |  |  |       |
 *  o--)----|<---|___|---3-o      o---gr---o  |  |       |
 *  |  |  STLED   ___      |D5  B0|        |  |  |      ---
 *  o--)----|<---|___|---4-o      o---br---)--o  |      ---
 *  |  |                   |GND D6|        |  |  |       |
 *  |  |               .-5-o      o---vi---)--)--o       |
 *  |  |               |   |at2313|        |  |  |       |
 *  |  |               |   '------'        |  |  |       |
 *  |  |               |                   |  |  |       |
 *  |  o |             |                 |/ |/ |/        |
 *  |    |=|           |                 |  |  |         |
 *  |  o |             |                 |> |> |>        |
 *  |  |               |                   |  |  |       |
 *  |  |               |                   |  |  |       |
 *  '--o---------------o-------------------o--o--o-------o--------GND blue/green
 *
 *
 *(created by AACircuit v1.28.6 beta 04/19/05 www.tech-chat.de)
 *
 */ 

//MAKROS
#define F_CPU 5922000UL
#define XTH 10
#define YTH 24
#define ZTH 10

#define DIRXX (1<<PB7)
#define DB25X (1<<PB6)
#define DIRYY (1<<PB5)
#define DB25Y (1<<PB4)
#define DIRZZ (1<<PB3)
#define DB25Z (1<<PB2)
#define PHOTX (1<<PB1)
#define PHOTY (1<<PB0)

#define ESTOP (1<<PD0)
#define XMLED (1<<PD2)
#define YMLED (1<<PD3)
#define ZMLED (1<<PD4)
#define STLED (1<<PD5) 
#define BUZZZ (1<<PD1)
#define PHOTZ (1<<PD6)

#define ALARM 3
#define BLINK 2
#define OFF 0
#define ON 1

#include <avr/io.h>
#include <util/delay.h>

//FIRST initialisation global variables
uint8_t soll_x=0;
uint8_t soll_y=0;
uint8_t soll_z=0;

uint8_t ist_x=0;
uint8_t ist_y=0;
uint8_t ist_z=0;

int8_t cnt_x=0;
int8_t cnt_y=0;
int8_t cnt_z=0;

uint8_t move_x=0;
uint8_t move_y=0;
uint8_t move_z=0;

uint16_t rounds=0;

void estop(uint8_t state)
{
	if(state)	PORTD &= ~ESTOP;
	else 		PORTD |=  ESTOP;
}

void buzzz(uint16_t ms)
{
	for(uint16_t i=0; i<(ms<<2); i++)
	{
		PIND |= BUZZZ;
		_delay_us(250);
	}
	PORTD &= ~BUZZZ;
}

void leds(uint8_t led, uint8_t show)
{
	if(show == ON) 			PORTD |=  led;
	else if(show == OFF)	PORTD &= ~led;
	else if(show == BLINK)
	{
		PORTD |= led;
		buzzz(50);
		PORTD &= ~led;
		buzzz(50);
	}
	else if(show == ALARM)
	{	
		buzzz(50);
		_delay_ms(200);
		buzzz(250);
		_delay_ms(1320);
		PORTD |= led;
		_delay_ms(40);
		PORTD &= ~led;
		_delay_ms(100);
		PORTD |= led;
		_delay_ms(40);
		PORTD &= ~led;
	}
	else;
}

int main(void)
{
	//Initialisation Outputs
	estop(OFF); // ESTOP 
	DDRD  |=  (ESTOP | BUZZZ | XMLED | YMLED | ZMLED | STLED);
	//estop(OFF);
	PORTD &= ~(BUZZZ | XMLED | YMLED | ZMLED | STLED);
	//Initialisation PULLUPS Inputs
	DDRB  &= ~(DIRXX | DB25X | DIRYY | DB25Y | DIRZZ | DB25Z | PHOTX | PHOTY);
	PORTB |=  (DIRXX | DB25X | DIRYY | DB25Y | DIRZZ | DB25Z | PHOTX | PHOTY);
	DDRD  &= ~(PHOTZ);
	PORTD |=   PHOTZ;

	for(uint8_t i=0; i<4; i++) leds((XMLED | YMLED | ZMLED | STLED), BLINK);
	
	while(1)
	{
		//Toggle HEART (heartbeatsign for debugging)
		rounds++;
		if (!rounds) PIND |= STLED;

		//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
		// B E G I N
		//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
		if((PINB & DB25X) && !soll_x)
		{
			//LOW to HIGH on DB25X
			PORTB |= DB25X; //Pullups ON for Hysterese
			soll_x = 1;
			cnt_x  = (PINB & DIRXX)? cnt_x +1 : cnt_x -1;
		}

		else if(!(PINB & DB25X) && soll_x)
		{
			//HIGH to LOW on DB25X
			PORTB &= ~DB25X; //Pullups OFF
			soll_x = 0;
			cnt_x  = (PINB & DIRXX)? cnt_x +1 : cnt_x -1;
		}

		else
		{
			//No change on DB25X
			;
		}

		if((PINB & PHOTX) && !ist_x)
		{
			//LIGHT to DARK on PHOTX
			PORTB |= PHOTX; //Pullups ON for Hysterese
			ist_x  = 1;
			move_x++;
			leds(XMLED, OFF);
		}

		else if(!(PINB & PHOTX) && ist_x)
		{
			//DARK to LIGHT on PHOTX
			PORTB &= ~PHOTX; //Pullups OFF
			ist_x  = 0;
			move_x++;
			leds(XMLED, ON);
		}

		else
		{
			//No change on PHOTX
			;
		}

		if(move_x >= 2)
		{
			move_x = 0;
			cnt_x  = 0;
		}

		if((cnt_x > XTH) || (cnt_x < 0-XTH))
		{
			cnt_x = 0;
			estop(ON);
			//ALARM forever, restart with RESET button
			while(1)	leds(XMLED, ALARM);
		}

		//YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
		// B E G I N
		//YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
		if((PINB & DB25Y) && !soll_y)
		{
			//LOW to HIGH on DB25X
			PORTB |= DB25Y; //Pullups ON for Hysterese
			soll_y = 1;
			cnt_y  = (PINB & DIRYY)? cnt_y +1 : cnt_y -1;
		}

		else if(!(PINB & DB25Y) && soll_y)
		{
			//HIGH to LOW on DB25X
			PORTB &= ~DB25Y; //Pullups OFF
			soll_y = 0;
			cnt_y  = (PINB & DIRYY)? cnt_y +1 : cnt_y -1;
		}

		else
		{
			//No change on DB25Y
			;
		}

		if((PINB & PHOTY) && !ist_y)
		{
			//LIGHT to DARK on PHOTY
			PORTB |= PHOTY; //Pullups ON for Hysterese
			ist_y  = 1;
			move_y++;
			leds(YMLED, OFF);
		}

		else if(!(PINB & PHOTY) && ist_y)
		{
			//DARK to LIGHT on PHOTY
			PORTB &= ~PHOTY; //Pullups OFF
			ist_y  = 0;
			move_y++;
			leds(YMLED, ON);
		}

		else
		{
			//No change on PHOTX
			;
		}

		if(move_y >= 2)
		{
			move_y = 0;
			cnt_y  = 0;
		}

		if((cnt_y > YTH) || (cnt_y < 0-YTH))
		{
			cnt_y = 0;
			estop(ON);
			//ALARM forever, restart with RESET button
			while(1)	leds(YMLED, ALARM);
		}		
		
		//ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ
		// B E G I N
		//ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ
		if((PINB & DB25Z) && !soll_z)
		{
			//LOW to HIGH on DB25X
			PORTB |= DB25Z; //Pullups ON for Hysterese
			soll_z = 1;
			cnt_z  = (PINB & DIRZZ)? cnt_z +1 : cnt_z -1;
		}

		else if(!(PINB & DB25Z) && soll_z)
		{
			//HIGH to LOW on DB25X
			PORTB &= ~DB25Z; //Pullups OFF
			soll_z = 0;
			cnt_z  = (PINB & DIRZZ)? cnt_z +1 : cnt_z -1;
		}

		else
		{
			//No change on DB25Z
			;
		}

		if((PIND & PHOTZ) && !ist_z)
		{
			//LIGHT to DARK on PHOTX
			PORTD |= PHOTZ; //Pullups ON for Hysterese
			ist_z  = 1;
			move_z++;
			leds(ZMLED, OFF);
			//PIND |= BUZZZ;
		}

		else if(!(PIND & PHOTZ) && ist_z)
		{
			//DARK to LIGHT on PHOTZ
			PORTD &= ~PHOTZ; //Pullups OFF
			ist_z  = 0;
			move_z++;
			leds(ZMLED, ON);
			//PIND |= BUZZZ;
		}

		else
		{
			//No change on PHOTZ
			;
		}

		if(move_z >= 2)
		{
			move_z = 0;
			cnt_z  = 0;
		}

		if((cnt_z > ZTH) || (cnt_z < 0-ZTH))
		{
			cnt_z = 0;
			estop(ON);
			//ALARM forever, restart with RESET button
			while(1)	leds(ZMLED, ALARM);
		}
	}
}