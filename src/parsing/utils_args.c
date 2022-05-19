/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:07:48 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/18 19:02:17 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_args	*new_args(void)
{
	t_args	*newargs;

	newargs = ft_calloc(sizeof(t_args), 1);
	if (!newargs)
		return (NULL);
	newargs->arg = NULL;
	newargs->next = NULL;
	return (newargs);
}

void	args_addback(t_args **start, t_args *new)
{
	t_args	*temp;

	temp = *start;
	if (!temp)
	{
		*start = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

char	**get_args(t_token *token)
{
	t_args	*tempargs;
	char	**retarr;
	int		i;

	tempargs = token->args;
	i = 0;
	while (tempargs)
	{
		i++;
		tempargs = tempargs->next;
	}
	retarr = ft_calloc(sizeof(char *), i + 1);
	tempargs = token->args;
	i = 0;
	while (tempargs)
	{
		retarr[i] = tempargs->arg;
		i++;
		tempargs = tempargs->next;
	}
	retarr[i] = NULL;
	return (retarr);
}