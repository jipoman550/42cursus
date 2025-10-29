// tests_mix.c
#define _GNU_SOURCE
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* 너의 구현 심볼 */
int ft_vfscanf(FILE *f, const char *format, va_list ap);

/* 동일 입력으로 ft_vfscanf를 돌리기 위한 래퍼 */
static int ft_sscanf(const char *input, const char *fmt, ...) {
    int ret;
    va_list ap;
    FILE *m = fmemopen((void*)input, strlen(input), "r");
    if (!m) { perror("fmemopen"); return -9999; }
    va_start(ap, fmt);
    ret = ft_vfscanf(m, fmt, ap);
    va_end(ap);
    fclose(m);
    return ret;
}

/* 케이스 정의: fmt, sig(예: "ds", "scd"), in */
typedef struct {
    const char *fmt;
    const char *sig;   /* d/s/c 만 포함, 변환 개수는 strlen(sig) */
    const char *in;
} Test;

/* 결과 저장용 */
typedef struct {
    int scanf_ret, ft_ret;
    char scanf_out[512];
    char ft_out[512];
    int pass;
} Result;

/* 값 출력 도우미 */
static void append_vis_str(char *dst, size_t cap, const char *s) {
    size_t n = strlen(dst);
    if (n >= cap) return;
    if (!s) { snprintf(dst+n, cap-n, "(null)"); return; }
    for (const unsigned char *p=(const unsigned char*)s; *p && n+4<cap; ++p) {
        unsigned char c = *p;
        if (c=='\n') { dst[n++]='\\'; dst[n++]='n'; }
        else if (c=='\t'){ dst[n++]='\\'; dst[n++]='t'; }
        else if (c=='\r'){ dst[n++]='\\'; dst[n++]='r'; }
        else if (c=='\\'){ dst[n++]='\\'; dst[n++]='\\'; }
        else if (c<32 || c==127) { n += snprintf(dst+n, cap-n, "\\x%02X", c); }
        else dst[n++]=c;
    }
    dst[n]='\0';
}

/* sig 순서대로 값을 요약 문자열로 만들기 */
static void build_out_string(char *dst, size_t cap,
                             const char *sig,
                             int *di, char cs[6], char *ss[6]) {
    dst[0]='\0';
    size_t n = 0;
    int id=0, ic=0, is=0;
    for (size_t i=0; sig[i]; ++i) {
        if (n+8 >= cap) break;
        if (i) n += snprintf(dst+n, cap-n, " | ");
        if (sig[i]=='d') {
            n += snprintf(dst+n, cap-n, "d=%d", di[id++]);
        } else if (sig[i]=='c') {
            n += snprintf(dst+n, cap-n, "c=%u", (unsigned)(unsigned char)cs[ic++]);
        } else if (sig[i]=='s') {
            n += snprintf(dst+n, cap-n, "s=");
            if (n < cap) {
                append_vis_str(dst, cap, ss[is++]);
                n = strlen(dst);
            }
        }
    }
}

