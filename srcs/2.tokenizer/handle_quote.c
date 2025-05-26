/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:12:24 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/25 23:38:51 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_handle_quote(t_ctx *ctx, const char **input, t_token **tokens)
{
	t_token_type	type;
	char			*str;
	int				len;
	char			c;

	c = **input;
	(*input)++;
	if (**input == c && c == '\'')
	{
		type = DQUOTE;
		len = define_substring(ctx, &str, input, type);
	}
	else if (**input != c)
	{
		type = SQUOTE;
		len = define_substring(ctx, &str, input, type);
	}
	(*input) += len;
	ft_lstadd_back(tokens, new_token(ctx, type, str));
}
