/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siligh <siligh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:51:15 by siligh            #+#    #+#             */
/*   Updated: 2026/04/13 21:11:31 by siligh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{

    DDRD &= ~(1 << PD2); // PD2 en entrée (bouton)
    PORTD |= (1 << PD2);// Pull-up activée
    DDRB |= (1 << PB0);// PB0 en sortie (LED)

    while (1)
    {
        if (!(PIND & (1 << PD2))) // if push 
        {
            _delay_ms(50);
            if (PIND & (1 << PD2)) // if release
                PINB |= (1 << PB0); // 14.2.2 DATASHEET
        }
    }
    return 0;
}
