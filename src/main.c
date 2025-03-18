/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:44:35 by vnicoles          #+#    #+#             */
/*   Updated: 2025/03/14 00:52:35 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/tokenizer.h"
#include "../inc/ast.h"
#include <readline/history.h>

static t_tokenizer_data init_tok_data(t_arena *arena) {
	t_tokenizer_data	tok_data;

	tok_data.arena = arena;
    tok_data.tokens = NULL;
    tok_data.tail = NULL;
    return tok_data;
}

static void print_tokens(t_tokenizer_data *tok_data) {
	while (tok_data->tokens) {
		printf("Tokens: [%s] (Type: %d)\n", tok_data->tokens->value, tok_data->tokens->type);
		tok_data->tokens = tok_data->tokens->next;
	}
}

int	main(void) {
	char				*input;
	t_arena				*arena;
	t_tokenizer_data	tok_data;
	t_ast_node			*root;
	//int					status;

	arena = arena_init(64 * 1024);
	tok_data = init_tok_data(arena);
	while (1) {
		input = readline("minishell> ");
		if (!input)
			continue;
		if (strcmp(input, "exit") == 0) {
            free(input);
			break;
        }
		if (*input)
			add_history(input);

		tok_data.tokens = tokenize(&tok_data, input);
		root = parse(&tok_data);
		print_tokens(&tok_data);
		debug_ast(root);
		//status = execute_ast(root);
		//printf("Command return value: %d\n", status);
		free(input);
	}
    rl_clear_history();
    rl_cleanup_after_signal();
	arena_free(arena);
	return 0;
}
