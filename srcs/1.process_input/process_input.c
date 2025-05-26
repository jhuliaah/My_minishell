/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:54:45 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/26 15:25:02 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(t_ctx *ctx, const char **input)
{
	t_token	*tokens;
	t_cmd	*ast;

	tokens = tokenize_input(ctx, input);
	if (!tokens)
	{
		ctx->exit_status = 2;
		return (free_all_allocations(ctx));
	}
	if (!validate_syntax(ctx, tokens))
	{
		ctx->exit_status = 2;
		return (free_all_allocations(ctx));
	}
	ast = parse_tokens(ctx, &tokens);
	if (!ast)
	{
		ctx->exit_status = 2;
		return (free_all_allocations(ctx));
	}
	//expand_ast(ctx, ast);
	//execute_ast(ctx, ast);
	free_all_allocations(ctx);
}
