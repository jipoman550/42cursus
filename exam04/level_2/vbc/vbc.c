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

/**
 * factor: 최우선순위 처리 (괄호 및 단일 숫자)
 * 1. 현재 토큰이 '(' 인지 확인한다. (accept)
 * - 맞다면, 새로운 하위 수식이 시작된 것이므로 expr()을 재귀 호출한다.
 * - expr() 결과가 NULL이면 에러이므로 상위로 NULL을 전달한다.
 * - 수식이 끝난 후 반드시 ')' 가 와야 하므로 확인한다. (expect)
 * - ')' 가 없다면 이미 생성된 하위 수식 트리를 메모리 해제(destroy)하고 에러를 반환한다.
 * 2. 현재 토큰이 숫자(isdigit)인지 확인한다.
 * - 숫자라면, 수식의 최소 단위인 VAL 타입의 노드를 생성한다.
 * - 문자열 포인터를 다음으로 한 칸 이동시킨다.
 * 3. 둘 다 아니라면 예상치 못한 토큰이므로 unexpected() 에러를 출력하고 NULL을 반환한다.
 */
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

/**
 * term: 중간 우선순위 처리 (곱셈 '*')
 * 1. 곱셈의 왼쪽 항이 될 factor()를 하나 가져온다.
 * 2. factor() 결과가 NULL이면 즉시 에러를 반환한다.
 * 3. 반복문(while)을 통해 연달아 나오는 '*' 연산자를 확인한다. (accept)
 * - '*'를 발견하면, 오른쪽 항이 될 다음 factor()를 가져온다.
 * - 만약 오른쪽 factor()가 NULL이라면(에러), 지금까지 만든 왼쪽 트리를 해제하고 NULL을 반환한다.
 * - 성공했다면, 기존 트리(왼쪽)와 새 factor(오른쪽)를 자식으로 갖는 MULTI 노드를 생성하여 갱신한다.
 * 4. 최종적으로 조립된 MULTI 트리를 반환한다.
 */
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

/**
 * expr: 최저 우선순위 처리 (덧셈 '+')
 * 1. 덧셈의 왼쪽 항이 될 term()을 하나 가져온다.
 * 2. term() 결과가 NULL이면 즉시 에러를 반환한다.
 * 3. 반복문(while)을 통해 연달아 나오는 '+' 연산자를 확인한다. (accept)
 * - '+'를 발견하면, 오른쪽 항이 될 다음 term()을 가져온다.
 * - 만약 오른쪽 term()이 NULL이라면(에러), 지금까지 만든 왼쪽 트리를 해제하고 NULL을 반환한다.
 * - 성공했다면, 기존 트리(왼쪽)와 새 term(오른쪽)을 자식으로 갖는 ADD 노드를 생성하여 갱신한다.
 * 4. 최종적으로 조립된 ADD 트리를 반환한다.
 */
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

/**
 * parse_expr: 파싱 시작점 및 최종 검증
 * 1. 가장 낮은 우선순위 함수인 expr()을 호출하여 파싱을 시작한다.
 * 2. expr()이 NULL을 반환했다면 이미 내부에서 에러가 처리된 것이므로 그대로 NULL을 반환한다.
 * 3. 전체 수식 파싱이 끝났는데도 문자열 포인터가 끝('\0')에 도달하지 않았는지 확인한다.
 * - 예: "1+2)" 같이 괄호가 남는 경우.
 * - 문자가 남아있다면 unexpected() 에러를 출력하고 트리를 해제한 뒤 NULL을 반환한다.
 * 4. 모든 검증을 통과한 최종 트리를 반환한다.
 */
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