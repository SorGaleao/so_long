/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrsouz <gabrsouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:16:09 by gabrsouz          #+#    #+#             */
/*   Updated: 2025/06/25 16:46:16 by gabrsouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strlen(char *c)
{
	int	i;

	if (!c)
		return (0);
	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	int		n;
	int		i;
	char	*dup;

	if (!src)
		return (NULL);
	i = 0;
	n = ft_strlen(src);
	dup = (char *)malloc((n + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	j = 0;
	i = -1;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(char *str, int chr)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)chr)
			return (&str[i]);
		i++;
	}
	if (str[i] == (unsigned char)chr)
		return (&str[i]);
	return (NULL);
}

char	*ft_substr(char *src, int start, int len)
{
	char			*str;
	unsigned int	i;
	int				size;

	if (!src)
		return (NULL);
	i = 0;
	size = ft_strlen(src);
	if (start > size)
	{
		str = malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[i] = '\0';
		return (str);
	}
	if (len > size - start)
		len = size - start;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (len--)
		str[i++] = src[start++];
	str[i] = '\0';
	return (str);
}
//Add all the helper functions you need in the 
//get_next_line_utils.c file.