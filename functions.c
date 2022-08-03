#include "ft_printf.h"

int		number_len(long long nbr)
{
	int	res;

    if (!nbr)
        return (1);
	res = 0;
	while (nbr)
	{
		res += 1;
		nbr /= 10;
	}
	return (res);
}

int	hex_len(long long nbr)
{
	int	res;

    if (!nbr)
        return (1);
	res = 0;
	while (nbr)
	{
		res += 1;
		nbr /= 16;
	}
	return (res);
}

int address_len(unsigned long address)
{
    int len;

    len = 2;
    while (address)
    {
        len += 1;
        address /= 16;
    }
    if (len == 2)
        return (3);
    return (len);
}

size_t  ft_strlen(const char *s)
{
    size_t  i;

    if (!s)
        return (0);
    i = 0;
    while (s[i])
        i++;
    return (i);
}