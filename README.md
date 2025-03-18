ast.h

added NODE_BUILTIN for CMD that should execute from parrent process not execve or fork(), (echo, cd, pwd, export, unset, env, exit)

ast.c

NODE_BUILTIN in case switch, func: node_type_to_str();

exec_engine.c

int execute_builtin(t_ast_node *node, int in_fd, int out_fd, int *last_status);

	case NODE_BUILTIN:
			return execute_builtin()