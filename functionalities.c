#include "ft_printf.h"

void    ft_putchar(char c, int *counter)
{
    write(1, &c, 1);
    *counter += 1;
}

void    ft_putstr(char *s, int *counter)
{
    while (*s)
    {
        ft_putchar(*s, counter);
        s++;
    }
}

void    print_lower_hex(unsigned int nbr, int *counter)
{
    char    *s;

    s = "0123456789abcdef";
    if (nbr >= 16)
    {
        print_lower_hex(nbr / 16, counter);
        print_lower_hex(nbr % 16, counter);
    }
    else
        ft_putchar(s[nbr], counter);
}

void    print_upper_hex(unsigned int nbr, int *counter)
{
    char    *s;

    s = "0123456789ABCDEF";
    if (nbr >= 16)
    {
        print_upper_hex(nbr / 16, counter);
        print_upper_hex(nbr % 16, counter);
    }
    else
        ft_putchar(s[nbr], counter);
}

void    put_hexa(unsigned long address, int *counter)
{
    char    *s;

    s = "0123456789abcdef";
    if (address >= 16)
        put_hexa(address / 16, counter);
    ft_putchar(s[address % 16], counter);
}

void    print_address(unsigned long address, int *counter)
{
    ft_putstr("0x", counter);
    put_hexa(address, counter);
}

void    ft_putnbr(int n, int *counter)
{
    unsigned int    nbr;
    int             t;

    t = 0;
    if (n < 0)
    {
        n = (n + 1);
        n = -n;
        t = 1;
    }
    nbr = n;
    nbr += t;
    if (nbr > 9)
        ft_putnbr(nbr / 10, counter);
    ft_putchar(nbr % 10 + '0', counter);
}

void    ft_putunbr(unsigned int nbr, int *counter)
{
    if (nbr >= 10)
    {
        ft_putunbr(nbr / 10, counter);
        ft_putunbr(nbr % 10, counter);
    }
    else
        ft_putchar(nbr + '0', counter);
}