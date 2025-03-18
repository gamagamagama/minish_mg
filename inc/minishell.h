/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matus <matus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:48:22 by vnicoles          #+#    #+#             */
/*   Updated: 2025/03/17 13:40:21 by matus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "arena.h"
# include "ast.h"
# include "tokenizer.h"
# include "env_var.h"

# include "libft.h"


# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

t_arena		*arena_init(size_t size);
void		*arena_malloc(t_arena *arena, size_t size);
void		arena_reset(t_arena *arena);
void		arena_free(t_arena *arena);
t_token 	*tokenize(t_tokenizer_data *data, char *input);
t_ast_node	*parse(t_tokenizer_data *data);
void		debug_ast(t_ast_node *root);


#endif

