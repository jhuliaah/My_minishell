/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:22:04 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/26 04:42:30 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h> 
#include <termios.h>
#include <errno.h>


// Handler para Ctrl+C (SIGINT)
// Limpa input atual
// Move cursor para nova linha
// Redesenha o prompt
void	handle_sigint(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// Handler para Ctrl+\ (SIGQUIT) - NÃO FAZ NADA
// Comportamento no modo interativo: Ignora
void	handle_sigquit(int sig)
{
	(void)sig;
}

// Configura Ctrl+C (SIGINT)
// Configura Ctrl+\ (SIGQUIT) para ignorar
void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
