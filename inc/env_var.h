/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:29:00 by vnicoles          #+#    #+#             */
/*   Updated: 2025/03/13 18:05:45 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef ENV_VAR_H
# define ENV_VAR_H

typedef struct s_env_var {
	char				*key;
	char				*value;
	struct s_env_var	*next;
} t_env_var;

#endif
