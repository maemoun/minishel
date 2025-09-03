/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:33:15 by abdo              #+#    #+#             */
/*   Updated: 2025/08/21 16:12:07 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	handle_exit(t_env *env_list, char *input)
{
	write(1, "exit\n", 5);
	free_env_list(env_list);
	free(input);
	rl_clear_history();
	exit(0);
}
