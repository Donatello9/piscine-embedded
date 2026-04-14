/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siligh <siligh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:51:15 by siligh            #+#    #+#             */
/*   Updated: 2026/04/14 17:55:52 by siligh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>

// 14.2.2 DATASHEET


void which_led(int value)
{
    PORTB = 0;
    if (value & (1 << 0)) // if bit 0 de value
        PORTB |= (1 << PB0); // allume
    if (value & (1 << 1))
        PORTB |= (1 << PB1);
    if (value & (1 << 2))
        PORTB |= (1 << PB2);
    if (value & (1 << 3))
        PORTB |= (1 << PB4);
}
int main(void)
{
    int value;
    
    DDRD &= ~(1 << PD2); // PD2 en entrée (bouton)
    PORTD |= (1 << PD2);// Pull-up activée
    
    DDRD &= ~(1 << PD4); // PD4 en entrée (bouton)
    PORTD |= (1 << PD4);// Pull-up activée
    
    DDRB |= (1 << PB0);
    DDRB |= (1 << PB1);
    DDRB |= (1 << PB2);
    DDRB |= (1 << PB4);
    PORTB = 0;
    
    value = 0;
    while (1)
    {
        if (!(PIND & (1 << PD2))) // if push 
        {
            _delay_ms(50);
            if ((PIND & (1 << PD2)) && (value < 15)) // if release
            {
                value++;
                which_led(value); 
            }
                
        }

        if (!(PIND & (1 << PD4))) // if push 
        {
            _delay_ms(50);
            if ((PIND & (1 << PD4)) && (value > 0)) // if release
            {
                value--;
                which_led(value);
            }
        }

    }
    
    return 0;
}
