/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:56:35 by abdo              #+#    #+#             */
/*   Updated: 2025/08/21 14:56:43 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	print_token_error(t_type type)
{
	char	*str;

	str = return_str(type);
	if (!str)
		return ;
	write(2, " `", 2);
	write(2, str, ft_strlen(str));
	write(2, "'", 1);
	free(str);
}

int	print_syntax(const char *msg, t_type type)
{
	write(2, "bash: ", 6);
	write(2, msg, ft_strlen(msg));
	if (type != (t_type)-1)
		print_token_error(type);
	write(2, "\n", 1);
	return (258);
}

char	*return_str(t_type type)
{
	if (type == PIPE)
		return (ft_strdup("|"));
	if (type == RED_IN)
		return (ft_strdup("<"));
	if (type == RED_OUT)
		return (ft_strdup(">"));
	if (type == HEREDOC)
		return (ft_strdup("<<"));
	if (type == APPEND)
		return (ft_strdup(">>"));
	if (type == DOUBLE_PIPE)
		return (ft_strdup("||"));
	return (ft_strdup(""));
}

int	contains_unclosed_quote(const char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (!str[i])
				return (1);
		}
		if (str[i])
			i++;
	}
	return (0);
}
