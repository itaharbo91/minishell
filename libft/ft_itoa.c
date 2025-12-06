/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:37:58 by itaharbo          #+#    #+#             */
/*   Updated: 2025/04/16 19:18:46 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	long	nb;
	char	*str;

	nb = n;
	len = ft_len(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[--len] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
    char *result;

    // Test avec INT_MIN
    result = ft_itoa(-2147483648);
    printf("INT_MIN: %s\n", result); // Attendu : "-2147483648"
    free(result);

    // Test avec un nombre positif
    result = ft_itoa(12345);
    printf("Positif: %s\n", result); // Attendu : "12345"
    free(result);

    // Test avec zéro
    result = ft_itoa(0);
    printf("Zéro: %s\n", result); // Attendu : "0"
    free(result);

    // Test avec un nombre négatif
    result = ft_itoa(-42);
    printf("Négatif: %s\n", result); // Attendu : "-42"
    free(result);

    return (0);
}*/
