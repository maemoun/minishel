/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 19:28:59 by abdo              #+#    #+#             */
/*   Updated: 2025/08/21 14:50:58 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	is_var_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_');
}

char	*append_char(char *str, char c)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(str);
	tmp = ft_realloc(str, len + 2);
	if (!tmp)
	{
		free(str);
		return (NULL);
	}
	tmp[len] = c;
	tmp[len + 1] = '\0';
	return (tmp);
}

char	*append_str(char *dest, const char *src)
{
	size_t	len_dest;
	size_t	len_src;
	char	*tmp;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	tmp = ft_realloc(dest, len_dest + len_src + 1);
	if (!tmp)
	{
		free(dest);
		return (NULL);
	}
	ft_strcat(tmp, src);
	return (tmp);
}
