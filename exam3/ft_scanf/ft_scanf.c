/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jaeholee <makest@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:30:29 by Jaeholee          #+#    #+#             */
/*   Updated: 2025/08/13 12:30:31 by Jaeholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	// You may insert code here
	int c = fgetc(f);
	if (c == EOF)
		return (1);
	while (isspace((unsigned char)c))
		c = fgetc(f);
	if (c == EOF)
		return (1);
	return (ungetc(c, f), 0);
}

int match_char(FILE *f, char format)
{
        // You may insert code here
	int c = fgetc(f);
	if (c == EOF || c != format)
		return (1);
	return (0);
}

int scan_char(FILE *f, va_list ap)
{
        // You may insert code here
	int c = fgetc(f);
	if (c == EOF)
		return (1);
	char *va_char = va_arg(ap, char *);
	*va_char = (char)c;
	return (0);
}

int scan_int(FILE *f, va_list ap)
{
	int c = fgetc(f);
	if (c == EOF)
		return 1;
	int sign = 1;
	if (!isdigit((unsigned char)c))
	{
		if ((char)c == '-' || (char)c == '+')
		{
			if ((char)c == '-')
				sign = -1;
			c = fgetc(f);
		}
		else
			return 1;
	}
	if (c == EOF || !isdigit((unsigned char)c))
		return -1;
	/*/
	{
		if (c != EOF)
			ungetc(c, f);
		return -1;
	}
	/*/
	long long num = 0;
	while (isdigit((unsigned char)c))
	{
		num = 10 * num + (c - '0');
		c = fgetc(f);
	}
	if (c != EOF)
		ungetc(c, f);
	int *va_int = va_arg(ap, int *);
	*va_int = sign * num;
	return (0);
}

int scan_string(FILE *f, va_list ap)
{
        // You may insert code here
	//int len = 0;
	int c = fgetc(f);
	if (c == EOF)
		return (1);
	char *va_string = va_arg(ap, char *);
	while (c != EOF && !isspace((unsigned char)c))
	{
		*va_string = (char)c;
		va_string++;
		c = fgetc(f);
		//len++;
	}
	*va_string = '\0';
	if (c != EOF)
		ungetc(c, f);
	return (0);//(len == 0 ? 1 : 0);
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			if (match_space(f))
				return 1;
			return scan_int(f, ap);
		case 's':
			if (match_space(f))
				return 1;
			return scan_string(f, ap);
		case EOF:
			return 1;
		default:
			return 1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			int check = match_conv(f, &format, ap);
			if (check == 1)
				break;
			else if (check == -1)
				return nconv;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == 1)
				break;
		}
		else if (match_char(f, *format) == 1)
			break;
		format++;
	}
	if (ferror(f))
	    return EOF;
	if (feof(f) && nconv == 0)
	    return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	//
	va_list ap;
	va_start(ap, format);
	//
	int ret = ft_vfscanf(stdin, format, ap);
	//
	va_end(ap);
	// 
	return ret;
}
