# 컴파일러 설정
CXX = c++
# 컴파일러 플래그: 모든 경고 활성화, 추가 경고 활성화, 경고를 오류로 처리, C++98 표준 사용
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# 소스 파일 목록
SRCS = main.cpp Harl.cpp

# 오브젝트 파일 목록 (소스 파일 확장자를 .o로 변경)
OBJS = $(SRCS:.cpp=.o)

# 최종 실행 파일 이름
NAME = harl

# 기본 규칙: 'all'은 최종 실행 파일을 빌드합니다.
all: $(NAME)

# 최종 실행 파일을 만드는 규칙
# $(OBJS)에 의존하며, 모든 오브젝트 파일을 링크하여 $(NAME)을 생성합니다.
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

# .cpp 파일을 .o 파일로 컴파일하는 규칙
# $<는 첫 번째 의존성 파일(.cpp)을, $@는 타겟 파일(.o)을 의미합니다.
%.o: %.cpp Harl.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 'clean' 규칙: 빌드 과정에서 생성된 오브젝트 파일을 삭제합니다.
clean:
	rm -f $(OBJS)

# 'fclean' 규칙: 'clean' 작업을 포함하여 최종 실행 파일까지 모두 삭제합니다.
fclean: clean
	rm -f $(NAME)

# 're' 규칙: 'fclean'으로 모두 삭제한 후 'all'을 통해 다시 빌드합니다.
re: fclean all

# .PHONY: 가짜 타겟을 지정하여, 해당 이름의 파일이 있어도 규칙이 실행되도록 합니다.
.PHONY: all clean fclean re
