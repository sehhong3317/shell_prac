/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gilee <gilee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:36:56 by gilee             #+#    #+#             */
/*   Updated: 2021/12/01 16:59:16 by gilee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdio.h>
extern int rl_catch_signals;
void	handler(int signum)
{
	if (signum != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

int		main(void)
{
	int				ret;
	char			*line;

	printf("%d\n", rl_catch_signals);
	rl_catch_signals = 0;
	printf("%d\n", rl_catch_signals);
	signal(SIGINT, handler);
	while (true)
	{
		line = readline("input> ");
		if (line)
		{
			ret = strcmp(line, "bye");
			if (ret)
				printf("output> %s\n", line);
			add_history(line);
			free(line);
			line = NULL;
			if (!ret)
				break ;
		}
		else
			return (1);
	}
	return (0);
}
