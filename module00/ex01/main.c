/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siligh <siligh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:51:15 by siligh            #+#    #+#             */
/*   Updated: 2026/04/13 18:29:39 by siligh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>

int main(void)
{
    // Configure PB0 en SORTIE
    // DDR = Data Direction Register
    // mettre le bit PB0 à 1 = sortie
    DDRB = DDRB | (1 << PB0);

    // Met PB0 à HIGH → allume la LED
    PORTB |= (1 << PB0);

    // Boucle infinie : le programme ne doit pas se terminer
    // sinon le microcontrôleur a un comportement indéfini
    while (1)
    {
    }

    return (0);
}
