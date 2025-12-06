/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:03:49 by itaharbo          #+#    #+#             */
/*   Updated: 2025/04/16 19:23:55 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static char	*string(char const *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!(str))
		return (NULL);
	ft_strlcpy(str, s, i + 1);
	return (str);
}

static void	ft_free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		strs_len;
	char	**str;

	if (!s)
		return (NULL);
	strs_len = count_word(s, c);
	str = ft_calloc(sizeof(char *), (strs_len + 1));
	if (!(str))
		return (NULL);
	i = 0;
	while (i < strs_len)
	{
		while (*s == c)
			s++;
		str[i] = string(s, c);
		if (!(str[i]))
			return (ft_free_split(str), NULL);
		s = s + ft_strlen(str[i]);
		i++;
	}
	str[i] = NULL;
	return (str);
}
/*
#include <stdio.h>

void	print_split(char **result)
{
    if (result)
    {
        for (int i = 0; result[i] != NULL; i++)
        {
            printf("Mot %d: %s\n", i + 1, result[i]);
            free(result[i]);
        }
        free(result);
    }
    else
    {
        printf("Erreur ou chaîne vide.\n");
    }
}

int	main(void)
{
    char	*str1 = "bonjour,les gars,hoh0";
    char	*str2 = "";
    char	*str3 = ",,,";
    char	*str4 = "hello";
    char	*str5 = ",hello,world,";
    char	**result;

    printf("Test 1:\n");
    result = ft_split(str1, ',');
    print_split(result);

    printf("\nTest 2:\n");
    result = ft_split(str2, ',');
    print_split(result);

    printf("\nTest 3:\n");
    result = ft_split(str3, ',');
    print_split(result);

    printf("\nTest 4:\n");
    result = ft_split(str4, ',');
    print_split(result);

    printf("\nTest 5:\n");
    result = ft_split(str5, ',');
    print_split(result);

    return (0);
}*/
