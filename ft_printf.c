#include "ft_printf.h"

void	print_data(t_data *data)
{
	printf("----------------------------\n");
	printf("Part => %s\n", data->part);
	printf("Minus => %d\n", data->minus);
	printf("Plus => %d\n", data->plus);
	printf("Point => %d\n", data->point);
	printf("Zeroes => %d\n", data->zeroes);
	printf("HashSign => %d\n", data->hashSign);
	printf("MinFieldWidth => %d\n", data->minFieldWidth);
	printf("Space => %d\n", data->space);
	printf("Specifier => %c\n", data->specifier);
	printf("-----------------------------\n");
}


char	*slice(const char *s, size_t a, size_t b)
{
	size_t	len;
	size_t	i;
	char	*res;

	len = b - a;
	res = (char *) malloc ((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (a < b && i < len)
	{
		res[i] = s[a];
		a++;
		i++;
	}
	res[i] = 0;
	return (res);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}


int	is_flag(char c)
{
	return (c == '#' || c == ' ' || c == '0' ||\
	c == '.' || c == '-' || c == '+');
}

int		is_specifier(char c)
{
	return (c == 'd' || c == 's' || c == 'x' || c == 'X' || c == 'i'\
	|| c == 'u' || c == 'c' || c == '%');
}

char	*get_part(const char *format)
{
	size_t	i;

	i = 0;
	while (format[i] && !ft_isalpha(format[i]) && format[i] != '%')
		i++;
	return (slice(format, 0, i + 1));
}

char	get_specifier(const char *format)
{
	size_t	i;

	i = 0;
	while (format[i] && !ft_isalpha(format[i]) && format[i] != '%')
		i++;
	return (format[i]);
}

size_t	get_point(t_data *data, size_t i)
{
	int	point;

	i += (data->part[i] == '.');
	point = 0;
	while (data->part[i] && ft_isdigit(data->part[i]))
	{
		point = (point * 10) + (data->part[i] - '0');
		i++;
	}
	data->point = point;
	return (i);
}

size_t	get_zeroes(t_data *data, size_t i)
{
	int	zeroes;

	zeroes = 0;
	while (data->part[i] && ft_isdigit(data->part[i]))
	{
		zeroes = zeroes * 10 + (data->part[i] - '0');
		i++;
	}
	data->zeroes = zeroes;
	return (i);
}

size_t	get_min_field_width(t_data *data, size_t i)
{
	int	min_field_width;

	min_field_width = 0;
	while (data->part[i] && ft_isdigit(data->part[i]))
	{
		min_field_width = (min_field_width * 10) + (data->part[i] - '0');
		i++;
	}
	data->minFieldWidth = min_field_width;
	return (i);
}

void	parse_data(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->part[i])
	{
		if (data->part[i] == '-' || data->part[i] == '+' || data->part[i] == ' ' || data->part[i] == '#')
		{
			if (data->part[i] == '-')
				data->minus = EXIST;
			else if (data->part[i] == '+')
				data->plus = EXIST;
			else if (data->part[i] == ' ')
				data->space = EXIST;
			else if (data->part[i] == '#')
				data->hashSign = EXIST;
			i++;
		}
		else
		{
			if (data->part[i] == '.')
				i = get_point(data, i);
			else if (data->part[i] == '0')
				i = get_zeroes(data, i);
			else if (ft_isdigit(data->part[i]) && data->part[i] != '0')
				i = get_min_field_width(data, i);
			else
				i++;
		}
	}
}

void	set_ap(t_data *data, va_list *ap)
{
	char	specifier;

	specifier = data->specifier;
	if (specifier == 'd' || specifier == 'i')
		data->nbr = va_arg(*ap, int);
	else if (specifier == 'c')
		data->c = va_arg(*ap, int);
	else if (specifier == 's')
		data->s = va_arg(*ap, char *);
	else if (specifier == 'x' || specifier == 'X' || specifier == 'u')
		data->u_nbr = va_arg(*ap, unsigned int);
	else if (specifier == 'p')
		data->ul_nbr = va_arg(*ap, unsigned long long);
	else if (specifier == '%')
		data->c = '%';
	return ;
}

t_data *get_data(const char *format, va_list *ap)
{
	t_data *data;

	data = (t_data *) malloc (sizeof(t_data));
	if (!data)
		return (NULL);
	data->hashSign = NOT_EXIST;
	data->minFieldWidth = NOT_EXIST;
	data->minus = NOT_EXIST;
	data->plus = NOT_EXIST;
	data->point = NOT_EXIST;
	data->space = NOT_EXIST;
	data->zeroes = NOT_EXIST;
	data->part = get_part(format);
	data->specifier = get_specifier(format);
	set_ap(data, ap);
	parse_data(data);
	clarify_data(data);
	return (data);
}

int	ft_printf(const char *format, ...)
{
	size_t	i;
	va_list	ap;
	t_data	*data;
	int		counter;

	counter = 0;
	data = NULL;
	va_start(ap, format);
	i = -1;
	while (format[++i])
	{
		if (format[i] != '%')
			ft_putchar(format[i], &counter);
		else
		{
			data = get_data(format + i + 1, &ap);
			data->counter = &counter;
			exec_data(data);
			i += ft_strlen(data->part);
			free(data->part);
			free(data);
			// print_data(data);
			data = NULL;
		}
	}
	va_end(ap);
	return (counter);
}

// int	main(void)
// {
// 	ft_printf("%2s", "");
// }