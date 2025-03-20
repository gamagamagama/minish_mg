/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_hand.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:09:02 by mgavorni          #+#    #+#             */
/*   Updated: 2025/03/20 16:00:16 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_HAND_H
# define SIG_HAND_H

#define _POSIX_C_SOURCE 200809L
#include <signal.h>

typedef struct sig_data_s {
    volatile sig_atomic_t sig;
} sig_data_t;

extern sig_data_t glob_sig;

typedef struct sig_action_s {
    void (*sig_handler)(int);
    void (*sig_alt_handler)(int, siginfo_t *, void *);
    sigset_t sig_mask;
    int sig_flag;
}sig_action_t;

void setup_sig_handler(void);

#endif