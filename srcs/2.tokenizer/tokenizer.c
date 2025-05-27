/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:34:30 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/26 22:48:04 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize_input(t_ctx *ctx, const char **input)
{
	t_token	*tokens;

	tokens = NULL;
	while (*input && **input && **input != '\0' && **input != '\n')
	{
		if (ft_isspace(**input))
			(*input)++;
		else if (**input == '|')
			token_handle_pipe(ctx, input, &tokens);
		else if (**input == '<' || **input == '>')
			token_handle_redir(ctx, input, &tokens);
		else if (**input == '\'' || **input == '\"')
			token_handle_quote(ctx, input, &tokens);
		else if (**input == '$')
			token_handle_env_var(ctx, input, &tokens);
		else
			token_handle_word(ctx, input, &tokens);
		if (!token_error_check(ctx, &tokens))
		{
			print_error(ctx, "Tokenization error", -1, 2);
			return (NULL);
		}
	}
	ft_lstadd_back(&tokens, new_token(ctx, END, NULL));
	return (tokens);
}

void	ft_lstadd_back(t_token **head, t_token *new_node)
{
	t_token	*current;

	if (!new_node)
		return ;
	if (!head || !new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}

t_token	*new_token(t_ctx *ctx, t_token_type type, const char *str)
{
	t_token	*token;

	token = safe_malloc(ctx, sizeof(t_token), ALLOC_TYPE_TOKEN);
	token->type = type;
	if (!str)
		token->value = NULL;
	else
		token->value = safe_strdup(ctx, str);
	token->next = NULL;
	return (token);
}

int	token_error_check(t_ctx *ctx, t_token **tokens)
{
	
}
