/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matus <matus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 08:34:17 by vnicoles          #+#    #+#             */
/*   Updated: 2025/03/17 06:52:55 by matus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

void exec_error(const char *msg) {
    perror(msg);
}

int execute_node(t_ast_node *node, int in_fd, int out_fd, int *last_status);
int execute_command(t_ast_node *node, int in_fd, int out_fd);
int execute_pipeline(t_ast_node *node, int in_fd, int out_fd, int *last_status);
int execute_redirections(t_ast_node *node, int in_fd, int out_fd, int *last_status);
int execute_logical_op(t_ast_node *node, int in_fd, int out_fd, int *last_status);
int execute_group(t_ast_node *node, int in_fd, int out_fd, int *last_status);

int execute_builtin(t_ast_node *node, int in_fd, int out_fd, int *last_status);

char **get_env_array(void); // You'll need to implement this based on your environment variables

int execute_node(t_ast_node *node, int in_fd, int out_fd, int *last_status) {
    if (!node)
        return 0;
    switch (node->type) {
		case NODE_BUILTIN:
			return execute_builtin(node, in_fd, out_fd, last_status);
        case NODE_CMD:
            return execute_command(node, in_fd, out_fd);
        case NODE_PIPE:
            return execute_pipeline(node, in_fd, out_fd, last_status);
        case NODE_REDIR_IN:
        case NODE_REDIR_OUT:
        case NODE_REDIR_APPEND:
        case NODE_HEREDOC:
            return execute_redirections(node, in_fd, out_fd, last_status);
        case NODE_AND:
        case NODE_OR:
            return execute_logical_op(node, in_fd, out_fd, last_status);
        case NODE_GROUP:
            return execute_group(node, in_fd, out_fd, last_status);
        default:
            fprintf(stderr, "Unknown node type in execution\n");
            return 1;
    }
}

int execute_builtin(t_ast_node *node, int in_fd, int out_fd, int *last_status)
{
	
}


int execute_command(t_ast_node *node, int in_fd, int out_fd) {
	pid_t	pid;
	char	**env;

	pid = fork();
	if (pid == 0) {
		if (in_fd != STDIN_FILENO) {
			dup2(in_fd, STDIN_FILENO);
			close(out_fd);
		}
		if (out_fd != STDOUT_FILENO) {
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		env = get_env_array();
		execve(node->args[0], node->args, env);
		fprintf(stderr, "Command not found: %s\n", node->args[0]);
		exit(127);
	}
    int status;
    waitpid(pid, &status, 0);
    if (in_fd != STDIN_FILENO)
        close(in_fd);
    if (out_fd != STDOUT_FILENO)
        close(out_fd);
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    else
        return 1;
}

int execute_pipeline(t_ast_node *node, int in_fd, int out_fd, int *last_status) {
	int	pipefd[2];
	int	left_status;
	int	right_status;

	if (pipe(pipefd) < 0) {
		exec_error("pipe");
		return 1;
	}
	left_status = execute_node(node->left, in_fd, pipefd[1], last_status);
	close(pipefd[1]);
	right_status = execute_node(node->right, pipefd[0], out_fd, last_status);
	close(pipefd[0]);
	*last_status = right_status;
    return right_status;
}

int execute_redirections(t_ast_node *node, int in_fd, int out_fd, int *last_status) {
	int	new_fd;
	int	old_fd;

	new_fd = -1;
	old_fd = -1;
	switch (node->type) {
		case NODE_REDIR_IN:
			new_fd = open(node->args[0], O_RDONLY);
			old_fd = in_fd;
			break;
		case NODE_REDIR_OUT:
			new_fd = open(node->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			old_fd = out_fd;
			break;
		case NODE_REDIR_APPEND:
			new_fd = open(node->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
			old_fd = out_fd;
			break;
		case NODE_HEREDOC:
			fprintf(stderr, "Heredoc not implemented yet\n");
            return 1;
		default:
		return 1;
	}
    if (node->type == NODE_REDIR_IN && in_fd != STDIN_FILENO)
        close(in_fd);
    else if ((node->type == NODE_REDIR_OUT || node->type == NODE_REDIR_APPEND) && out_fd != STDOUT_FILENO)
        close(out_fd);
    if (node->type == NODE_REDIR_IN)
        return execute_node(node->right, new_fd, out_fd, last_status);
    else
        return execute_node(node->right, in_fd, new_fd, last_status);
}

int execute_logical_op(t_ast_node *node, int in_fd, int out_fd, int *last_status) {
	int	left_status;
	int right_status;

	left_status = execute_node(node->left, in_fd, out_fd, last_status);
	*last_status = left_status;
	if ((node->type == NODE_AND && left_status == 0) ||
	(node->type == NODE_OR && left_status != 0)) {
		right_status = execute_node(node->right, in_fd, out_fd, last_status);
		*last_status = right_status;
		return right_status;
	}
	return left_status;
}

int execute_group(t_ast_node *node, int in_fd, int out_fd, int *last_status) {
	return execute_node(node->left, in_fd, out_fd, last_status);
}

int execute_ast(t_ast_node *root) {
	int last_status;

	last_status = 0;
	return execute_node(root, STDIN_FILENO, STDOUT_FILENO, &last_status);
}

