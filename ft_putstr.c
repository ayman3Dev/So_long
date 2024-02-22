#include "so_long.h"

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		write (1, "(null)", 6);
		i += 6;
	}
	else if (s != NULL)
	{
		while (s[i] != '\0')
		{
			write (1, &s[i], 1);
			i++;
		}
	}
	return (i);
}
