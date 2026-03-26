# 컴파일러 설정
CXX = c++
# 컴파일러 플래그: C++98 표준, Wall(모든 경고), Wextra(추가 경고), Werror(경고를 에러로)
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror

# 실행 파일 이름
NAME = harlFilter

# 소스 파일 목록
SRCS = main.cpp Harl.cpp

# 소스 파일로부터 오브젝트 파일 목록 자동 생성
OBJS = $(SRCS:.cpp=.o)

# 기본 규칙: all
# $(NAME)을 빌드
all: $(NAME)

# 실행 파일($(NAME)) 생성 규칙
# $(OBJS)를 링크하여 $(NAME) 생성
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

# .cpp 파일을 .o 파일로 컴파일하는 규칙
# $<: 첫 번째 의존성 파일 (여기서는 .cpp 파일)
# $@: 타겟 파일 (여기서는 .o 파일)
%.o: %.cpp Harl.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean 규칙: 빌드 과정에서 생성된 오브젝트 파일(.o)들을 삭제
clean:
	rm -f $(OBJS)

# fclean 규칙: clean 규칙을 포함하며, 최종 실행 파일($(NAME))까지 삭제
fclean: clean
	rm -f $(NAME)

# re 규칙: fclean을 실행하여 모든 빌드 파일을 삭제하고, 다시 all을 통해 전체 빌드
re: fclean all

# .PHONY: 가짜 타겟을 명시. all, clean, fclean, re는 실제 파일이 아님을 선언
.PHONY: all clean fclean re