/* 실제 실행: 하나의 테스트케이스를 표준/ft 각각 수행하고 비교 */
static void run_one(const Test *t, Result *r) {
    /* 캡처 버퍼들 (표준/ft 각각 따로) */
    int d1[6]={0}, d2[6]={0};
    char c1[6]={0}, c2[6]={0};
    char s1[6][256]={{0}}, s2[6][256]={{0}};
    char *s1p[6] = { s1[0], s1[1], s1[2], s1[3], s1[4], s1[5] };
    char *s2p[6] = { s2[0], s2[1], s2[2], s2[3], s2[4], s2[5] };

    /* sig 파싱: 개수 카운트 */
    int nd=0, nc=0, ns=0;
    for (const char *p=t->sig; *p; ++p) {
        if (*p=='d') nd++;
        else if (*p=='c') nc++;
        else if (*p=='s') ns++;
    }

    /* 표준 sscanf 호출: sig 길이에 따라 분기 */
    {
        const char *p = t->sig;
        /* 최대 6개까지 지원 */
        if      (!p[1]) {
            if (p[0]=='d') r->scanf_ret = sscanf(t->in, t->fmt, &d1[0]);
            else if (p[0]=='c') r->scanf_ret = sscanf(t->in, t->fmt, &c1[0]);
            else r->scanf_ret = sscanf(t->in, t->fmt, s1p[0]);
        }
        else if (!p[2]) {
            if      (p[0]=='d'&&p[1]=='d') r->scanf_ret = sscanf(t->in, t->fmt, &d1[0], &d1[1]);
            else if (p[0]=='d'&&p[1]=='s') r->scanf_ret = sscanf(t->in, t->fmt, &d1[0], s1p[0]);
            else if (p[0]=='d'&&p[1]=='c') r->scanf_ret = sscanf(t->in, t->fmt, &d1[0], &c1[0]);
            else if (p[0]=='s'&&p[1]=='d') r->scanf_ret = sscanf(t->in, t->fmt, s1p[0], &d1[0]);
            else if (p[0]=='s'&&p[1]=='s') r->scanf_ret = sscanf(t->in, t->fmt, s1p[0], s1p[1]);
            else if (p[0]=='s'&&p[1]=='c') r->scanf_ret = sscanf(t->in, t->fmt, s1p[0], &c1[0]);
            else if (p[0]=='c'&&p[1]=='d') r->scanf_ret = sscanf(t->in, t->fmt, &c1[0], &d1[0]);
            else if (p[0]=='c'&&p[1]=='s') r->scanf_ret = sscanf(t->in, t->fmt, &c1[0], s1p[0]);
            else if (p[0]=='c'&&p[1]=='c') r->scanf_ret = sscanf(t->in, t->fmt, &c1[0], &c1[1]);
            else r->scanf_ret = 0;
        }
        else if (!p[3]) {
            /* 3개 조합: 모두 나열 (간단/흔한 조합만) */
            if      (p[0]=='d'&&p[1]=='s'&&p[2]=='c') r->scanf_ret = sscanf(t->in, t->fmt, &d1[0], s1p[0], &c1[0]);
            else if (p[0]=='d'&&p[1]=='d'&&p[2]=='s') r->scanf_ret = sscanf(t->in, t->fmt, &d1[0], &d1[1], s1p[0]);
            else if (p[0]=='s'&&p[1]=='d'&&p[2]=='c') r->scanf_ret = sscanf(t->in, t->fmt, s1p[0], &d1[0], &c1[0]);
            else if (p[0]=='c'&&p[1]=='s'&&p[2]=='d') r->scanf_ret = sscanf(t->in, t->fmt, &c1[0], s1p[0], &d1[0]);
            else if (p[0]=='c'&&p[1]=='c'&&p[2]=='c') r->scanf_ret = sscanf(t->in, t->fmt, &c1[0], &c1[1], &c1[2]);
            else if (p[0]=='s'&&p[1]=='s'&&p[2]=='s') r->scanf_ret = sscanf(t->in, t->fmt, s1p[0], s1p[1], s1p[2]);
            else r->scanf_ret = sscanf(t->in, t->fmt, &d1[0], &d1[1], &d1[2]); /* fallback */
        }
        else {
	    size_t L = strlen(p);
	    if (L==4 && p[0]=='d'&&p[1]=='s'&&p[2]=='c'&&p[3]=='d')
		r->scanf_ret = sscanf(t->in, t->fmt, &d1[0], s1p[0], &c1[0], &d1[1]);
	    else if (L==5 && p[0]=='d'&&p[1]=='s'&&p[2]=='c'&&p[3]=='d'&&p[4]=='s')
		r->scanf_ret = sscanf(t->in, t->fmt, &d1[0], s1p[0], &c1[0], &d1[1], s1p[1]);  // ★ 추가
	    else if (L==5 && p[0]=='c'&&p[1]=='d'&&p[2]=='s'&&p[3]=='c'&&p[4]=='d')
		r->scanf_ret = sscanf(t->in, t->fmt, &c1[0], &d1[0], s1p[0], &c1[1], &d1[1]);
	    else if (L==6 && p[0]=='d'&&p[1]=='s'&&p[2]=='d'&&p[3]=='c'&&p[4]=='s'&&p[5]=='c')
		r->scanf_ret = sscanf(t->in, t->fmt, &d1[0], s1p[0], &d1[1], &c1[0], s1p[1], &c1[1]);
	    else
		r->scanf_ret = sscanf(t->in, t->fmt, &d1[0], &d1[1], &d1[2], &d1[3]); // fallback (가능하면 줄이자)
}
    }

    /* ft_sscanf 호출 (동일 분기) */
    {
        const char *p = t->sig;
        if      (!p[1]) {
            if (p[0]=='d') r->ft_ret = ft_sscanf(t->in, t->fmt, &d2[0]);
            else if (p[0]=='c') r->ft_ret = ft_sscanf(t->in, t->fmt, &c2[0]);
            else r->ft_ret = ft_sscanf(t->in, t->fmt, s2p[0]);
        }
        else if (!p[2]) {
            if      (p[0]=='d'&&p[1]=='d') r->ft_ret = ft_sscanf(t->in, t->fmt, &d2[0], &d2[1]);
            else if (p[0]=='d'&&p[1]=='s') r->ft_ret = ft_sscanf(t->in, t->fmt, &d2[0], s2p[0]);
            else if (p[0]=='d'&&p[1]=='c') r->ft_ret = ft_sscanf(t->in, t->fmt, &d2[0], &c2[0]);
            else if (p[0]=='s'&&p[1]=='d') r->ft_ret = ft_sscanf(t->in, t->fmt, s2p[0], &d2[0]);
            else if (p[0]=='s'&&p[1]=='s') r->ft_ret = ft_sscanf(t->in, t->fmt, s2p[0], s2p[1]);
            else if (p[0]=='s'&&p[1]=='c') r->ft_ret = ft_sscanf(t->in, t->fmt, s2p[0], &c2[0]);
            else if (p[0]=='c'&&p[1]=='d') r->ft_ret = ft_sscanf(t->in, t->fmt, &c2[0], &d2[0]);
            else if (p[0]=='c'&&p[1]=='s') r->ft_ret = ft_sscanf(t->in, t->fmt, &c2[0], s2p[0]);
            else if (p[0]=='c'&&p[1]=='c') r->ft_ret = ft_sscanf(t->in, t->fmt, &c2[0], &c2[1]);
            else r->ft_ret = 0;
        }
        else if (!p[3]) {
            if      (p[0]=='d'&&p[1]=='s'&&p[2]=='c') r->ft_ret = ft_sscanf(t->in, t->fmt, &d2[0], s2p[0], &c2[0]);
            else if (p[0]=='d'&&p[1]=='d'&&p[2]=='s') r->ft_ret = ft_sscanf(t->in, t->fmt, &d2[0], &d2[1], s2p[0]);
            else if (p[0]=='s'&&p[1]=='d'&&p[2]=='c') r->ft_ret = ft_sscanf(t->in, t->fmt, s2p[0], &d2[0], &c2[0]);
            else if (p[0]=='c'&&p[1]=='s'&&p[2]=='d') r->ft_ret = ft_sscanf(t->in, t->fmt, &c2[0], s2p[0], &d2[0]);
            else if (p[0]=='c'&&p[1]=='c'&&p[2]=='c') r->ft_ret = ft_sscanf(t->in, t->fmt, &c2[0], &c2[1], &c2[2]);
            else if (p[0]=='s'&&p[1]=='s'&&p[2]=='s') r->ft_ret = ft_sscanf(t->in, t->fmt, s2p[0], s2p[1], s2p[2]);
            else r->ft_ret = ft_sscanf(t->in, t->fmt, &d2[0], &d2[1], &d2[2]);
        }
	else {
	    size_t L = strlen(p);
	    if (L==4 && p[0]=='d'&&p[1]=='s'&&p[2]=='c'&&p[3]=='d')
		r->ft_ret = ft_sscanf(t->in, t->fmt, &d2[0], s2p[0], &c2[0], &d2[1]);
	    else if (L==5 && p[0]=='d'&&p[1]=='s'&&p[2]=='c'&&p[3]=='d'&&p[4]=='s')
		r->ft_ret = ft_sscanf(t->in, t->fmt, &d2[0], s2p[0], &c2[0], &d2[1], s2p[1]);  // ★ 추가
	    else if (L==5 && p[0]=='c'&&p[1]=='d'&&p[2]=='s'&&p[3]=='c'&&p[4]=='d')
		r->ft_ret = ft_sscanf(t->in, t->fmt, &c2[0], &d2[0], s2p[0], &c2[1], &d2[1]);
	    else if (L==6 && p[0]=='d'&&p[1]=='s'&&p[2]=='d'&&p[3]=='c'&&p[4]=='s'&&p[5]=='c')
		r->ft_ret = ft_sscanf(t->in, t->fmt, &d2[0], s2p[0], &d2[1], &c2[0], s2p[1], &c2[1]);
	    else
		r->ft_ret = ft_sscanf(t->in, t->fmt, &d2[0], &d2[1], &d2[2], &d2[3]); // fallback
	}
    }

    /* 출력 요약 만들기 */
    build_out_string(r->scanf_out, sizeof r->scanf_out, t->sig, d1, c1, s1p);
    build_out_string(r->ft_out,    sizeof r->ft_out,    t->sig, d2, c2, s2p);

    /* PASS 판정: ret 동일 && (ret>0이면 값 동일) */
    r->pass = (r->scanf_ret == r->ft_ret);
    if (r->pass && r->scanf_ret > 0) {
        /* ret만큼 비교 — 간단히 전체 문자열 비교로 처리 */
        r->pass = (strcmp(r->scanf_out, r->ft_out) == 0);
    }
}

