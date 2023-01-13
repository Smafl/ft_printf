/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:52 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/13 15:41:26 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_H
# define PRIVATE_H

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>

# define FLAG_MINUS 	0b0000000001
# define FLAG_ZERO 		0b0000000010
# define FLAG_HASH 		0b0000000100
# define FLAG_SPACE 	0b0000001000
# define FLAG_PLUS 		0b0000010000
# define FLAG_WIDTH 	0b0000100000
# define FLAG_PRECISION 0b0001000000
# define FLAG_UPPERCASE 0b0010000000
# define FLAG_POINTER 	0b0100000000
# define FLAG_BASE_DEC	0b1000000000

enum e_state
{
	STATE_TEXT,
	STATE_FORMAT,
	STATE_FLAG,
	STATE_WIDTH,
	STATE_UNDEF_PRECISION,
	STATE_PRECISION,
	STATE_TYPE,
	STATE_END
};

#endif
