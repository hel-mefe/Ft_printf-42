#include "ft_printf.h"

int     abs_z(int x)
{
    return ((x < 0) ? 0 : x);
}

int     max(int x, int y)
{
    return ((x > y) ? x : y);
}

int     min(int x, int y)
{
    return ((x < y) ? x : y);
}

void    clarify_int(t_data *data)
{
    if (is_exist(data->plus) || data->nbr < 0)
        data->space = NOT_EXIST;
    if (is_exist(data->zeroes) && is_exist(data->point))
    {
        data->minFieldWidth = data->zeroes;
        data->zeroes = NOT_EXIST;
    }
    if ((is_exist(data->space) || is_exist(data->plus) || data->nbr < 0) && is_exist(data->zeroes))
        data->zeroes -= 1;
    data->hashSign = NOT_EXIST;
    if (is_exist(data->point))
        data->point -= number_len((long long) data->nbr);
    if (is_exist(data->zeroes))
        data->zeroes -= number_len((long long) data->nbr);
    if (is_exist(data->minFieldWidth))
    {
        data->minFieldWidth -= number_len((long long) data->nbr);
        data->minFieldWidth -= abs_z(data->point);
        data->minFieldWidth -= abs_z(data->zeroes);
    }
    if (!is_exist(data->zeroes))
    {
        data->zeroes = data->point;
        data->point = NOT_EXIST;
    }
    if (is_exist(data->minFieldWidth))
        data->minFieldWidth -= (data->nbr < 0);
}

void    clarify_hex(t_data *data)
{
    if (is_exist(data->zeroes) && is_exist(data->point))
    {
        data->minFieldWidth = data->zeroes;
        data->zeroes = NOT_EXIST;
    }
    if (data->hashSign != NOT_EXIST)
	{
        if (is_exist(data->minFieldWidth))
            data->minFieldWidth -= 2;
		if (is_exist(data->zeroes))
			data->zeroes -= 2;
	}
    if (is_exist(data->point))
        data->point -= hex_len((long long) data->u_nbr);
    if (is_exist(data->minFieldWidth))
    {
        data->minFieldWidth -= hex_len((long long) data->u_nbr);
        data->minFieldWidth -= abs_z(data->point);
    }
    data->space = NOT_EXIST;
    data->plus = NOT_EXIST;
    if (!is_exist(data->zeroes))
	{
        data->zeroes = data->point;
		data->point = NOT_EXIST;
	}
	else
		data->zeroes -= hex_len((long long) data->u_nbr);
}

void    clarify_string(t_data *data)
{
    data->space = NOT_EXIST;
    data->hashSign = NOT_EXIST;
    data->plus = NOT_EXIST;
    data->zeroes = NOT_EXIST;
    if (is_exist(data->minFieldWidth))
    {
        if (!is_exist(data->point))
            data->minFieldWidth -= ft_strlen(data->s);
        else
            data->minFieldWidth -= min(data->point, ft_strlen(data->s));
    }
}

void    clarify_address(t_data *data)
{
    data->hashSign = NOT_EXIST;
    data->point = NOT_EXIST;
    data->zeroes = NOT_EXIST;
    data->space = NOT_EXIST;
    data->plus = NOT_EXIST;
    if (data->minFieldWidth != NOT_EXIST)
        data->minFieldWidth -= address_len(data->ul_nbr);
}

void    clarify_character(t_data *data)
{
    if (data->minFieldWidth != NOT_EXIST)
        data->minFieldWidth -= 1;
    data->hashSign = NOT_EXIST;
    data->space = NOT_EXIST;
    data->plus = NOT_EXIST;
    data->zeroes = NOT_EXIST;
    data->point = NOT_EXIST;
}

void    clarify_uint(t_data *data)
{
    if (is_exist(data->plus))
        data->space = NOT_EXIST;
    if (is_exist(data->zeroes) && is_exist(data->point))
    {
        data->minFieldWidth = data->zeroes;
        data->zeroes = NOT_EXIST;
    }
    if ((is_exist(data->space) || is_exist(data->plus)) && is_exist(data->zeroes))
        data->zeroes -= 1;
    data->hashSign = NOT_EXIST;
    if (is_exist(data->point))
        data->point -= number_len((long long) data->u_nbr);
    if (is_exist(data->zeroes))
        data->zeroes -= number_len((long long) data->u_nbr);
    if (is_exist(data->minFieldWidth))
    {
        data->minFieldWidth -= number_len((long long) data->u_nbr);
        data->minFieldWidth -= abs_z(data->point);
        data->minFieldWidth -= abs_z(data->zeroes);
    }
    if (!is_exist(data->zeroes))
    {
        data->zeroes = data->point;
        data->point = NOT_EXIST;
    }
}

void    clarify_data(t_data *data)
{
    if (data->specifier == 'd' || data->specifier == 'i')
        clarify_int(data);
    else if (data->specifier == 'u')
        clarify_uint(data);
    else if (data->specifier == 'x' || data->specifier == 'X')
        clarify_hex(data);
    else if (data->specifier == 's')
        clarify_string(data);
    else if (data->specifier == 'p')
        clarify_address(data);
    else if (data->specifier == '%' || data->specifier == 'c')
        clarify_character(data);
    return ;
}