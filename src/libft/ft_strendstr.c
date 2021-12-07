#include "libft.h"

char	*ft_strendstr(const char *str, const char *part)
{
	if (str == NULL || part == NULL)
		return (NULL);
	while (*str)
	{
		while (*str && *part && *str == *part)
			part++;
		if (*part == '\0')
			return ((char *)str + ft_strlen(part));
		str++;
	}
	return (NULL);
}
