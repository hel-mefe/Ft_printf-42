#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>

# define NOT_EXIST INT_MIN
# define EXIST 1

typedef struct s_data
{
	int					*counter;
	int					zeroes;
	int					minus;
	int					plus;
	int					point;
	int					hashSign;
	char				specifier;
	int					space;
	int					minFieldWidth;
	int					nbr;
	unsigned long		u_nbr;
	unsigned long long	ul_nbr;
	long long			l_nbr;
	char				*s;
	char				c;
	char				*part;
}	t_data;

int	is_exist(int n);
int	ft_printf(const char *format, ...);

void    clarify_uint(t_data *data);
void    clarify_int(t_data *data);
void    clarify_hex(t_data *data);
void    clarify_string(t_data *data);
void    clarify_address(t_data *data);
void    clarify_data(t_data *data);

int     abs_z(int x);
int     max(int x, int y);
int     min(int x, int y);

int		number_len(long long nbr);
int		hex_len(long long nbr);
int 	address_len(unsigned long address);
size_t  ft_strlen(const char *s);

void    ft_putchar(char c, int *counter);
void    ft_putstr(char *s, int *counter);
void    print_lower_hex(unsigned int nbr, int *counter);
void    print_upper_hex(unsigned int nbr, int *counter);
void    put_hexa(unsigned long address, int *counter);
void    print_address(unsigned long address, int *counter);
void    ft_putnbr(int n, int *counter);
void    ft_putunbr(unsigned int nbr, int *counter);

void    print_spaces(int n, int *counter);
void    print_zeroes(int n_zeroes, int *counter);
void    exec_int(t_data *data);
void    exec_string(t_data *data);
void    exec_uint(t_data *data);
void    exec_char(t_data *data);
void    exec_hex(t_data *data);
void    exec_address(t_data *data);
void    exec_data(t_data *data);

#endif