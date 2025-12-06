/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:46:05 by itaharbo          #+#    #+#             */
/*   Updated: 2024/11/11 19:02:14 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*destmove;
	char	*srcmove;
	size_t	i;

	if (!dest && !src)
		return (0);
	destmove = (char *)dest;
	srcmove = (char *)src;
	i = 0;
	if (destmove > srcmove)
	{
		while (n--)
			destmove[n] = srcmove[n];
	}
	else
	{
		while (n--)
		{
			destmove[i] = srcmove[i];
			i++;
		}
	}
	return (destmove);
}

/*int main()
{
	char source[] = "Bonjour, monde!";
	char destination[] = "idriss";
	
	ft_memmove(destination, source, 3);
	printf("Source: %s\n", source);
	printf("Destination: %s\n", destination);
	return (0);
}*/
