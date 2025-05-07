#include <stdio.h>

int main() {
    printf("%d", 123);
	printf("\n");
    printf("%d", __INT_MAX__);
	printf("\n");
    //printf("%d", ); 가장 작은 수 넣기
	printf("\n");

	// ?? printf가 출력할 수 있는 decimal 이니까 해줘야할 듯?
    return 0;
}