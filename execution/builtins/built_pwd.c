#include "../.././parsing/main.h"

int	ft_pwd(t_env *env_list)
{
	char	*pwd;

	pwd = get_value(env_list, "PWD");
	if (!pwd)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (1);
		printf("%s\n", pwd);
		free(pwd);
	}
	else
		printf("%s\n", pwd);
	return (0);
}
