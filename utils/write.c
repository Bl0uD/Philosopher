/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:40:50 by jdupuis           #+#    #+#             */
/*   Updated: 2025/04/28 03:21:26 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static void	write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
	if (status == TAKE_FIRST_FORK && !simulation_finished(philo->table))
		printf(W"%6ld"RST" %ld has taken the 1° fork"
			"\t\t\tn°"B"[ %ld ]\n"RST, elapsed, (long)philo->id, (long)philo->id);
	else if (status == TAKE_SECOND_FORK && !simulation_finished(philo->table))
		printf(W"%6ld"RST" %ld has taken the 2° fork"
			"\t\t\tn°"B"[ %ld ]\n"RST, elapsed, (long)philo->id, (long)philo->id);
	else if (status == EATING && !simulation_finished(philo->table))
		printf(W"%6ld"C" %ld is eating ..."
			"\t\t\tn°"B"[ %ld ]\n"RST, elapsed, (long)philo->id, philo->meals_counter);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf(W"%6ld"C" %ld is sleeping ...\n"RST, elapsed, (long)philo->id);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf(W"%6ld"C" %ld is thinking ...\n"RST, elapsed, (long)philo->id);
	else if (status == DIED)
		printf(RED"\t\t %6ld %ld died !!!\n"RST, elapsed, (long)philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = gettime(MILISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			&& !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING && !simulation_finished(philo->table))
			printf(W"%-6ld"C" %d is eating\n"RST, elapsed, philo->id);
		else if (status == SLEEPING && !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING && !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d is thinking\n", elapsed, philo->id);
		else if (status == DIED)
			printf(RED"%-6ld %d died\n"RST, elapsed, philo->id);
	}
}
