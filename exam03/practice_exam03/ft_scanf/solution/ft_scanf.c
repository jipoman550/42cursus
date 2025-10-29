#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	// You may insert code here
	int c;

	while (1)
	{
		c = fgetc(f);
		if (c == EOF)
			return -1;
		if (!isspace(c))
		{
			ungetc(c, f);
			break;
		}
	}
	return (0);
}

int match_char(FILE *f, char c)
{
	// You may insert code here
	int ch = fgetc(f);

	if (ch == EOF)
		return -1;
	if (ch == (unsigned char)c)
		return 1;
	ungetc(ch, f);
	return (0);
}

int scan_char(FILE *f, va_list ap)
{
	// You may insert code here
	int ch = fgetc(f);

	if (ch == EOF)
		return -1;

	char *dst = va_arg(ap, char *);
	*dst = (char)ch;
	return (1);
}

int scan_int(FILE *f, va_list ap)
{
	// You may insert code here
	int c;
	long val = 0;
	int sign = 1;
	int any = 0;

	c = fgetc(f);
	if (c == EOF)
		return -1;

	if (c == '+' || c == '-')
	{
		sign = (c == '-') ? -1 : 1;
		int next = fgetc(f);
		if (next == EOF)
		{
			ungetc(c, f);
			return -1;
		}
		if (!isdigit(next))
		{
			ungetc(next, f);
			ungetc(c, f);
			return 0;
		}
		val = next - '0';
		any = 1;

	}
	else if (isdigit(c))
	{
		val = c - '0';
		any = 1;
	}
	else
	{
		ungetc(c, f);
		return 0;
	}

	while (1)
	{
		int d = fgetc(f);
		if (d == EOF)
			break;
		if (!isdigit(d))
		{
			ungetc(d, f);
			break;
		}
		val = val * 10 + (d - '0');
	}

	if (!any)
	{
		return 0;
	}

	int *dst = va_arg(ap, int *);
	*dst = (int)(val * sign);
	return (1);
}

int scan_string(FILE *f, va_list ap)
{
	// You may insert code here
	int c;
	char *dst = va_arg(ap, char *);

	c = fgetc(f);
	if (c == EOF)
		return -1;

	if (isspace(c))
	{
		ungetc(c, f);
		return 0;
	}

	char *p = dst;
	*p++ = (char)c;

	while (1)
	{
		int d = fgetc(f);
		if (d == EOF)
			break;
		if (isspace(d))
		{
			ungetc(d, f);
			break;
		}
		*p++ = (char)d;
	}

	*p = '\0';
	return (1);
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
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
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}

	if (ferror(f))
		return EOF;
	return nconv;
}

int ft_scanf(const char *format, ...)
{
	// ...
	va_list ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	// ...
	va_end(ap);
	return ret;
}
