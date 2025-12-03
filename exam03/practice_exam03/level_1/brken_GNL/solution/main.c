// 파일 1개만 test
#include "gnl.h" // get_next_line 함수 선언이 포함된 헤더 파일
#include <stdio.h>  // printf, perror 사용
#include <fcntl.h>  // open 함수 사용
#include <unistd.h> // close 함수 사용
#include <stdlib.h> // free 함수 사용 (get_next_line의 반환값을 해제해야 함)

