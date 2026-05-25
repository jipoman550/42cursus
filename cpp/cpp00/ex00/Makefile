# 1. 프로그램 이름 설정
NAME		= megaphone

# 2. 컴파일러 및 플래그 설정
# C++ 과제이므로 c++ 컴파일러를 사용합니다.
CXX			= c++
# -Wall -Wextra -Werror 플래그는 필수입니다.
# -std=c++98 플래그를 통해 C++98 표준 준수를 명시합니다.
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

# 3. 소스 파일 및 오브젝트 파일 설정
SRCS		= megaphone.cpp
OBJS		= $(SRCS:.cpp=.o)

# 4. 기본 규칙 (all)
# 'make' 또는 'make all' 입력 시 실행됩니다.
all: $(NAME)

# 5. 실행 파일 생성 규칙
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

# 6. 오브젝트 파일 생성 규칙 (암시적 규칙 활용)
# .cpp 파일을 .o 파일로 컴파일합니다.
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 7. 생성된 오브젝트 파일 삭제 (clean)
clean:
	rm -f $(OBJS)

# 8. 오브젝트 파일 및 실행 파일 모두 삭제 (fclean)
fclean: clean
	rm -f $(NAME)

# 9. 빌드 초기화 후 다시 빌드 (re)
re: fclean all

# 10. 파일 이름과 타겟 이름이 겹치는 것을 방지 (Phony)
.PHONY: all clean fclean re