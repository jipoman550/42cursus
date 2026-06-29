# --- Executable Name ---
NAME = RPN

# --- Compiler and Flags ---
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# --- Source Files ---
SRCS = main.cpp \
	   RPN.cpp

# --- Object Files ---
OBJS = $(SRCS:.cpp=.o)

# --- Header Files ---
# 헤더 파일이 변경될 경우, 이를 포함하는 소스 파일들이 재컴파일되도록 의존성을 추가합니다.
DEPS = RPN.hpp

# --- Main Rule ---
# 'make' 명령어 실행 시 기본적으로 'all' 규칙이 실행됩니다.
all: $(NAME)

# --- Linking Rule ---
# 오브젝트 파일들을 링크하여 최종 실행 파일을 생성합니다.
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

# --- Compilation Rule ---
# .cpp 소스 파일을 .o 오브젝트 파일로 컴파일하는 규칙입니다.
# 헤더 파일 의존성($(DEPS))을 명시하여 헤더 변경 시 재컴파일을 보장합니다.
%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- Clean Rule ---
# 컴파일된 오브젝트 파일들을 삭제합니다.
clean:
	rm -f $(OBJS)

# --- Fclean Rule ---
# 오브젝트 파일과 최종 실행 파일을 모두 삭제합니다.
fclean: clean
	rm -f $(NAME)

# --- Re Rule ---
# 'fclean'과 'all'을 순차적으로 실행하여 프로젝트를 완전히 새로 빌드합니다.
re: fclean all

# --- Phony Targets ---
# 파일 이름과 혼동될 수 있는 규칙들을 .PHONY로 선언합니다.
.PHONY: all clean fclean re