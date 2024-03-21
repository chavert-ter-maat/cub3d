/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_s.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/24 14:30:41 by cter-maa      #+#    #+#                 */
/*   Updated: 2024/01/04 15:52:07 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_string(char *string)
{
	int	index;

	index = 0;
	if (!string)
		return (FAILED);
	while (string[index])
	{
		if (put_c(string[index]) == FAILED)
			return (FAILED);
		index++;
	}
	return (index);
}

int	put_s(char *s)
{
	int	index;

	index = 0;
	if (s == 0)
	{
		index = print_string("(null)");
		if (index != 6)
			return (FAILED);
		return (6);
	}
	while (s[index])
	{
		if (put_c(s[index]) == FAILED)
			return (FAILED);
		index++;
	}
	return (index);
}
