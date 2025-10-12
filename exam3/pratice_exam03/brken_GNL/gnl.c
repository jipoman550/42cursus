#include "gnl.h"

// ft_strlen: 문자열 길이를 계산. NULL 입력 처리 추가.
static size_t  ft_strlen(const char *s)
{
    size_t i = 0;
    // 수정 이유: 원래 코드는 s가 NULL일 때 세그멘테이션 폴트 발생 가능.
    // NULL 체크를 추가해 안전하게 0 반환. 방어적 프로그래밍으로 견고함 강화.
    if (!s)
        return 0;
    // 인덱스 방식으로 변경: 포인터 연산(*s) 대신 s[i]로 가독성과 일관성 개선.
    while (s[i])
        i++;
    return i;
}

// ft_strchr: 문자열에서 문자 c를 찾음. NULL 입력과 \0 처리 개선.
static char    *ft_strchr(const char *s, int c)
{
    // 수정 이유: 원래 코드는 s가 NULL일 때 세그멘테이션 폴트 발생.
    // NULL 체크 추가로 안전성 강화.
    if (!s)
        return NULL;
    while (*s)
    {
        // 수정 이유: 원래 *s != c로 비교 후 s++했는데, 바로 c와 비교해 찾으면 해당 포인터 반환.
        // (char)c로 명시적 캐스팅해 타입 일관성 유지.
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    // 수정 이유: 원래는 *s == c일 때 s + 1 반환, \n 찾을 때 다음 문자로 이동하는 버그.
    // 올바른 위치(*s) 반환, \0도 c로 간주 가능하도록 마지막 체크 추가.
    if (*s == (char)c)
        return ((char *)s);
    return NULL;
}

// ft_memcpy: 메모리 복사. off-by-one 버그 수정.
static void    *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i = 0;
    // 수정 이유: 원래 (!dest && !src)로 잘못된 조건, ||로 수정해 둘 다 NULL이면 NULL 반환.
    // NULL 체크로 세그멘테이션 폴트 방지.
    if (!dest && !src)
        return NULL;
    // 수정 이유: 원래 --n > 0 조건은 off-by-one 버그로 n=0일 때 문제 발생.
    // 인덱스 i 사용, i < n으로 정확히 n바이트 복사. 가독성과 안정성 개선.
    while (i < n)
    {
        ((char *)dest)[i] = ((char *)src)[i];
        i++;
    }
    return dest;
}

// ft_memmove: 겹치는 메모리 복사. 잘못된 strlen 사용 제거.
static void    *ft_memmove(void *dest, const void *src, size_t len)
{
    char *d = (char *)dest;
    const char *s = (const char *)src;
    size_t i;
    // 방어적 프로그래밍하지 않아도 됨?
	// if (!dest && !src)
	// 	return (NULL);

    // 수정 이유: 원래 dest == src 체크 후 바로 반환, 유지.
    if (d == s)
        return (dest);
    // 수정 이유: 원래 ft_strlen(src) 사용은 src가 널 종료 문자열일 때만 유효.
    // memmove는 문자열이 아닌 일반 메모리 복사이므로 len 사용.
    // d < s일 때 순방향 복사, d > s일 때 역방향 복사로 겹침 문제 해결.
    if (d < s)
    {
        i = 0;
        while (i < len)
        {
            d[i] = s[i];
            i++;
        }
    }
    else
    {
        // 수정 이유: 원래 n = ft_strlen(src) - 1로 잘못된 길이 계산, off-by-one 버그.
        // len 사용, i = len부터 역순으로 복사해 겹침 방지.
        i = len;
        while (i > 0)
        {
            i--;
            d[i] = s[i];
        }
    }
    return (dest);
}

// str_join_and_free: 두 문자열 결합 후 원래 메모리 해제.
static int str_join_and_free(char **s1, const char *s2, size_t size2)
{
    // 수정 이유: 원래 ft_strlen(*s1)에서 *s1이 NULL일 때 문제.
    // *s1이 NULL이면 size1 = 0으로 처리 (ft_strlen 수정으로 해결).
    size_t size1 = ft_strlen(*s1);
    char *tmp = malloc(size1 + size2 + 1);
    // 수정 이유: malloc 실패 시 원래 *s1 해제 추가.
    // 메모리 누수 방지, *s1을 NULL로 설정해 안전성 강화.
    // 궁금한게 왜 s1에 대해서만 free를 해주는거지?
    if (!tmp)
    {
        free(*s1);
        *s1 = NULL;
        return 1;
    }
    // 수정 이유: *s1이 NULL일 때 memcpy 호출 방지, 조건문 추가.
    if (*s1)
        ft_memcpy(tmp, *s1, size1);
    ft_memcpy(tmp + size1, s2, size2);
    // 수정 이유: 원래 널 종료 처리 없음. tmp[size1 + size2] = '\0' 추가.
    // 문자열이 올바르게 종료되도록 보장.
    tmp[size1 + size2] = '\0';
    free(*s1);
    *s1 = tmp;
    return 0;
}

