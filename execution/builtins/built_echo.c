#include "../.././parsing/main.h"

static bool	check_n(char *parm)
{
	int	i;

	i = 0;
	if (parm[i] == '-')
		i++;
	while (parm[i] == 'n')
		i++;
	if (parm[i] == '\0' && i >= 2)
		return (true);
	return (false);
}

int	ft_echo(char **command)
{
	int	i;
	int	check;

	i = 1;
	check = 0;
	while (command[i] && check_n(command[i]))
	{
		check = 1;
		i++;
	}
	while (command[i])
	{
		ft_putstr_fd2(command[i], 1);
		if (command[i + 1])
			ft_putstr_fd2(" ", 1);
		i++;
	}
	if (check == 1)
		return (0);
	ft_putstr_fd2("\n", 1);
	return (0);
}
