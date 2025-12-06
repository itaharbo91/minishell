/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:25:01 by itaharbo          #+#    #+#             */
/*   Updated: 2025/05/19 17:10:48 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s) + 1;
	ptr = (char *)malloc(sizeof(char) * len);
	if (ptr == 0)
		return (0);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
#include <stdio.h>

int main(void)
{
    char *original = "Hello, world!";
    char *duplicate;

    duplicate = ft_strdup(original);
    if (!duplicate)
    {
        printf("Error: ft_strdup returned NULL\n");
        return 1;
    }

    printf("Original:  %s\n", original);
    printf("Duplicate: %s\n", duplicate);

    free(duplicate); // Libération de la mémoire allouée
    return 0;
}*/
