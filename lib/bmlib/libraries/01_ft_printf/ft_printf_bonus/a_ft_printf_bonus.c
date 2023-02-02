/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_ft_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 11:48:20 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/07/01 11:05:19 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf_bonus.h"

int	ft_printf(const char *inp_str, ...)
{
	va_list	args;
	ssize_t	rslt;

	va_start(args, inp_str);
	rslt = ft_read(inp_str, args);
	va_end(args);
	return (rslt);
}
/*
int	main(void)
{
	char	*NUll = NULL;
	char	*N;
	char	*p = "HELLO";
	int		result;
	int		oresult;

	printf("\n\t\t\t     ***MANDATORY***\n");
	printf("\n--FT_PRINTF--							--PRINTF--\n\n");
	result = ft_printf("char:	 -%c-", 'c');
	printf("							");
	oresult = printf("char:	 -%c-", 'c');
	printf("\n");

	result += ft_printf("string:  -%s-", "Hello World");
	printf("						");
	oresult += printf("string:  -%-s-", "Hello World");
	printf("\n");
	result += ft_printf("strNULL: -%s-", NUll);
	printf("						");
	oresult += printf("strNULL: -%s-", NUll);
	printf("\n");

	result += ft_printf("pointer: -%p-", p);
	printf("						");
	oresult += printf("pointer: -%p-", p);
	printf("\n");
	printf("RETURN: %d							RETURN: %d\n", result, oresult);
	N = (char *)-1;
	result += ft_printf("pointer: -1 -%p-", N);
	printf("				");
	oresult += printf("pointer: -1 -%p-", N);
	printf("\n");
	printf("RETURN: %d							RETURN: %d\n", result, oresult);
	N = (char *)0;
	result += ft_printf("pointer: 0  -%p-", N);
	printf("						");
	oresult += printf("pointer: 0  -%p-", N);
	printf("\n");
	printf("RETURN: %d							RETURN: %d\n", result, oresult);
	N = (char *)1;
	result += ft_printf("pointer: 1  -%p-", N);
	printf("						");
	oresult += printf("pointer: 1  -%p-", N);
	printf("\n");
	printf("RETURN: %d							RETURN: %d\n", result, oresult);
	N = (char *)15;
	result += ft_printf("pointer: 15 -%p-", N);
	printf("						");
	oresult += printf("pointer: 15 -%p-", N);
	printf("\n");

	result += ft_printf("decimal: -%d-", 12345678);
	printf("						");
	oresult += printf("decimal: -%d-", 12345678);
	printf("\n");
	result += ft_printf("decimal: -%d-", -12345678);
	printf("						");
	oresult += printf("decimal: -%d-", -12345678);
	printf("\n");
	result += ft_printf("decimal: -%d-", 0);
	printf("							");
	oresult += printf("decimal: -%d-", 0);
	printf("\n");

	result += ft_printf("unsigned: -%u-", -1);
	printf("						");
	oresult += printf("unsigned: -%u-", -1);
	printf("\n");
	result += ft_printf("unsigned: -%u-", 0);
	printf("							");
	oresult += printf("unsigned: -%u-", 0);
	printf("\n");
	result += ft_printf("unsigned: -%u-", 4003001);
	printf("						");
	oresult += printf("unsigned: -%u-", 4003001);
	printf("\n");

	result += ft_printf("x: -%x-", -1234);
	printf("							");
	oresult += printf("x: -%x-", -1234);
	printf("\n");
	result += ft_printf("x: -%x-", 0);
	printf("								");
	oresult += printf("x: -%x-", 0);
	printf("\n");
	result += ft_printf("x: -%x-", 1234);
	printf("							");
	oresult += printf("x: -%x-", 1234);
	printf("\n");

	result += ft_printf("X: -%X-", -1234);
	printf("							");
	oresult += printf("X: -%X-", -1234);
	printf("\n");
	result += ft_printf("X: -%X-", 0);
	printf("								");
	oresult += printf("X: -%X-", 0);
	printf("\n");
	result += ft_printf("X: -%X-", 1234);
	printf("							");
	oresult += printf("X: -%X-", 1234);
	printf("\n");
	printf("RETURN: %d							RETURN: %d\n", result, oresult);
	
	printf("\n\t\t\t\t***BONUS***\n");
	printf("\n--FT_PRINTF--							--PRINTF--\n\n");
	result += ft_printf("#x: -%#x-", -1234);
	printf("						");
	oresult += printf("#x: -%#x-", -1234);
	printf("\n");
	result += ft_printf("#x: -%#x-", 0);
	printf("								");
	oresult += printf("#x: -%#x-", 0);
	printf("\n");
	result += ft_printf("#x: -%#x-", 1234);
	printf("							");
	oresult += printf("#x: -%#x-", 1234);
	printf("\n");
	result += ft_printf("#x: -%#x-", 1);
	printf("							");
	oresult += printf("#x: -%#x-", 1);
	printf("\n");
	result += ft_printf("#x: -%#x-", 9);
	printf("							");
	oresult += printf("#x: -%#x-", 9);
	printf("\n");
	result += ft_printf("#X: -%#X-", -1);
	printf("						");
	oresult += printf("#X: -%#X-", -1);
	printf("\n");
	result += ft_printf("#X: -%#X-", 0);
	printf("								");
	oresult += printf("#X: -%#X-", 0);
	printf("\n");
	result += ft_printf("#X: -%#X-", 15);
	printf("							");
	oresult += printf("#X: -%#X-", 15);
	printf("\n");
	result += ft_printf("#X: -%#X-", 101);
	printf("							");
	oresult += printf("#X: -%#X-", 101);
	printf("\n");
	result += ft_printf("#X: -%#X-", -101);
	printf("						");
	oresult += printf("#X: -%#X-", -101);
	printf("\n");

	result += ft_printf(" i: -% i-", 1234);
	printf("							");
	oresult += printf(" i: -% i-", 1234);
	printf("\n");
	result += ft_printf(" d: -% d-", 0);
	printf("							");
	oresult += printf(" d: -% d-", 0);
	printf("\n");
	result += ft_printf(" d: -% d-", -1234);
	printf("							");
	oresult += printf(" d: -% d-", -1234);
	printf("\n");
	printf("RETURN: %d							RETURN: %d\n", result, oresult);
	result += ft_printf(" s: -% s-", "STRING string");
	printf("						");
	oresult += printf(" s: -% s-", "STRING string");
	printf("\n");
	printf("RETURN: %d							RETURN: %d\n", result, oresult);
	result += ft_printf(" s: -% s-", "");
	printf("								");
	oresult += printf(" s: -% s-", "");
	printf("\n");
	printf("RETURN: %d							RETURN: %d\n", result, oresult);

	result += ft_printf("+i: -%+i-", 1234);
	printf("							");
	oresult += printf("+i: -%+i-", 1234);
	printf("\n");
	printf("RETURN: %d							RETURN: %d\n", result, oresult);
	result += ft_printf("+d: -%+d-", 0);
	printf("							");
	oresult += printf("+d: -%+d-", 0);
	printf("\n");
	printf("RETURN: %d							RETURN: %d\n", result, oresult);
	result += ft_printf("+d: -%+d-", -1234);
	printf("							");
	oresult += printf("+d: -%+d-", -1234);
	printf("\n");
	printf("RETURN: %d							RETURN: %d\n", result, oresult);
	result += ft_printf("+ d: -%+ d-", -1234);
	printf("							");
	oresult += printf("+ d: -%+ d-", -1234);
	printf("\n");
	printf("RETURN: %d							RETURN: %d\n", result, oresult);
	result += ft_printf("- %#x -", 0);
	printf("								");
	oresult += printf("- %#x -", 0);
	printf("\n");
	printf("RETURN: %d							RETURN: %d\n", result, oresult);
	result += ft_printf("- % 1s-", "");
	printf("								");
	oresult += printf("- % 1s-", "");
	printf("\n");

	printf("RETURN: %d							RETURN: %d\n", result, oresult);
}*/
