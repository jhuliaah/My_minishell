/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 03:03:10 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/26 03:10:33 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	execute_cmd(t_ctx *ctx, t_cmd *cmd)
// {
// 	int i = 0;
	
// 	// Expansão de argumentos
// 	while (cmd->args[i])
// 	{
// 		if (needs_expansion(cmd->args[i])) // Verifica se contém $ ou quotes
// 		{
// 			char *expanded = expand_string(ctx, cmd->args[i]);
// 			safe_free(ctx, cmd->args[i]);
// 			cmd->args[i] = expanded;
// 		}
// 		i++;
// 	}
	
// 	// Expansão de redirecionamentos
// 	t_redir *redir = cmd->redirections;
// 	while (redir)
// 	{
// 		if (ft_strchr(redir->filename, '$'))
// 		{
// 			char *expanded = expand_string(ctx, redir->filename);
// 			safe_free(ctx, redir->filename);
// 			redir->filename = expanded;
// 		}
// 		redir = redir->next;
// 	}
	
// 	// Resto da lógica de execução...
// }