/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:12:24 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/26 21:47:27 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_handle_quote(t_ctx *ctx, const char **input, t_token **tokens)
{
	t_token_type	type;
	char			*str;
	char			c;

	if (!closed_quotation(ctx, input))
	{
		print_error(ctx, "Unclosed quotation", -1, 2);
		return ;
	}
	c = **input;
	(*input)++;
	if (**input != c && c == '"')
	{
		type = DQUOTE;
		define_substring(ctx, &str, input, type);
	}
	else if (**input != c && c == '\'')
	{
		type = SQUOTE;
		define_substring(ctx, &str, input, type);
	}
	else if (**input == c)
	{
		str = safe_strdup(ctx, "");
		(*input)++;
	}
	ft_lstadd_back(tokens, new_token(ctx, type, str));
}
