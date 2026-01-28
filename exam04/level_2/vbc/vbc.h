#ifndef VBC_H
# define VBC_H

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <unistd.h>

typedef struct node {
	enum {
		ADD,
		MULTI,
		VAL
	} type;
	int val;
	struct node *l;
	struct node *r;
} node;

// 함수 프로토타입
// 제공된 유틸리티 및 노드 관리 함수
node    *new_node(node n);
void    destroy_tree(node *n);
void    unexpected(char c);
int     accept(char **s, char c);
int     expect(char **s, char c);

// 재귀 하강 파싱 핵심 함수 (직접 추가할 부분)
node    *parse_expr(char *s);
node    *expr(char **s);
node    *term(char **s);
node    *factor(char **s);

// 결과 계산 함수
int     eval_tree(node *tree);

#endif