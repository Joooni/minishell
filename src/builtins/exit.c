/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:01:04 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/23 17:49:51 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	ft_isnumeric(char *str);

/**
* @brief cleanly terminate and exit the program
* Check arguments of invocation:
*	if no argument, exit with global error number
*	if one numeric argument, exit with that
*	if more than one, throw error and don't exit
*/
int	ft_exit_minishell(t_shell *shell)
{
	int	nbr_args;

	nbr_args = ft_nbr_args(shell->token->args);
	if (nbr_args > 2)
		ft_error_msg(shell, ERR_EXIT_COUNT, ERRNO_EXIT_COUNT);
	else if (nbr_args == 2 && !(ft_isnumeric(shell->token->args->next->arg)))
		ft_error_msg(shell, ERR_EXIT_ISNUM, ERRNO_EXIT_ISNUM);
	else
		shell->lastreturn = ft_atoi(shell->token->args->next->arg);
	ft_free_everything(shell);
	return (1);
}

/**
 * Takes a message and error number and prints out the corresponding error messages
 * If err_num is given the function, looks it up from header and sets lastreturn to it
 *
*/
void	ft_error_msg(t_shell *shell, char *msg, int err_num)
{
	char *tmp;

	tmp = ft_strjoin("minishell: ", msg);
	if (err_num == 0)
		perror(tmp);
	else
	{
		ft_putendl_fd(tmp, 2);
		shell->lastreturn = err_num;
	}
	free(tmp);
}

static int	ft_isnumeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] <= '0' || str[i] >= '9')
			return (0);
		i++;
	}
	return (1);
}
