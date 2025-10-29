// permutations.c — lexicographic next_permutation로 출력 (중복 문자는 안 들어온다고 가정)
// Allowed: write, malloc/free, (puts 불사용)
#include <unistd.h>
#include <stdlib.h>

static size_t my_strlen(const char *s) {
    size_t n = 0; while (s[n]) n++; return n;
}
static void swap(char *a, char *b) { char t = *a; *a = *b; *b = t; }
static void reverse_range(char *s, int l, int r) {
    while (l < r) swap(&s[l++], &s[r--]);
}
static void sort_asc(char *s, size_t n) {               // 단순 선택정렬
    for (size_t i = 0; i + 1 < n; ++i) {
        size_t minj = i;
        for (size_t j = i + 1; j < n; ++j)
            if (s[j] < s[minj]) minj = j;
        if (minj != i) swap(&s[i], &s[minj]);
    }
}
static int next_permutation(char *s, size_t n) {        // 사전식 다음 순열
    if (n < 2) return 0;
    int i = (int)n - 2;
    while (i >= 0 && s[i] >= s[i + 1]) i--;
    if (i < 0) return 0;
    int j = (int)n - 1;
    while (s[j] <= s[i]) j--;
    swap(&s[i], &s[j]);
    reverse_range(s, i + 1, (int)n - 1);
    return 1;
}
static void putline(const char *s, size_t n) {
    write(1, s, n);
    write(1, "\n", 1);
}

int main(int ac, char **av) {
    if (ac != 2) return 0;
    size_t n = my_strlen(av[1]);
    char *buf = (char*)malloc(n + 1);
    if (!buf) return 0;
    for (size_t i = 0; i < n; ++i) buf[i] = av[1][i];
    buf[n] = '\0';

    sort_asc(buf, n);            // 알파벳 순 시작
    do { putline(buf, n); } while (next_permutation(buf, n));

    free(buf);
    return 0;
}

