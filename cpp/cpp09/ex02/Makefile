# 실행 파일 이름
NAME = PmergeMe

# 컴파일러 및 플래그 설정
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# 소스 파일 목록
SRCS = main.cpp \
	   PmergeMe.cpp

OBJS = $(SRCS:.cpp=.o)

# 파일 제거 명령어
RM = rm -f

# 기본 규칙: all
# $(NAME)을 빌드합니다.
all: $(NAME)

# 실행 파일 빌드 규칙
# 오브젝트 파일들을 링크하여 최종 실행 파일을 생성합니다.
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

# 오브젝트 파일 빌드 규칙 (암묵적 규칙 재정의)
# .cpp 파일과 헤더 파일이 변경될 때마다 오브젝트 파일을 다시 컴파일합니다.
%.o: %.cpp PmergeMe.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean 규칙
# 빌드 과정에서 생성된 오브젝트 파일들을 삭제합니다.
clean:
	$(RM) $(OBJS)

# fclean 규칙
# clean 규칙에서 삭제하는 파일들과 최종 실행 파일까지 모두 삭제합니다.
fclean: clean
	$(RM) $(NAME)

# re 규칙
# fclean을 실행하여 모든 빌드 산출물을 삭제한 후, 다시 all을 실행하여 전체를 새로 빌드합니다.
# relink를 방지하고 깨끗한 상태에서 다시 빌드할 때 유용합니다.
re: fclean all

# 가상 타겟 선언
# all, clean, fclean, re는 실제 파일 이름이 아니므로 .PHONY로 선언합니다.
.PHONY: all clean fclean re
