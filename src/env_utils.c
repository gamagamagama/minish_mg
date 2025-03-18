/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:23:59 by vnicoles          #+#    #+#             */
/*   Updated: 2025/03/13 19:52:52 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/env_var.h"
#include "../inc/minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void set_signal(int signum) {
	g_signal_received = signum;
}

int get_env_var_count(t_env_var *env_list) {
	int			count;
	t_env_var	*current;

	count = 0;
	current = env_list;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

char **get_env_array(t_arena *arena, t_env_var *env_list) {
	int			count;
	char		**env_array;
	t_env_var	*current;
	int			i;
	size_t		len;

	count = get_env_var_count(env_list);
	env_array = arena_malloc(arena, sizeof(char *) * (count + 1));
	if (!env_array)
		return NULL;
	current = env_list;
	i = 0;
	while (current && env_array) {
		len = strlen(current->key) + strlen(current->value) + 2;
		env_array[i] = arena_malloc(arena, len);
		if (env_array[i]) {
			snprintf(env_array[i], len, "%s=%s", current->key, current->value);
			i++;
		}
		current = current->next;
	}
	if (env_array)
        env_array[i] = NULL;
    return env_array;
}

char *get_env_value(t_env_var *env_list, const char *key) {
    t_env_var	*current;

	current = env_list;
    while (current) {
        if (strcmp(current->key, key) == 0)
            return current->value;
        current = current->next;
    }
    return NULL;
}

void process_var(t_arena *arena, const char **src, char **dst, t_env_var *env_list) {
	char	*name;
	char	*value;

	(*src)++;
	name = extract_var_name(arena, src);
	if (name)
		value = get_env_value(env_list, name);
	else
		value = NULL;
	if (value) {
		strcpy(*dst, value);
		*dst += strlen(value);
	}
}

size_t calc_expanded_size(const char *str, t_env_var *env_list) {
	size_t		size;
	const char	*p = str;
	char		*name;
	char		*value;

	size = 0;
	while (*p) {
		if (*p == '$' && *(p + 1) && (isalnum(*(p + 1)) || *(p + 1) == '_')) {
			p++;
			name = extract_var_name(NULL, &p);
			if (name)
				value = get_env_value(env_list, name);
			else
				value = NULL;
			if (value)
				size += strlen(value);
		} else {
			size++;
			p++;
		}
	}
	return size;
}

char *expand_variables(t_arena *arena, const char *str, t_env_var *env_list) {
    char	*dst;
    char	*src;
	size_t	size;
	char	*expanded;
	
	if (!str)
		return NULL;
	size = calc_expanded_size(str, env_list);
	expanded = arena_malloc(arena, size + 1);
	dst = expanded;
	src = str;
	while (src && *src && expanded) {
		if (*src == '$' && *(src + 1) && (isalnum(*(src + 1)) || *(src + 1) == '_'))
			process_var(arena, &src, &dst, env_list);
		else
			*dst++ = *src++;
	}
	if (expanded)
		*dst = '\0';
	return expanded;
}

int match_wildcard(const char *pattern, const char *string) {
	if (!*pattern && !*string)
		return 1;
	if (*pattern == '*' && !*(pattern + 1))
		return 1;
	if (!*pattern || !*string)
		return 0;
	if (*pattern == '*')
		return match_wildcard(pattern + 1, string) ||
				match_wildcard(pattern, string + 1);
	if (*pattern == '?' || *pattern == *string)
		return match_wildcard(pattern + 1, string + 1);
	return 0;
}

char **process_wildcard(t_arena *arena, char *arg, int *count) {
	
}
