/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:38:19 by jdupuis           #+#    #+#             */
/*   Updated: 2025/04/28 17:30:59 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	*safe_malloc(size_t bytes)
{
	void	*res;

	res = malloc(bytes);
	if (!res)
		error_exit("Error whit the malloc\n");
	return (res);
}

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	else if (EINVAL == status && (opcode == LOCK || opcode == UNLOCK
			|| opcode == DESTROY))
		error_exit("The value specified by mutex is invalid\n");
	else if (EINVAL == status && (opcode == INIT))
		error_exit("The value specified by attr is invalid\n");
	else if (EDEADLK == status)
		error_exit("A dead lock would occur"
			" if the thread blocked waiting for mutex\n");
	else if (EPERM == status)
		error_exit("The current thread does not hold a lock on mutex\n");
	else if (ENOMEM == status)
		error_exit("The process cannot allocate enough memory to create"
			" another mutex\n");
	else if (EBUSY == status)
		error_exit("Mutex is locked\n");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("wrong opcode for the mutex handle"
			" use <LOCK UNLOCK INIT DESTROY>\n");
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EAGAIN == status)
		error_exit("Insufficient resources to create another thread\n");
	else if (EPERM == status)
		error_exit("The caller does not have appropriate perimission\n");
	else if (EINVAL == status && CREATE == opcode)
		error_exit("The value specified by attr is invalid\n");
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		error_exit("The thread is not joinable\n");
	else if (ESRCH == status)
		error_exit("No thread could be found corresponding to that specified"
			" by the given thread ID, thread\n");
	else if (EDEADLK == status)
		error_exit("A deadlock was detected or the value of thread specifies"
			" the calling thread\n");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("wrong opc for the thread handle"
			" use <CREATE JOIN DETACH>\n");
}
