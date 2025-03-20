/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:52:08 by mgavorni          #+#    #+#             */
/*   Updated: 2025/03/20 16:11:25 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

sig_data_t glob_sig = {0};

void handle_sig(int sig)
{
    glob_sig.sig = 1;
    
}

void setup_sig_handler(void)
{
    
}