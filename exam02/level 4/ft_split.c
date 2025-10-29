#include <stdlib.h> // malloc 함수 사용을 위해 포함

// 주어진 문자가 공백(스페이스, 탭, 개행 문자)인지 확인하는 헬퍼 함수
int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

// 문자열에서 단어의 개수를 세는 헬퍼 함수
int count_words(char *str)
{
    int count = 0;
    int in_word = 0; // 현재 단어 안에 있는지 여부를 나타내는 플래그

    while (*str) // 문자열의 끝까지 순회
    {
        if (is_whitespace(*str)) // 현재 문자가 공백인 경우
        {
            in_word = 0; // 단어 밖으로 나옴
        }
        else if (in_word == 0) // 현재 문자가 공백이 아니고, 이전에 단어 밖에 있었다면
        {
            in_word = 1; // 새로운 단어의 시작
            count++;     // 단어 개수 증가
        }
        str++; // 다음 문자로 이동
    }
    return (count); // 총 단어 개수 반환
}

// 문자열을 단어로 분리하여 문자열 배열로 반환하는 함수
char **ft_split(char *str)
{
    char **result;     // 분리된 단어들을 저장할 문자열 배열
    int num_words;     // 총 단어 개수
    int i = 0;         // result 배열의 인덱스
    int word_start;    // 현재 단어의 시작 인덱스
    int word_len;      // 현재 단어의 길이
    int k;             // 단어 복사 시 사용할 인덱스

    // 단어 개수를 세어 total_words 변수에 저장
    num_words = count_words(str);

    // 단어들을 저장할 배열을 할당. 마지막 NULL을 위해 num_words + 1 크기로 할당
    result = (char **)malloc(sizeof(char *) * (num_words + 1));
    if (result == NULL) // 메모리 할당 실패 시 NULL 반환
        return (NULL);

    // 원본 문자열을 순회하며 단어를 찾고 분리
    while (*str)
    {
        // 공백 문자 건너뛰기
        while (*str && is_whitespace(*str))
            str++;

        if (!*str) // 문자열의 끝에 도달했다면 루프 종료
            break;

        // 단어의 시작 인덱스 저장
        word_start = 0; // 현재 str 포인터를 기준으로 단어의 시작점을 0으로 가정
        word_len = 0;   // 단어 길이 초기화

        // 단어의 끝까지 이동하며 길이 계산
        while (str[word_len] && !is_whitespace(str[word_len]))
            word_len++;

        // 현재 단어를 저장할 메모리 할당
        result[i] = (char *)malloc(sizeof(char) * (word_len + 1));
        if (result[i] == NULL) // 메모리 할당 실패 시
        {
            // 이전에 할당된 메모리들을 해제하고 NULL 반환 (오류 처리)
            while (i > 0)
            {
                i--;
                free(result[i]);
            }
            free(result);
            return (NULL);
        }

        // 단어를 새로 할당된 메모리로 복사
        k = 0;
        while (k < word_len)
        {
            result[i][k] = str[word_start + k];
            k++;
        }
        result[i][k] = '\0'; // 단어의 끝에 NULL 문자 추가

        // 다음 단어를 찾기 위해 str 포인터 이동
        str += word_len;
        i++; // result 배열의 다음 인덱스로 이동
    }

    result[i] = NULL; // 배열의 마지막에 NULL 포인터 추가
    return (result);  // 분리된 단어 배열 반환
}

/*단어 개수를 센다는 개념
str = " abc apple kkeum sisung "
단어 개수 = 4? 아하*/