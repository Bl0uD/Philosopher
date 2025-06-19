/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:30:52 by jdupuis           #+#    #+#             */
/*   Updated: 2025/06/19 11:38:10 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		parsing(&table, av);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	else
	{
		error_exit("Wrong input:\n"
			G"Correct id ./philo 5 800 200 200 [5]"RST);
	}
	return (0);
}