/* 다양한 케이스 정의 — 모두 3필드(fmt, sig, in)로 통일 */
static const Test CASES[] = {
    /* 단일 */
    {"%d",  "d", ""},                // 빈 입력
    {"%d",  "d", "-"},               // 부호만
    {"%d",  "d", "  +42"},
    {"%d",  "d", "abc"},
    {"%s",  "s", "hello"},
    {" %s", "s", "   world  tail"},
    {"%s",  "s", "   "},
    {"%c",  "c", "A"},
    {"%c",  "c", "  B"},             // 공백도 %c로 읽힘

    /* 이중 */
    {"%d %d", "dd", "12 34"},
    {"%d%s",  "ds", "7xyz"},
    {"%s %d", "sd", "abc 99"},
    {"%c%s",  "cs", "Zhi"},
    {"%s%c",  "sc", "wow !"},
    {"%d %c", "dc", "65 ?"},
    {"%c %d", "cd", "  @ 123"},

    /* 삼중 */
    {"%d %s %c", "dsc", "1 ab !"},
    {"%s %d %c", "sdc", "xy 10 #"},
    {"%c%s%d",   "csd", "Ahi42"},
    {"%c %c %c", "ccc", "x y z"},
    {"%s%s%s",   "sss", "a bb ccc"},

    /* 리터럴 섞기 */
    {"X:%d Y:%s Z:%c", "dsc", "X:10 Y:ok Z:Q"},
    {"[%d]-{%s}-(%c)", "dsc", "[-12]-{foo}-(!)"},
    {"d=%d,s=%s,c=%c", "dsc", "d=7,s=hi,c=@"},

    /* 넷 이상 */
    {"%d %s %c %d", "dscd", "10 a ! -5"},
    {"%s %d %s %c", "sdsc", "L 4 Oops ?"},   // sig의 공백 제거
    {"%c %d %s %c %d", "cdscd", "@ 9 aa ! 3"},
    {"%d %s %d %c %s %c", "dsdcsc", "1 a 2 ! b ?"},

    /* --- 입력 고갈(EOF)/빈 입력 계열 --- */
    {"%d",   "d",  ""},               // d: empty
    {"%s",   "s",  ""},               // s: empty
    {"%c",   "c",  ""},               // c: empty

    {"%d",   "d",  "-"},              // d: sign only
    {"%d",   "d",  "- \t"},           // d: sign only + ws
    {" %d",  "d",  "   "},            // d: ws then EOF (공백만)

    {"%s",   "s",  "     "},          // s: spaces only
    {" %s",  "s",  "   "},            // s: ws+EOF

    {"%c",   "c",  "\n"},             // c: newline
    {"%c",   "c",  "\tA"},            // c: tabs

    /* --- 리터럴 불일치/부분 성공 --- */
    {"%dX",  "d",  "123X"},           // ok
    {"%dX",  "d",  "123Y"},           // bad
    {"X%d",  "d",  "Y10"},            // first literal bad

    /* --- %d 경계 --- */
    {"%d",   "d",  "abc"},            // non-digit first
    {"%d",   "d",  "0000123"},        // leading zeros
    {"%d",   "d",  "-0009"},          // sign+zeros
    {"%d",   "d",  "42xyz"},          // digits+alpha
    {"%d",   "d",  "+7"},             // plus

    /* --- %s 경계 --- */
    {"%s",   "s",  "abc def"},        // stops at space
    {" %s",  "s",  "   hello"},       // leading ws
    {"%s",   "s",  "line1\nline2"},   // newline stop

    /* --- %c 경계 --- */
    {"%c",   "c",  " A"},             // reads space
    {"%d%c", "dc", "65?"},            // after int

    /* --- 이중/삼중/그 이상 조합: 뒤에서 실패 --- */
    {"%d %s","ds", "10 abc"},         // ok
    {"%d %s","ds", "10   "},          // s fails → ret=1
    {"%s %d","sd", "abc xyz"},        // d fails → ret=1
    {"%c %s %d","csd","  @ hi 99"},
    {"%d %s %c %d","dscd","1 a ! -2"},

    /* --- 개행/탭 섞인 포맷 공백 --- */
    {"%d \t %s", "ds", "12 \t\t xyz"},
    {"%d\n%s",   "ds", "5\nok"},

    /* --- 5~6개 조합 --- */
    {"%d %s %c %d %s",       "dscds", "1 a ! 2 bb"},
    {"%d %s %d %c %s %c",    "dsdcsc", "1 a 2 ! b ?"},
};

