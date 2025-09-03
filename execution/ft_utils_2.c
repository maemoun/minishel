#include ".././parsing/main.h"

char	*ft_strjoin_2(char const *s1, char const *s2)
{
	char	*p;
	int		len_s;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup_2(s2));
	if (!s2)
		return (ft_strdup_2(s1));
	len_s = ft_strlen_2(s1) + ft_strlen_2(s2);
	p = (char *)malloc((sizeof(char) * len_s) + 1);
	if (!p)
		return (strerror(errno), NULL);
	i = -1;
	while (s1[++i])
		p[i] = s1[i];
	j = 0;
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}

char	*ft_strdup_2(const char *s1)
{
	char	*ma;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	ma = (char *)malloc(sizeof(char) * (ft_strlen_2(s1) + 1));
	if (!ma)
		return (strerror(errno), NULL);
	while (s1[i])
	{
		ma[i] = s1[i];
		i++;
	}
	ma[i] = '\0';
	return (ma);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	tot;

	i = 0;
	sign = 1;
	tot = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		tot = (tot * 10) + (str[i] - 48);
		i++;
	}
	return ((int)(tot * sign));
}

char	*ft_substr_2(char const *s, unsigned int start, size_t len)
{
	char	*ma;
	size_t	mlen;
	size_t	b;

	if (!s)
		return (NULL);
	mlen = ft_strlen_2(s);
	b = 0;
	if (start >= (unsigned int)mlen)
		return (ft_strdup_2(""));
	if (len > mlen - start)
		len = mlen - start;
	ma = (char *)malloc(sizeof(char) * (len + 1));
	if (!ma)
		return (strerror(errno), NULL);
	while (b < len)
	{
		ma[b] = s[start + b];
		b++;
	}
	ma[b] = '\0';
	return (ma);
}

char	*ft_strchr_2(const char *s, int c)
{
	size_t	x;

	x = 0;
	while (s[x])
	{
		if (s[x] == (char)c)
			return ((char *)s + x);
		x++;
	}
	if (s[x] == (char)c)
		return ((char *)s + x);
	return (NULL);
}
