/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siligh <siligh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:51:15 by siligh            #+#    #+#             */
/*   Updated: 2026/04/20 18:33:12 by siligh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>

//DATASHEET 16

int main(void)
{

    int value;
    
    DDRD &= ~(1 << PD2); // PD2 en entree (bouton)
    PORTD |= (1 << PD2);// Pull-up activee
    
    DDRD &= ~(1 << PD4); // PD4 en entree (bouton)
    PORTD |= (1 << PD4);// Pull-up activee

    
    DDRB |= (1 << PB1); //LED D2 en sortie OC1A
    
    PRR &= ~(1 << PRTIM1); //PRTIM1 = 0 enable timer1 16.2

    TCCR1A |= (1 << COM1A1); //= 1
    TCCR1A &= ~(1 << COM1A0); //=0 action sur OC1A quand TOP ,duty cycle normal (16.11.1) 

    TCCR1B |= (1 << WGM12); //mode Fast PWM 16.11
    TCCR1B |= (1 << WGM13);
    TCCR1A |= (1 << WGM11);
    
    TCCR1B |= (1 << CS12); //Sset le prescaler a 256, 16M trop grand valeur max 16bit = 65 536 (16.5)

    
    OCR1A  = 6249; // OCR1A = duty cycle = 10% de la periode totale
    ICR1 = 62499; // ICR1 = (16M / 256 * 1Hz ) - 1 (16.9.3)
    
    value = 1;
    
    while(1)
    {
        if (!(PIND & (1 << PD2))) // if push 
        {
            _delay_ms(50); //bounce mecanique
            if ((PIND & (1 << PD2)) && (value < 10)) // if release
            {
                value++;
                if (value == 10)
                    OCR1A = 62499;
                else
                    OCR1A += 6249; 
            }
                
        }

        if (!(PIND & (1 << PD4))) // if push 
        {
            _delay_ms(50);
            if ((PIND & (1 << PD4)) && (value > 0)) // if release
            {
                value--;
                if (value == 0)
                    OCR1A = 0;
                else
                    OCR1A -= 6249;
            }
        }

    }
}