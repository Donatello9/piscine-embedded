/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siligh <siligh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:06:10 by siligh            #+#    #+#             */
/*   Updated: 2026/04/25 21:27:48 by siligh           ###   ########.fr       */
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
    UCSR0B |= (1 << RXEN0); //enable receiver (20.11.3)
    
    UCSR0C &= ~(1 << UPM01);
    UCSR0C &= ~(1 << UPM00); // pas de parite

    UCSR0C &= ~(1 << USBS0); // Stop Bit = 1bit

    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); //On code l'info sur 8bit
    
}

char    uart_rx(void)
{
    while (!(UCSR0A & (1 << RXC0)));
    return (UDR0);
}

void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0))); //(20.11.1)
    UDR0 = c;
}


void __vector_18__(void) __attribute__((signal, used));
void __vector_18__(void)
{
    char c = uart_rx();  // lit le caractère reçu
    uart_tx(c);          // le renvoie immédiatement (echo)
}

int main(void)
{
    uart_init();
    // Active le bit I du SREG, interruptions globales ON (7.3.1)
    SREG |= (1 << 7);
    
    while(1)
    {}
}