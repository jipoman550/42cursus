# 실행 파일 이름
NAME = fixed

# 컴파일러 및 플래그
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# 소스 파일 및 오브젝트 파일
SRCS =	main.cpp \
		Fixed.cpp

OBJS = $(SRCS:.cpp=.o)

# 헤더 파일
HDRS = Fixed.hpp

# 기본 규칙: 최종 실행 파일 생성
all: $(NAME)

# 링크 규칙: 오브젝트 파일들을 링크하여 실행 파일 생성
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

# 컴파일 규칙: .cpp 파일을 .o 파일로 컴파일
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean: 오브젝트 파일 삭제
clean:
	rm -f $(OBJS)

# fclean: 실행 파일 및 오브젝트 파일 모두 삭제
fclean: clean
	rm -f $(NAME)

# re: 전체 재컴파일
re: fclean all

.PHONY: all clean fclean re
