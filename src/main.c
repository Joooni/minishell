/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:40:30 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/30 13:23:29 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	*g_pids = NULL;

static void	ft_parse_and_execute(t_shell *shell, char *input)
{
	parser(shell, input);
	exec(shell);
	g_pids[0] = 0;
	free(g_pids);
	g_pids = NULL;
	parsing_cleanup(shell);
	shell->token = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 1 || argv[1])
	{
		perror("Too many arguments");
		return (1);
	}
	printf("/* ********************************************************** */\n");
	printf("/*                                                            */\n");
	printf("/*                                        :::      ::::::::   */\n");
	printf("/*                                      :+:      :+:    :+:   */\n");
	printf("/*                                    +:+ +:+         +:+     */\n");
	printf("/*   MINISHELL                      +#+  +:+       +#+        */\n");
	printf("/*                                +#+#+#+#+#+   +#+           */\n");
	printf("/*                by jsubel            #+#    #+#             */\n");
	printf("/*               and kmeixner         ###   ########.fr       */\n");
	printf("/*                                                            */\n");
	printf("/* ********************************************************** */\n");
	shell(envp);
	return (0);
}

//	this is just temporarily here for testing
void	printtoken(t_token **tokenn)
{
	t_args	*args;
	t_redir	*redir;
	t_token	*token;

	token = *tokenn;
	while (token)
	{
		printf("-------------NEW TOKEN------------\n");
		printf("PID: %d\n", token->pid);
		args = token->args;
		printf("---------------ARGS---------------\n");
		while (args)
		{
			printf("%s\n", args->arg);
			args = args->next;
		}
		printf("----------------------------------\n");
		redir = token->redir;
		printf("--------------REDIRS--------------\n");
		while (redir)
		{
			printf("%d: %s\n", redir->id, redir->filename);
			redir = redir->next;
		}
		printf("----------------------------------\n");
		token = token->next;
	}
}

void	shell(char **envp)
{
	char	*input;
	t_shell	*shell;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	shell = ft_calloc(sizeof(t_shell), 1);
	shell->env = init_env(envp);
	while (42)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		add_history(input);
		if (input && *input && !prechecks(shell, input))
			ft_parse_and_execute(shell, input);
		free(input);
	}
	rl_clear_history();
	ft_free_everything(shell);
	free(input);
	return ;
}
