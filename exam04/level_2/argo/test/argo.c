#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct	json {
	enum {
		MAP,
		INTEGER,
		STRING
	} type;
	union {
		struct {
			struct pair	*data;
			size_t		size;
		} map;
		int	integer;
		char	*string;
	};
}	json;

typedef struct	pair {
	char	*key;
	json	value;
}	pair;

int	peek(FILE *stream)
{
	int	c = getc(stream);
	ungetc(c, stream);
	return c;
}

int parse_map(json *dst, FILE *stream);
int parse_string(json *dst, FILE *stream);
int	argo(json *dst, FILE *stream);

void	unexpected(FILE *stream)
{
	if (peek(stream) != EOF)
		printf("unexpected token '%c'\n", peek(stream));
	else
		printf("unexpected end of input\n");
}

int	accept(FILE *stream, char c)
{
	if (peek(stream) == c)
	{
		(void)getc(stream);
		return 1;
	}
	return 0;
}

int	expect(FILE *stream, char c)
{
	if (accept(stream, c))
		return 1;
	unexpected(stream);
	return 0;
}

void	free_json(json j)
{
	switch (j.type)
	{
		case MAP:
			for (size_t i = 0; i < j.map.size; i++)
			{
				free(j.map.data[i].key);
				free_json(j.map.data[i].value);
			}
			free(j.map.data);
			break ;
		case STRING:
			free(j.string);
			break ;
		default:
			break ;
	}
}

void	serialize(json j)
{
	switch (j.type)
	{
		case INTEGER:
			printf("%d", j.integer);
			break ;
		case STRING:
			putchar('"');
			for (int i = 0; j.string[i]; i++)
			{
				if (j.string[i] == '\\' || j.string[i] == '"')
					putchar('\\');
				putchar(j.string[i]);
			}
			putchar('"');
			break ;
		case MAP:
			putchar('{');
			for (size_t i = 0; i < j.map.size; i++)
			{
				if (i != 0)
					putchar(',');
				serialize((json){.type = STRING, .string = j.map.data[i].key});
				putchar(':');
				serialize(j.map.data[i].value);
			}
			putchar('}');
			break ;
	}
}

int parse_map(json *dst, FILE *stream)
{
	// 1. { 제거
	if (!expect(stream, '{'))
		return (-1);

	// 2. 초기화
	dst->type = MAP;
	dst->map.data = NULL;
	dst->map.size = 0;

	// 3. } 가 바로 나오면 빈 맵 처리
	if (accept(stream, '}'))
		return (1);

	// 4. 무한 루프
	while (1)
	{
		pair new_pair;
		json key_json;

		// 1. [key 파싱] key는 항상 문자열
		if (parse_string(&key_json, stream) != 1)
			return (-1);
		new_pair.key = key_json.string;

		// 2. [separator 확인] 콜론(:)이 있어야 함
		if (!expect(stream, ':'))
		{
			free(new_pair.key);
			return (-1);
		}

		// 3. [value 파싱] 여기서 재귀 호출! argo를 다시 부름
		if (argo(&new_pair.value, stream) != 1)
		{
			free(new_pair.key);
			return (-1);
		}

		// 4. [메모리 확장] realloc 으로 pair 배열 크기를 하나 늘림
		pair *tmp = realloc(dst->map.data, sizeof(pair) * (dst->map.size + 1));
		if (!tmp)
		{
			free(new_pair.key);
			free_json(new_pair.value);
			return (-1);
		}
		dst->map.data = tmp;
		dst->map.data[dst->map.size] = new_pair;
		dst->map.size++;

		// 5. 다음 요소 확인: 쉼표(,)가 있으면 계속 ㄱ, 없으면 루프 종료
		if (!accept(stream, ','))
			break ;
	}

	// 5. } 제거
	if (!expect(stream, '}'))
		return (-1);

	return (1);
}

int parse_string(json *dst, FILE *stream)
{
	// 1. 시작확인 "
	if (!expect(stream, '"'))
		return (-1);

	// 2. 초기화
	dst->type = STRING;
	dst->string = NULL;
	size_t len = 0;

	// 3. 무한루프: " 가 나오기 or 파일이 끝날 때까지 한 글자씩 읽기
	while (1)
	{
		// 1. 한 글자씩 읽기
		int c = getc(stream);

		// 2. 에러 처리
		if (c == EOF)
		{
			printf("unexpected end of input\n");
			return (-1);
		}

		// 3. 종료조건 (이스케이프 되지 않은 따옴표 발견)
		if (c == '"')
			break ;

		// 4. 이스케이프 처리
		if (c == '\\')
		{
			c = getc(stream);
			if (c != '"' && c != '\\')
			{
				ungetc(c, stream);
				unexpected(stream);
				return (-1);
			}
		}

		// 5. 메모리 확장 및 문자 저장
		char *tmp = realloc(dst->string, len + 2);
		if (!tmp)
			return (-1);
		dst->string = tmp;
		dst->string[len] = (char)c;
		len++;
		dst->string[len] = '\0';
	}

	// 4. 예외처리: 빈문자열("")일 경우 최소한 할당 보장
	if (dst->string == NULL)
		dst->string = calloc(1, 1);

	return (1);
}

int	argo(json *dst, FILE *stream)
{
	int p = peek(stream);

	// 1. 정수처리
	if (isdigit(p) || p == '-')
	{
		dst->type = INTEGER;
		if (fscanf(stream, "%d", &dst->integer) == 1)
			return (1);
		return (-1);
	}
	// 2. 문자열 처리
	else if (p == '"')
		return (parse_string(dst, stream));
	// 3. 맵 처리
	else if (p == '{')
		return (parse_map(dst, stream));
	// 4. 예외처리
	else
	{
		unexpected(stream);
		return (-1);
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	char *filename = argv[1];
	FILE *stream = fopen(filename, "r");
	json	file;
	if (argo (&file, stream) != 1)
	{
		free_json(file);
		return 1;
	}
	serialize(file);
	printf("\n");
}