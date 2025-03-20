/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_mg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 00:26:11 by matus             #+#    #+#             */
/*   Updated: 2025/03/18 21:01:14 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

typedef struct s_arena {
	void	*mem; //got a reason why use char? i know you then need to cast everything but its just didnt feel right to me :D
	size_t	size;
	size_t	used;
} t_arena;

void edge_case_mg(t_arena *arena, size_t struct_size)
{
    /*1024 is minimal size for malloc to not return undefined behavior things*/
    if (arena->size == 0 )
    {
        if (struct_size > 1024) 
        {
            arena->size = struct_size;
        } 
        else 
        {
            arena->size = 1024;
        }
    }
}

void *arena_expand_mg(t_arena *arena, size_t struct_size)
/* idea behind struct_size is that we expand 
reserved memblock acording to sizeof struct that 
in current momment didnt fitin,
but makeing sure keeping it effective and not calling function
too often i keep the factor to alocate more.
*/

{
    void *new_mem;
    size_t new_size;
    size_t   factor;
        
    factor = 2;
    edge_case_mg(arena, struct_size);
    if (arena->used + struct_size > arena->size)
    {
        if(arena->size > SIZE_MAX / factor - struct_size)
            return(NULL);
        new_size = arena->size * factor + struct_size;
        new_mem = (void *)malloc(new_size);
        if(!new_mem)
            return (0);
        if(arena->mem)
            ft_memcpy(new_mem, arena->mem, arena->used);
        free(arena->mem);
        arena->mem = new_mem;
        arena->size = new_size;
        
    }
    return((char *)arena->mem + arena->used); //move pointer at the begginig of free space.
}