static const int NCASE = sizeof(CASES)/sizeof(CASES[0]);

int main(void) {
    int pass=0, fail=0;
    Result *R = calloc(NCASE, sizeof(Result));
    if (!R) { perror("calloc"); return 1; }

    for (int i=0;i<NCASE;i++) {
        /* sig에서 공백은 무시 (위 케이스 하나에 의도적으로 넣어놨음) */
        char sigbuf[8]={0}; int k=0;
        for (const char *p=CASES[i].sig; *p && k<6; ++p) if (*p=='d'||*p=='s'||*p=='c') sigbuf[k++]=*p;
        Test t = { CASES[i].fmt, sigbuf, CASES[i].in };
        run_one(&t, &R[i]);
        if (R[i].pass) pass++; else fail++;
    }

    /* 리포트 */
    puts("--------------------------------------------------------------------------------");
    puts("SUMMARY: scanf(sscanf) vs ft_vfscanf (same inputs)");
    puts("--------------------------------------------------------------------------------");
    printf("%-3s | %-14s | %-30s | %-6s | %-6s | %-28s | %-28s | %s\n",
           "No", "FMT", "INPUT(head)", "retS", "retF", "out(scanf)", "out(ft)", "OK");
    puts("--------------------------------------------------------------------------------");
    for (int i=0;i<NCASE;i++) {
        char head[31]; head[0]='\0';
        strncpy(head, CASES[i].in, 30); head[30]='\0';
        printf("%-3d | %-14s | %-30s | %-6d | %-6d | %-28s | %-28s | %s\n",
               i+1, CASES[i].fmt, head, R[i].scanf_ret, R[i].ft_ret,
               R[i].scanf_out, R[i].ft_out, R[i].pass?"PASS":"FAIL");
    }
    puts("--------------------------------------------------------------------------------");
    printf("TOTAL: %d  PASS: %d  FAIL: %d\n", NCASE, pass, fail);
    free(R);
    return (fail? 1: 0);
}

