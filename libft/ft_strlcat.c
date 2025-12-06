/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:13:37 by itaharbo          #+#    #+#             */
/*   Updated: 2024/11/12 15:45:10 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;
	size_t	srclen;
	size_t	dstlen;

	i = 0;
	j = siz - 1;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (siz <= dstlen)
		return (srclen + siz);
	while (*src && (dstlen + i) < j)
	{
		dst[dstlen + i] = *src;
		i++;
		src++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}
