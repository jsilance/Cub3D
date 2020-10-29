/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_d_malloc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsilance <jsilance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 20:21:42 by jsilance          #+#    #+#             */
/*   Updated: 2020/10/24 20:48:48 by jsilance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void		ft_duty_free(char **ptr_ptr, int string)
{
	int	i;

	i = 0;
	while (ptr_ptr && ptr_ptr[i] && i < string)
		free((void *)ptr_ptr[i++]);
	if (ptr_ptr)
		free((void *)ptr_ptr);
}

static void	*ft_memcpy_ws(void *dest, const void *src, size_t n)
{
	unsigned char	*src1;
	unsigned char	*dst;

	if (!dest && !src)
		return (NULL);
	src1 = (unsigned char *)src;
	dst = (unsigned char *)dest;
	if (!n || dest == src)
		return (dest);
	while (n--)
	{
		*dst++ = *src1++;
		*dst = 0;
	}
	return (dest);
}

static char	*ft_strdup_ws(const char *s)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ptr = NULL;
	while (s && s[i++])
		j++;
	if (!(ptr = ft_calloc(sizeof(char), (j + 1))))
		return (NULL);
	if (s)
		ft_memcpy_ws(ptr, s, j);
	ptr[j] = '\0';
	return ((char *)ptr);
}

char		**ft_realloc_d_malloc(char **ptr, char *str, t_info *info)
{
	char	**tab;
	int		c_str;
	int		i;

	i = 0;
	c_str = count_string((char const **)ptr);
	if (!str || !*str)
		return (ptr);
	if (!(tab = (char**)ft_calloc(sizeof(char*), (c_str + 2))))
		return (NULL);
	while (ptr != NULL && ptr[i] && i < c_str)
	{
		tab[i] = ft_strdup_ws(ptr[i]);
		i++;
	}
	ft_duty_free(ptr, c_str);
	tab[i++] = ft_strdup_ws(str);
	tab[i] = NULL;
	return (tab);
}
