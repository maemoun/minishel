#include ".././parsing/main.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}

void	ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
	{
		write(fd, &c, 1);
	}
}

void	ft_putstr_fd2(char *s, int fd)
{
	size_t	x;

	x = 0;
	if (fd >= 0 && s)
	{
		while (s[x])
		{
			ft_putchar_fd(s[x], fd);
			x++;
		}
	}
}

void	file_error(int error_nb, char *message, char *cmd)
{
	ft_putstr_fd2("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd2(cmd, 2);
		ft_putstr_fd2(": ", 2);
	}
	if (error_nb == -1)
	{
		ft_putstr_fd2(message, 2);
		return (ft_putstr_fd2(": ambiguous redirect\n", 2));
	}
	if (error_nb == EACCES)
		return (perror(message));
	if (error_nb == ENOENT)
		return (perror(message));
	if (error_nb == EEXIST)
		return (perror(message));
	if (error_nb == EISDIR)
		return (perror(message));
	if (error_nb == ENOTDIR)
		return (perror(message));
}

void	print_error(int error_nb, char *message, char *cmd)
{
	if (error_nb == EACCES || error_nb == ENOENT
		|| error_nb == EEXIST || error_nb == EISDIR
		|| error_nb == ENOTDIR || error_nb == -1)
		return (file_error(error_nb, message, cmd));
	else if (error_nb == ENOMEM)
		return (perror("minishell"));
	else if (error_nb == EINVAL)
		return (perror("minishell"));
	else if (error_nb == ENOSPC)
		return (perror("minishell"));
	else if (error_nb == EIO)
		return (perror("minishell"));
	else if (error_nb == EPIPE)
		return (perror("minishell"));
	else if (error_nb == EROFS)
		return (perror("minishell"));
	else if (error_nb == ELOOP)
		return (perror("minishell"));
}