// gnl: 파일 디스크립터에서 한 줄씩 읽기.
char    *gnl(int fd)
{
    static char b[BUFFER_SIZE + 1] = "";
    char    *ret = NULL;
    char    *tmp;
    ssize_t readbyte;

    // 수정 이유: 원래 fd와 BUFFER_SIZE 유효성 검사 없음.
    // fd < 0 또는 BUFFER_SIZE <= 0일 때 NULL 반환, 잘못된 입력 방지.
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    // 1. Start with the remainder from the last call
    // 질문: "BUFFER_SIZE가 전에 gnl로 읽는 과정에서 \n 이 나오기 전에 끝나서 다음 gnl를 불러야할 때를 대비해서 이런건가?"
    // 답변: 정확히 맞습니다! static char b는 이전 gnl 호출에서 읽은 데이터 중 \n 이후 남은 데이터를 저장.
    // 예: 파일에 "hello\nworld"가 있고, BUFFER_SIZE=5라면 첫 read에서 "hello" 읽음.
    // 첫 gnl 호출에서 "hello\n" 처리 후 b에 "world" 저장. 다음 gnl 호출에서 b의 "world"부터 시작.
    // 수정 이유: 원래 str_add_str로 바로 ret에 b 추가. str_join_and_free로 통일, \n 체크 전에 호출해 남은 데이터 먼저 처리.
    if (str_join_and_free(&ret, b, ft_strlen(b)))
        return NULL;

    // 2. Read until newline or EOF
    while (!(tmp = ft_strchr(ret, '\n')))
    {
        readbyte = read(fd, b, BUFFER_SIZE);
        // 수정 이유: 원래 readbyte == -1만 체크, readbyte <= 0으로 EOF와 에러 처리 통합.
        // readbyte == 0 (EOF)일 때 ret가 비어 있거나 NULL이면 NULL 반환, 아니면 ret 반환.
        if (readbyte <= 0)
        {
            b[0] = '\0'; // 다음 호출을 위해 버퍼 비움.
            if (readbyte == -1 || !ret || ret[0] == '\0')
            {
                free(ret); // 에러 또는 빈 ret 해제.
                return (NULL);
            }
            return ret;
        }
        b[readbyte] = '\0'; // 읽은 데이터 널 종료.
        // 수정 이유: 원래 str_add_str로 처리, str_join_and_free로 통일.
        // readbyte만큼만 추가해 메모리 효율성 개선.
        if (str_join_and_free(&ret, b, readbyte))
            return NULL;
    }

    // 질문: "여기부터 아랫부분은 어떤 기능을 하지는 잘 모르겠음."
    // 답변: 이 부분은 \n을 찾았을 때 줄을 잘라서 반환하고, \n 이후 데이터를 다음 gnl 호출을 위해 저장.
    // 기능:
    // 1. \n까지의 문자열을 final_line에 복사해 반환.
    // 2. \n 이후 데이터를 static b 에 저장해 다음 gnl 호출에서 사용.
    // 예: ret = "hello\nworld", tmp = \n의 위치 -> final_line = "hello\n", b = "world".
    // 수정 이유: 원래 tmp - b + 1로 잘못된 계산, ret 기준으로 line_len 계산.
    // final_line을 새로 할당해 ret와 분리, 메모리 누수 방지.

    // 3. Newline found. Split the string.
    size_t line_len = (tmp - ret) + 1; // \n까지의 길이 (tmp는 \n 위치).
    size_t remainder_len = ft_strlen(tmp + 1); // \n 이후 남은 데이터 길이.

    // Save remainder to static buffer 'b'
    // 수정 이유: 원래 tmp + 1을 b로 이동, ft_memmove로 안전하게 복사.
    // remainder_len + 1로 널 종료 포함.
    ft_memmove(b, tmp + 1, remainder_len + 1);

    // Create the final line to return
    char *final_line = malloc(line_len + 1);
    if (!final_line)
    {
        free(ret); // malloc 실패 시 ret 해제.
        return NULL;
    }
    // 수정 이유: 원래 tmp - b로 계산, ret에서 line_len 만큼 복사로 수정.
    // line_len에 \n 포함, 올바른 줄 복사.
    ft_memcpy(final_line, ret, line_len);
    final_line[line_len] = '\0';

    free(ret); // 원래 ret 해제.
    return final_line;
}
