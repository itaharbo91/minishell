/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:45:24 by itaharbo          #+#    #+#             */
/*   Updated: 2025/05/19 17:11:00 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	unc;
	char			*str;
	int				i;

	unc = (unsigned char)c;
	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == unc)
			return (&str[i]);
		i++;
	}
	if (unc == '\0')
		return (&str[i]);
	return (NULL);
}
/*
#include <stdio.h>

int	main(void)
{
    const char *str = "Hello, world!";
    char *result;

    result = ft_strchr(str, 'o');
    printf("Résultat pour 'o' : %s\n", result); // Attendu : "o, world!"

    result = ft_strchr(str, ',');
    printf("Résultat pour ',' : %s\n", result); // Attendu : ", world!"

    result = ft_strchr(str, 'z');
    printf("Résultat pour 'z' : %s\n", result); // Attendu : (null)

    result = ft_strchr(str, '\0');
    printf("Résultat pour '\\0' : %s\n", result); // Attendu : ""

    return (0);
}*/
