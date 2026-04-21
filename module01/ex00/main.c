/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siligh <siligh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:51:15 by siligh            #+#    #+#             */
/*   Updated: 2026/04/19 14:31:52 by siligh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>

//DATASHEET 37

void delay_ms(int ms)
{
    volatile unsigned long i, j; //pas d'optimizations
    for (i = 0; i < ms; i++) 
        for(j = 0; j < 445; j++); // 36 cycle * 445 = ~ 16 000 cycles =  ~ 1ms
}

int main(void)
{
    DDRB |= (1 << PB1);
    PORTB &= ~(1 << PB1);
    
    while(1)
    {
        PINB |= (1 << PB1); // toggle
        delay_ms(500);
    }
}