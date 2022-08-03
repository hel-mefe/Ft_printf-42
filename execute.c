#include "ft_printf.h"

int is_exist(int n)
{
    return (n != NOT_EXIST);
}

void    print_spaces(int n, int *counter)
{
    int i;

    i = -1;
    while (++i < n)
        ft_putchar(' ', counter);
}

void    print_zeroes(int n_zeroes, int *counter)
{
    int i;

    i = -1;
    while (++i < n_zeroes)
        ft_putchar('0', counter);
}

void    exec_int(t_data *data)
{
    int nbr;

    nbr = data->nbr;
    if (!is_exist(data->minus))
    {
        print_spaces(data->minFieldWidth, data->counter);
        if (is_exist(data->plus) && data->nbr >= 0)
            ft_putchar('+', data->counter);
        if (is_exist(data->space))
            ft_putchar(' ', data->counter);
        if (data->nbr < 0)
            ft_putchar('-', data->counter);
        print_zeroes(data->zeroes, data->counter);
        ft_putnbr(nbr, data->counter);
    }
    else
    {
        print_zeroes(data->zeroes, data->counter);
        if (is_exist(data->plus) && data->nbr >= 0)
            ft_putchar('+', data->counter);
        if (is_exist(data->space))
            ft_putchar(' ', data->counter);
        if (data->nbr < 0)
            ft_putchar('-', data->counter);
        ft_putnbr(nbr, data->counter);
        print_spaces(data->minFieldWidth, data->counter);
    }
}

void    exec_string(t_data *data)
{
    int     len;
    int     i;
    int     points;

    if (!is_exist(data->minus))
        print_spaces(data->minFieldWidth, data->counter);
    points = data->point;
    if (is_exist(data->point))
        len = min(abs_z(points), (int ) ft_strlen(data->s));
    else
        len = ft_strlen(data->s);
    i = 0;
    if (!data->s)
        ft_putstr("(null)", data->counter);
    while (i < len)
    {
        ft_putchar(data->s[i], data->counter);
        i++;
    }
    if (is_exist(data->minus))
        print_spaces(data->minFieldWidth, data->counter);
    return ;
}

void    exec_uint(t_data *data)
{
    if (is_exist(data->minus))
    {
        print_zeroes(data->zeroes, data->counter);
        ft_putunbr(data->u_nbr, data->counter);
        print_spaces(data->minFieldWidth, data->counter);
    }
    else
    {
        print_spaces(data->minFieldWidth, data->counter);
        print_zeroes(data->zeroes, data->counter);
        ft_putunbr(data->u_nbr, data->counter);
    }
}

void    exec_char(t_data *data)
{
    if (!is_exist(data->minus))
        print_spaces(data->minFieldWidth, data->counter);
    ft_putchar(data->c, data->counter);
    if (is_exist(data->minus))
        print_spaces(data->minFieldWidth, data->counter);
}

void    exec_hex(t_data *data)
{
    if (!is_exist(data->minus))
        print_spaces(data->minFieldWidth, data->counter);
    if (is_exist(data->hashSign) && data->specifier == 'x' && data->u_nbr != 0)
        ft_putstr("0x", data->counter);
    else if (is_exist(data->hashSign) && data->specifier == 'X' && data->u_nbr != 0)
        ft_putstr("0X", data->counter);
    if (is_exist(data->zeroes))
        print_zeroes(data->zeroes, data->counter);
    if (data->specifier == 'x')
        print_lower_hex(data->u_nbr, data->counter);
    else if (data->specifier == 'X')
        print_upper_hex(data->u_nbr, data->counter);
    if (is_exist(data->minus))
        print_spaces(data->minFieldWidth, data->counter);
}

void    exec_address(t_data *data)
{
    if (!is_exist(data->minus))
        print_spaces(data->minFieldWidth, data->counter);
    print_address(data->ul_nbr, data->counter);
    if (is_exist(data->minus))
        print_spaces(data->minFieldWidth, data->counter);
}

void    exec_data(t_data *data)
{
    if (data->specifier == 'd' || data->specifier == 'i')
        exec_int(data);
    else if (data->specifier == 'u')
        exec_uint(data);
    else if (data->specifier == 'u')
        exec_uint(data);
    else if (data->specifier == 's')
        exec_string(data);
    else if (data->specifier == 'x' || data->specifier == 'X')
        exec_hex(data);
    else if (data->specifier == 'c' || data->specifier == '%')
        exec_char(data);
    else if (data->specifier == 'p')
        exec_address(data);
    return ;
}