/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siligh <siligh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:06:10 by siligh            #+#    #+#             */
/*   Updated: 2026/04/25 21:30:04 by siligh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void uart_init(void)
{
    UBRR0L = 16; // Writing UBRRnL will trigger an immediate update of the baud rate prescaler (20.11.5)
    
    UCSR0A |= (1 << U2X0); //Double the USART Transmission Speed (20.11.2)
    
    UCSR0B |= (1 << TXEN0); //enable transmitter (20.11.3)
    
    UCSR0C &= ~(1 << UPM01);
    UCSR0C &= ~(1 << UPM00); // pas de parite

    UCSR0C &= ~(1 << USBS0); // Stop Bit = 1bit

    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); //On code l'info sur 8bit
    
}

void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0))); //(20.11.1)
    UDR0 = c;
}

void uart_printstr(const char *str)
{
    int i = 0;
    while(str[i])
    {
        uart_tx(str[i++]);
    }
}

void timer1_init()
{
	TCNT1 = 0; // Initialize timer1 counter to 0
	TCCR1A = 0; // Normal mode
	TCCR1B |= (1 << CS12) | (1 << WGM12); // Set the prescaler to 256 and enable CTC mode
	OCR1A = 62500; // Set the compare match value for a 1 second interrupt rate (16 000 000 / 256 = 62 500)

	TIMSK1 |= (1 << OCIE1A); // Enable interrupt for timer 1
}

void __vector_11(void) __attribute__((signal, used, externally_visible));
void __vector_11(void)
{
    uart_printstr("Hello World!\r\n");
}



int main(void)
{
    uart_init();
    timer1_init();
    // Active le bit I du SREG, interruptions globales ON (7.3.1)
    SREG |= (1 << 7);
    
    while(1)
    {} 
}