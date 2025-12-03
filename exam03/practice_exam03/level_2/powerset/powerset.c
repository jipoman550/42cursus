#include "powerset.h"

// 전역 변수로 관리
int g_target;
int *g_set;
int g_total_count;

// write 함수를 사용하여 출력하는 도우미 함수
void safe_write(const char *buf, size_t len)
{
    // write는 허용된 함수
    write(1, buf, len);
}

// 현재까지 선택된 부분집합을 출력합니다.
// 이 함수의 로직은 문제 없이 잘 구현되었습니다.
void print_subset(int *selected, int count)
{
    char buffer[20]; // 숫자를 문자열로 변환하기 위한 임시 버퍼
    int len;

    if (count == 0)
    {
        safe_write("\n", 1); // 빈 집합은 빈 줄 출력
        return;
    }

    for (int i = 0; i < count; i++)
    {
        // 정수 -> 문자열 변환 (itoa가 허용되지 않아 수동 구현)
        int num = selected[i];
        int is_negative = 0;
        char *ptr = buffer + sizeof(buffer) - 1;
        *ptr = '\0';

        if (num == 0)
        {
            *(--ptr) = '0';
        }
        else
        {
            if (num < 0)
            {
                is_negative = 1;
                num = -num;
            }

            while (num > 0)
            {
                *(--ptr) = (num % 10) + '0';
                num /= 10;
            }

            if (is_negative)
            {
                *(--ptr) = '-';
            }
        }

        len = buffer + sizeof(buffer) - 1 - ptr;

        // 원소 출력
        safe_write(ptr, len);

        // 마지막 원소가 아니면 공백 출력
        if (i < count - 1)
            safe_write(" ", 1);
    }
    safe_write("\n", 1);
}

// 재귀를 이용한 백트래킹으로 목표 합 n을 만족하는 부분집합을 찾습니다.
// 목표 합 확인을 종료 조건(Base Case)으로 이동하여 중복 출력을 방지합니다.
void find_subsets(int index, long long current_sum, int *selected, int sel_count)
{
    // 1. 모든 원소를 확인했는지 확인 (종료 조건, Base Case)
    if (index >= g_total_count)
    {
        // 경로의 끝에 도달했을 때, 최종 합을 확인하고 출력합니다.
        if (current_sum == g_target)
        {
            print_subset(selected, sel_count);
        }
        return;
    }
    // ----------------------------------------------------
    // 참고: 이전 코드에 있던 'current_sum == g_target' 체크는 여기서 제거되었습니다.

    // 2. 현재 원소를 포함하지 않는 경우 (Skip)
    find_subsets(index + 1, current_sum, selected, sel_count);

    // 3. 현재 원소를 포함하는 경우 (Take)
    selected[sel_count] = g_set[index];
    find_subsets(index + 1, current_sum + g_set[index], selected, sel_count + 1);
}

int main(int argc, char **argv)
{
    // 입력 인자 수 확인
    if (argc < 2)
        return 0;

    // 1. 입력 파싱 및 메모리 할당
    g_target = atoi(argv[1]);
    g_total_count = argc - 2;

    g_set = (int *)malloc(sizeof(int) * g_total_count);
    if (!g_set)
        return 1; // malloc 실패 시 exit(1)

    for (int i = 0; i < g_total_count; i++)
    {
        g_set[i] = atoi(argv[i + 2]);
    }

    int *selected = (int *)malloc(sizeof(int) * g_total_count);
    if (!selected)
    {
        free(g_set);
        return 1; // malloc 실패 시 exit(1)
    }

    // 2. 부분집합 찾기 시작
    find_subsets(0, 0, selected, 0);

    // 3. 메모리 해제
    free(selected);
    free(g_set);

    return 0;
}
