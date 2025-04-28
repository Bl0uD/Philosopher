/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:40:50 by jdupuis           #+#    #+#             */
/*   Updated: 2025/04/28 16:59:49 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static void	write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
	if (status == TAKE_FIRST_FORK && !simulation_finished(philo->table))
		printf(W"%6ld"RST" %d has taken the 1° fork"
			"\t\t\tn°"B"[ %d ]\n"RST, elapsed, philo->id,
			philo->first_fork->fork_id);
	else if (status == TAKE_SECOND_FORK && !simulation_finished(philo->table))
		printf(W"%6ld"RST" %d has taken the 2° fork"
			"\t\t\tn°"B"[ %d ]\n"RST, elapsed, philo->id,
			philo->first_fork->fork_id);
	else if (status == EATING && !simulation_finished(philo->table))
		printf(W"%6ld"C" %d is eating ..."
			"\t\t\t"Y"[ %ld ]\n"RST, elapsed, philo->id, philo->meals_counter);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf(W"%6ld"RST" %d is sleeping ...\n", elapsed, philo->id);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf(W"%6ld"RST" %d is thinking ...\n", elapsed, philo->id);
	else if (status == DIED)
		printf(RED"\t\t %6ld %d died !!!\n"RST, elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
		else if (EATING == status && !simulation_finished(philo->table))
			printf(W"%-6ld"C" %d is eating ...\n"RST, elapsed, philo->id);
		else if (SLEEPING == status && !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d is sleeping ...\n", elapsed, philo->id);
		else if (THINKING == status && !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d is thinking ...\n", elapsed, philo->id);
		else if (DIED == status)
			printf(RED"%-6ld %d died\n"RST, elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
