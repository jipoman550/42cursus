#include <unistd.h> // write 함수를 위해 포함합니다.

// 주어진 문자가 공백 또는 탭인지 확인하는 헬퍼 함수
int is_whitespace(char c) {
    return (c == ' ' || c == '\t');
}

// 문자열을 회전시켜 출력하는 주 함수
void rostring(char *str) {
    int i = 0; // 문자열을 순회하기 위한 인덱스
    int start_first_word = -1; // 첫 번째 단어의 시작 인덱스
    int end_first_word = -1;   // 첫 번째 단어의 끝 인덱스
    int word_count = 0;        // 문자열에 있는 총 단어 수

    // 1. 문자열 앞의 모든 공백/탭을 건너뜀
    while (str[i] && is_whitespace(str[i])) {
        i++;
    }

    // 2. 첫 번째 단어를 찾고 시작/끝 인덱스를 저장
    if (str[i]) { // 공백을 건너뛴 후 내용이 있다면
        start_first_word = i;
        while (str[i] && !is_whitespace(str[i])) {
            i++;
        }
        end_first_word = i - 1; // 첫 번째 단어의 마지막 문자 인덱스
        word_count++;           // 첫 번째 단어를 카운트
    } else { // 문자열이 비어있거나 공백으로만 구성된 경우
        return; // 회전할 단어가 없으므로 함수 종료
    }

    // 3. 첫 번째 단어 이후의 모든 단어를 출력
    int is_first_output_word = 1; // 첫 번째로 출력되는 단어인지 (즉, 첫 번째 단어 제외하고)
                                  // 공백을 앞에 붙여야 하는지 판단하는 플래그

    while (str[i]) {
        // 단어 사이의 모든 공백/탭을 건너뜀
        while (str[i] && is_whitespace(str[i])) {
            i++;
        }

        // 현재 위치에서 단어가 시작된다면
        if (str[i] && !is_whitespace(str[i])) {
            if (!is_first_output_word) { // 첫 번째로 출력되는 단어가 아니라면 앞에 공백을 추가
                write(1, " ", 1);
            }
            is_first_output_word = 0; // 이제는 첫 번째 출력 단어가 아니므로 플래그 변경

            // 현재 단어를 출력
            int current_word_start = i;
            while (str[i] && !is_whitespace(str[i])) {
                i++;
            }
            write(1, &str[current_word_start], i - current_word_start);
            word_count++; // 현재 단어를 카운트
        }
    }

    // 4. 모든 단어가 출력되었다면 (첫 번째 단어 제외)
    // 총 단어 수가 1보다 크고, 첫 번째 출력 단어 뒤에 공백을 붙여야 하는 경우
    if (word_count > 1) {
        write(1, " ", 1); // 첫 번째 단어 앞에 공백을 추가
    }

    // 5. 첫 번째 단어를 맨 뒤에 출력
    if (start_first_word != -1) { // 첫 번째 단어가 유효한 경우
        write(1, &str[start_first_word], end_first_word - start_first_word + 1);
    }
}

int main(int argc, char **argv) {
    if (argc < 2) { // 인자가 하나도 없으면 (프로그램 이름만 있는 경우)
        write(1, "\n", 1); // 개행 문자만 출력
    } else { // 인자가 있다면 첫 번째 인자를 처리
        rostring(argv[1]);
        write(1, "\n", 1); // 결과 출력 후 개행 문자 추가
    }
    return 0; // 프로그램 성공 종료
}