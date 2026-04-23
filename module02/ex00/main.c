/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siligh <siligh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:06:10 by siligh            #+#    #+#             */
/*   Updated: 2026/04/23 15:16:04 by siligh           ###   ########.fr       */
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


void uart_tx(void)
{
    char c = 'Z';
    while (!(UCSR0A & (1 << UDRE0))); //(20.11.1)
    UDR0 = c;
}

int main(void)
{
    uart_init();
    while(1)
    {
        uart_tx();
        _delay_ms(1000);
    } 
}