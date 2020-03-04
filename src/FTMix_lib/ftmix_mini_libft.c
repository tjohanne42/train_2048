#include "ftmix_lib.h"

size_t		ft_nblen(int nb)
{
	size_t	i = 0;

	if (nb < 0)
	{
		nb *= -1;
		i++;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		i++;
	}
	return (i + 1);
}

char		*ft_itoa(int x)
{
	char 	*str;
	size_t	len = ft_nblen(x);
	size_t	i = 0;
	size_t	neg = 0;

	str = NULL;
	if (!(str = malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	if (x < 0)
	{
		neg = 1;
		x *= -1;
	}
	while (i < len)
	{
		str[len - i - 1] = x % 10 + '0';
		x = x / 10;
		i++;
	}
	str[len] = '\0';
	if (neg == 1)
		str[0] = '-';
	return (str);
}

int		ft_sqrt(int x, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (x * ft_sqrt(x, power - 1));
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

_Bool			ft_strfreejoin(char **s1, const char *s2, char statut)
{
	char		*tmp;
	size_t		len;

	if (statut != 's' && statut != 'e')
		return (SDL_FALSE);
	tmp = NULL;
	len = ft_strlen(*s1);
	if (!(tmp = malloc(sizeof(*tmp) * (len + 1))))
		return (SDL_FALSE);
	ft_strncpy(tmp, *s1, len);
	free(*s1);
	*s1 = NULL;
	if (statut == 's' && !(*s1 = ft_strjoin(s2, tmp)))
		return (SDL_FALSE);
	else if (statut == 'e' && !(*s1 = ft_strjoin(tmp, s2)))
		return (SDL_FALSE);
	free(tmp);
	return (SDL_TRUE);
}

// mili sec to str
char			*ft_mststr(long int ms)
{
	char		*str;
	size_t		size;
	size_t		i;

	str = NULL;
	ms = ms % (24 * 60 * 60 * 1000);
	if (ms / 1000 / 60 / 60 >= 10)
		size = 8;
	else if (ms / 1000 / 60 / 60 > 0)
		size = 7;
	else if (ms / 1000 / 60 % 60 >= 10)
		size = 5;
	else
		size = 4;
	if (!(str = malloc(sizeof(*str) * (size + 1))))
		return (NULL);
	i = 0;
	if (ms / 1000 / 60 / 60 >= 10)
		str[i++] = ms / 1000 / 60 / 60 / 10 + '0';
	if (ms / 1000 / 60 / 60 > 0)
	{
		str[i++] = ms / 1000 / 60 / 60 % 10 + '0';
		str[i++] = ':';
	}
	if (ms / 1000 / 60 >= 10)
		str[i++] = ms / 1000 / 60 % 60 / 10 + '0';
	str[i++] = ms / 1000 / 60 % 60 % 10 + '0';
	str[i++] = ':';
	str[i++] = ms / 1000 % 60 / 10 + '0';
	str[i++] = ms / 1000 % 60 % 10 + '0';
	str[i] = '\0';
	return (str);
}

void			ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

size_t			ft_strlen(const char *str)
{
	size_t		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char			*ft_strjoin(const char *s1, const char *s2)
{
	size_t		len;
	size_t		i;
	size_t		x;
	char		*str;

	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	x = 0;
	while (s2[x])
	{
		str[i + x] = s2[x];
		x++;
	}
	str[i + x] = '\0';
	return (str);
}
