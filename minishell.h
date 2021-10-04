/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:07:16 by hyospark          #+#    #+#             */
/*   Updated: 2021/10/04 19:07:54 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include "libft/libft.h"
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <sys/ioctl.h>


void	print_error(char *str);

#endif
