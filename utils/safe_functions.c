/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:38:19 by jdupuis           #+#    #+#             */
/*   Updated: 2025/06/19 11:38:14 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	*safe_malloc(size_t bytes)
{
	void	*res;

	res = malloc(bytes);
	if (!res)
		error_exit("Error with the malloc");
	return (res);
}

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	else if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK
			|| opcode == DESTROY))
		error_exit("The value specified by mutex is invalid");
	else if (status == EINVAL && (opcode == INIT))
		error_exit("The value specified by attr is invalid");
	else if (status == EDEADLK)
		error_exit("A dead lock would occur"
			" if the thread blocked waiting for mutex");
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock on mutex");
	else if (status == ENOMEM)
		error_exit("The process cannot allocate enough memory to create"
			" another mutex");
	else if (status == EBUSY)
		error_exit("Mutex is locked");
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
			" use <LOCK UNLOCK INIT DESTROY>");
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("Insufficient resources to create another thread");
	else if (status == EPERM)
		error_exit("The caller does not have appropriate perimission");
	else if (status == EINVAL && CREATE == opcode)
		error_exit("The value specified by attr is invalid");
	else if (status == EINVAL && (JOIN == opcode || DETACH == opcode))
		error_exit("The thread is not joinable");
	else if (status == ESRCH)
		error_exit("No thread could be found corresponding to that specified"
			" by the given thread ID, thread");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected or the value of thread specifies"
			" the calling thread");
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
			" use <CREATE JOIN DETACH>");
}
