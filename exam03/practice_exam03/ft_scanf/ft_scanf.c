#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

/*
 * match_space:
 *  포맷에서 공백(포맷 문자열의 공백이나 %d/%s의 선행 공백 처리용)과 대응.
 *  입력 파일에서 0개 이상의 공백 문자를 소비하고, 마지막으로 읽은 비공백 문자는 ungetc로 복원함.
 *  반환값:
 *    0 : 정상(공백을 소비했거나 소비할 공백이 없음)
 *   -1 : 입력에서 즉시 EOF가 나와 더 이상 진행할 수 없음 (에러/입력종료)
 */
int match_space(FILE *f)
{
    // You may insert code here
	int c;

	/* 읽어들여서 공백이면 계속 소비, 비공백이면 다시 되돌리고 끝냄.
       만약 첫 읽기에서 EOF가 나오면 -1 반환. */
	while (1)
	{
		c = fgetc(f);
		if (c == EOF)
			return -1; /* 더 이상 읽을 수 없음 */
		if (!isspace(c))
		{
			/* 비공백 문자이므로 다음 처리를 위해 되돌림 */
			ungetc(c, f);
			break;
		}
		/* 공백이면 계속 루프해서 더 소비 */
	}
    return (0);
}

/*
 * match_char:
 *  포맷에 있는 특정 리터럴 문자(공백 아님)를 입력에서 일치시킴.
 *  반환값:
 *    1  : 다음 입력 문자가 c였고 소비함 (일치)
 *    0  : 다음 입력 문자가 c가 아님 -> 읽은 문자는 복원하고 실패
 *   -1  : EOF 또는 읽기 불가
 */
int match_char(FILE *f, char c)
{
    // You may insert code here
	int ch = fgetc(f);
	if (ch == EOF)
		return -1;
	if (ch == (unsigned char)c)
		return 1;
	/* 불일치인 경우 읽은 문자를 되돌리고 실패를 알림 */
	ungetc(ch, f);
    return (0);
}

/*
 * scan_char:
 *  %c 처리: 공백을 건너뛰지 않고 정확히 한 문자 읽어 (char *)로 전달된 버퍼에 저장.
 *  반환값:
 *    1  : 성공적으로 한 문자 읽음과 저장
 *   -1  : EOF 또는 읽기 불가
 */
int scan_char(FILE *f, va_list ap)
{
    // You may insert code here
	int ch = fgetc(f);
	if (ch == EOF)
		return -1;

	/* %c는 공백을 무시하지 않으므로 어떤 문자든 하나 받아서 저장 */
	char *dst = va_arg(ap, char *);
    *dst = (char)ch;

    return (1);
}

/*
 * scan_int:
 *  %d 처리: (전제: 선행 공백은 match_space에 의해 처리되었을 수 있음)
 *  동작:
 *    - 선택적 부호 + 또는 - 처리
 *    - 하나 이상의 숫자(0-9)를 읽어 정수 변환
 *    - 숫자가 하나도 없으면 매칭 실패(0)
 *    - 성공 시 읽다 멈춘 비숫자 문자는 ungetc로 복원
 *
 *  반환값:
 *    1  : 성공적으로 정수 읽고 저장
 *    0  : 변환 매칭 실패 (숫자 없음)
 *   -1  : EOF 등 읽기 불가(특히 변환 시작 시 EOF)
 */
