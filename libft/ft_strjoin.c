/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:35:57 by itaharbo          #+#    #+#             */
/*   Updated: 2025/04/16 19:36:22 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stddef.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < len1)
		str[i] = s1[i];
	i = -1;
	while (++i < len2)
		str[len1 + i] = s2[i];
	str[len1 + len2] = '\0';
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
    char *result;

    result = ft_strjoin("hello", " world");
    printf("Résultat : %s\n", result); // Attendu : "hello world"
    free(result);

    result = ft_strjoin("", "test");
    printf("Résultat : %s\n", result); // Attendu : "test"
    free(result);

    result = ft_strjoin("test", "");
    printf("Résultat : %s\n", result); // Attendu : "test"
    free(result);

    result = ft_strjoin("", "");
    printf("Résultat : %s\n", result); // Attendu : ""
    free(result);

    result = ft_strjoin(NULL, "test");
    printf("Résultat : %s\n", result); // Attendu : (null)

    return (0);
}*/
