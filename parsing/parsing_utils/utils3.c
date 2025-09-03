/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:32:54 by abdo              #+#    #+#             */
/*   Updated: 2025/08/21 14:42:04 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	ft_len(int nb)
{
	int	x;

	x = 0;
	if (nb == -2147483648)
		return (11);
	else if (nb == 0)
		return (1);
	else if (nb < 0)
	{
		nb = -nb;
		x++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		x++;
	}
	return (x);
}

char	*ft_itoa(int n)
{
	long int	nb;
	int			len;
	char		*s;

	nb = n;
	len = ft_len(n);
	s = malloc(sizeof(char) * len + 1);
	if (s == NULL)
		return (NULL);
	s[len] = '\0';
	len--;
	if (nb == 0)
		s[len] = nb + 48;
	if (nb < 0)
	{
		s[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		s[len] = (nb % 10) + 48;
		nb = nb / 10;
		len--;
	}
	return (s);
}

void	*ft_realloc(void *ptr, size_t new_size)
{
	char	*old;
	char	*new_ptr;
	size_t	i;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	old = (char *)ptr;
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	i = 0;
	while (i + 1 < new_size && old[i])
	{
		new_ptr[i] = old[i];
		i++;
	}
	new_ptr[i] = '\0';
	free(ptr);
	return (new_ptr);
}

char	*my_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char	*dest, const char	*src)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