int scan_int(FILE *f, va_list ap)
{
    // You may insert code here
    int c;
    long val = 0;
    int sign = 1;
    int any = 0; /* 숫자를 하나 이상 읽었는지 표시 */

    /* 첫 문자 읽기 (부호 또는 숫자 기대) */
    c = fgetc(f);
    if (c == EOF)
        return -1;

    /* 부호 처리: + 또는 -인 경우 다음 문자를 확인해야 함 */
    if (c == '+' || c == '-')
    {
        sign = (c == '-') ? -1 : 1;
        int next = fgetc(f);
        if (next == EOF)
        {
            /* 부호만 있는데 EOF면 되돌림하고 실패(EOF)로 처리 */
            ungetc(c, f);
            return -1;
        }
        if (!isdigit(next))
        {
            /* 부호 다음이 숫자가 아니면 변환 매칭 실패:
               읽은 문자를 원상복구: next와 c 순서대로 되돌림 */
            ungetc(next, f);
            ungetc(c, f);
            return 0;
        }
        /* next는 숫자이므로 처리 시작 */
        val = next - '0';
        any = 1;
    }
    else if (isdigit(c))
    {
        /* 첫 문자가 숫자 */
        val = c - '0';
        any = 1;
    }
    else
    {
        /* 첫 문자가 부호도 숫자도 아니면 매칭 실패: 읽은 문자를 되돌림 */
        ungetc(c, f);
        return 0;
    }

    /* 나머지 숫자들을 연속으로 읽기 */
    while (1)
    {
        int d = fgetc(f);
        if (d == EOF)
            break; /* EOF면 루프 탈출(읽은 숫자는 유효함) */
        if (!isdigit(d))
        {
            /* 숫자 끝, 이 문자는 변환 이후 처리를 위해 되돌림 */
            ungetc(d, f);
            break;
        }
        val = val * 10 + (d - '0');
        /* 주의: overflow 체크는 과제에서 요구하지 않음(생략) */
    }

    if (!any)
    {
        /* 숫자를 하나도 읽지 못한 경우 매칭 실패 */
        return 0;
    }

    /* 최종 저장: va_arg로 넘어온 포인터에 int로 저장 */
    {
        int *dst = va_arg(ap, int *);
        *dst = (int)(val * sign);
    }
    return (1);
}

/*
 * scan_string:
 *  %s 처리: 선행 공백은 이미 match_space에서 처리된다(또는 match_conv에서 호출).
 *  동작:
 *    - 공백이 아닌 문자를 하나 이상 읽어 dst에 저장
 *    - 읽는 도중 공백 또는 EOF가 나오면 그 문자는 ungetc로 복원(EOF 제외)
 *    - 읽은 문자가 하나도 없으면 매칭 실패(0)
 *
 *  반환값:
 *    1  : 성공적으로 문자열을 읽어 저장
 *    0  : 매칭 실패 (문자 하나도 없음)
 *   -1  : EOF 등 읽기 불가 (특히 변환 시작 시 EOF)
 */
int scan_string(FILE *f, va_list ap)
{
	// You may insert code here
    int c;
    char *dst = va_arg(ap, char *);

    /* 첫 문자 읽기 (공백을 건너뛴 상태이므로 첫 문자가 곧 시작이어야 함) */
    c = fgetc(f);
    if (c == EOF)
        return -1;

    if (isspace(c))
    {
        /* 공백이면 매칭 실패: 읽은 문자는 되돌림 */
        ungetc(c, f);
        return 0;
    }

    /* 첫 문자부터 저장 */
    char *p = dst;
    *p++ = (char)c;

    /* 계속해서 공백이 나오기 전까지 저장 */
    while (1)
    {
        int d = fgetc(f);
        if (d == EOF)
            break;
        if (isspace(d))
        {
            /* 공백이 나오면 이 문자를 되돌리고 루프 종료 */
            ungetc(d, f);
            break;
        }
        *p++ = (char)d;
    }

    /* 널 종단 */
    *p = '\0';
    return (1);
}

/* match_conv는 포맷의 변환 문자에 따라 적절한 scan_* 호출 */
int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			/* %c는 공백을 건너뛰지 않음 */
			return scan_char(f, ap);
		case 'd':
			/* %d와 %s는 선행 공백을 건너뛰어야 함 */
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			/* 지원하지 않는 변환이면 실패로 처리 */
			return -1;
	}
}

/*
 * ft_vfscanf:
 *  포맷을 순회하며 위의 헬퍼들을 사용해 입력을 처리함.
 *  반환값: 성공적으로 수행된 변환의 개수. 파일이 처음부터 EOF라면 EOF 반환.
 */
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

/* ft_scanf: 표준 입력(stdin)에서 동작하는 래퍼 */
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
