/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:32:53 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/26 04:42:45 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_minishell(t_ctx *ctx, char **input)
{
	add_history(*input);
	process_input(ctx, input);
	if (g_signal == SIGINT || ctx->sigint_received)
		sigint_true(ctx);
}

void	sigint_true(t_ctx *ctx)
{
	ctx->exit_status = 130;
	g_signal = 0;
	ctx->sigint_received = false;
}

void	no_input(char *input)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "exit\\n", 5);
}

void	check_g_signal(t_ctx *ctx, char **input)
{
	if (ctx->sigint_received)
	{
		free(*input);
		*input = NULL;
		ctx->exit_status = 130;
	}
	else
	{
		ctx->sigint_received = true;
	}
}

void	input_null(t_ctx *ctx, char **input)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	free_all_allocations(ctx);
	exit(ctx->exit_status);
	free(*input);
}
