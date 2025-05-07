#include <stdio.h>

int main() {
    printf("%d", 123);
	printf("\n");
    printf("%d", __INT_MAX__);
	printf("\n");
    printf("%d", -2147483649); //가장 작은 수 넣기
	printf("\n");

	// ?? printf가 출력할 수 있는 decimal 이니까 해줘야할 듯?
	// ?? int의 최소값이랑 최댓값을 넣어 줄 수 있나?
	// 애초에 d,i 는 integer범위만 되는 건데 범위를 넘어버리는 경우에도 %d에 넣을 수 있나?
    return 0;
}