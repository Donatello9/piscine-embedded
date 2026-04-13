/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siligh <siligh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:51:15 by siligh            #+#    #+#             */
/*   Updated: 2026/04/13 19:26:10 by siligh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // DATASHEET 14.2
    
    // Configure PB0 en SORTIE(WRITE)
    // DDR = Data Direction Register
    // mettre le bit PB0 à 1 = sortie
    DDRB = DDRB | (1 << PB0);

    // Met PD2 a 0 en ENTREE(READ) (inverse de 1)
    DDRD &= ~(1 << PD2);
    
    //pull-up active en mettant PD2 a 1 avant de le lire
    PORTD |= (1 << PD2);
    
    while (1)
    {
        // PIND & (1 << PD2) lit uniquement le bit PD2
        // Si le bit est à 0, bouton pressé (logique inversée)
        if (!(PIND & (1 << PD2)))
        {
            // Met PB0 à HIGH (1), allume la LED
            PORTB |= (1 << PB0);
        }
        else
        {
            //on met PB0 a 0, eteint la LED
            PORTB &= ~(1 << PB0);
        }

        _delay_ms(10);
    }
    return (0);
}
