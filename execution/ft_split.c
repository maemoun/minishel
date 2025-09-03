#include ".././parsing/main.h"

static size_t	counts(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static char	**shorten(char **p, size_t x)
{
	while (x > 0)
		free (p[--x]);
	free (p);
	return (NULL);
}

static char	**shoten2(char **p, const char *s, char c)
{
	size_t	i;
	size_t	start;
	size_t	x;

	i = 0;
	x = 0;
	while (s[i] && x < counts (s, c))
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		p[x++] = ft_substr(s, start, i - start);
		if (!p[x - 1])
			return (shorten(p, x));
	}
	p[x] = NULL;
	return (p);
}

char	**ft_split(const char *s, char c)
{
	size_t	count;
	char	**p;

	if (!s)
		return (NULL);
	count = counts(s, c);
	p = (char **)malloc(sizeof(char *) * (count + 1));
	if (!p)
		return (NULL);
	return (shoten2(p, s, c));
}
