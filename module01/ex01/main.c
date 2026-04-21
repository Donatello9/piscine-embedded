/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siligh <siligh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:51:15 by siligh            #+#    #+#             */
/*   Updated: 2026/04/20 18:23:22 by siligh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <avr/io.h>

//DATASHEET 16

int main(void)
{
    DDRB |= (1 << PB1); //LED D2 en sortie OC1A
    
    PRR &= ~(1 << PRTIM1); //PRTIM1 = 0 enable timer1 16.2

    TCCR1A &= ~(1 << COM1A1); //= 0
    TCCR1A |= (1 << COM1A0); //=1 action sur OC1A quand TOP, (16.11.1) 

    TCCR1B |= (1 << WGM12); //mode CTC 16.11

    TCCR1B |= (1 << CS12); //Sset le prescaler a 256, 16M trop grand valeur max 16bit = 65 536 (16.5)

    OCR1A  = 31249; // OCR1A = (16M * 1Hz / (2 * 256)) - 1 (16.6)
    while(1){}
}

