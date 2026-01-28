#include "vbc.h"

// --- 제공된 기본 유틸리티 함수 (수정 포함) ---

node *new_node(node n)
{
	node *ret = calloc(1, sizeof(node));
	if (!ret)
		return (NULL);
	*ret = n;
	return (ret);
}

void destroy_tree(node *n)
{
	if (!n)
		return ;
	if (n->type != VAL)
	{
		destroy_tree(n->l);
		destroy_tree(n->r);
	}
	free(n);
}

void unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input\n");
}

int accept(char **s, char c)
{
	if (**s == c) // = 을 == 으로 수정
	{
		(*s)++;
		return (1);
	}
	return (0);
}

int expect(char **s, char c)
{
	if (accept(s, c))
		return (1);
	unexpected(**s);
	return (0);
}

// --- 직접 구현해야 하는 파싱 부분 ---

node *factor(char **s)
{
	if (accept(s, '('))
	{
		node *ret = expr(s);
		if (!ret)
			return (NULL);
		if (!expect(s, ')'))
		{
			destroy_tree(ret);
			return (NULL);
		}
		return (ret);
	}
	else if (isdigit(**s))
	{
		node *ret = new_node((node){VAL, **s - '0', NULL, NULL});
		(*s)++;
		return (ret);
	}
	unexpected(**s);
	return (NULL);
}

node *term(char **s)
{
	node *ret = factor(s);
	if (!ret)
		return (NULL);
	while (accept(s, '*'))
	{
		node *right = factor(s);
		if (!right)
		{
			destroy_tree(ret);
			return (NULL);
		}
		ret = new_node((node){MULTI, 0, ret, right});
	}
	return (ret);
}

node *expr(char **s)
{
	node *ret = term(s);
	if (!ret)
		return (NULL);
	while (accept(s, '+'))
	{
		node *right = term(s);
		if (!right)
		{
			destroy_tree(ret);
			return (NULL);
		}
		ret = new_node((node){ADD, 0, ret, right});
	}
	return (ret);
}

node *parse_expr(char *s)
{
	node *ret = expr(&s);
	if (!ret)
		return (NULL);
	if (*s) // 수식이 끝났는데 문자가 남은 경우 (예: "1+2)")
	{
		unexpected(*s);
		destroy_tree(ret);
		return (NULL);
	}
	return (ret);
}

// --- 메인 로직 ---

int eval_tree(node *tree)
{
	if (tree->type == ADD)
		return (eval_tree(tree->l) + eval_tree(tree->r));
	if (tree->type == MULTI)
		return (eval_tree(tree->l) * eval_tree(tree->r));
	return (tree->val);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	node *tree = parse_expr(argv[1]);
	if (!tree)
		return (1);
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
	return (0);
}