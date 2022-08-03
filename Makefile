NAME		:= libftprintf.a
CCW			:= cc -Wall -Wextra -Werror
SRCS		:= ft_printf.c combination.c execute.c functions.c functionalities.c
OBJS		:= $(SRCS:.c=.o)

all :		$(NAME)

bonus: $(NAME)

$(NAME) :	$(OBJS)
	@printf "\033[1;32m --> The archive has been created successfully! <--\n"

$(OBJS) :
	$(CCW) -c $(@:.o=.c) -o $@
	@ar rcs $(NAME) $@

clean :
	rm -f $(OBJS)

fclean :	clean
	rm -f $(NAME)

re :		fclean	all

.PHONY : all clean fclean re bonus
