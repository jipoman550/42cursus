# 1. 프로그램 이름 설정
# 실행 파일의 이름입니다. 과제에서 요구하는 관련성 있는 이름을 설정합니다.
NAME		= phonebook

# 2. 컴파일러 및 플래그 설정
# C++ 과제이므로 c++ 컴파일러를 사용합니다.
CXX			= c++
# -Wall -Wextra -Werror 플래그는 필수입니다.
# -std=c++98 플래그를 통해 C++98 표준 준수를 명시합니다.
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

# 3. 소스 파일 및 오브젝트 파일 설정
# 구현하신 모든 .cpp 파일들을 나열합니다.
SRCS		= main.cpp \
			  PhoneBook.cpp \
			  Contact.cpp

# 소스 파일 이름에서 .cpp를 .o로 바꿔서 오브젝트 파일 리스트를 만듭니다.
OBJS		= $(SRCS:.cpp=.o)

# 4. 기본 규칙 (all)
# 'make' 또는 'make all' 입력 시 실행됩니다.
all: $(NAME)

# 5. 실행 파일 생성 규칙
# 모든 오브젝트 파일이 생성된 후, 이를 링크하여 최종 실행 파일을 만듭니다.
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

# 6. 오브젝트 파일 생성 규칙
# 각 .cpp 파일을 .o 파일로 컴파일합니다.
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 7. 생성된 오브젝트 파일 삭제 (clean)
# 컴파일 과정에서 생성된 .o 파일들만 삭제합니다.
clean:
	rm -f $(OBJS)

# 8. 오브젝트 파일 및 실행 파일 모두 삭제 (fclean)
# clean을 실행한 후 생성된 실행 파일(phonebook)까지 삭제합니다.
fclean: clean
	rm -f $(NAME)

# 9. 빌드 초기화 후 다시 빌드 (re)
# 기존 결과물을 모두 지우고 처음부터 다시 컴파일합니다.
re: fclean all

# 10. 가짜 타겟 (Phony)
# 파일 이름과 타겟 이름이 겹치는 것을 방지하기 위해 사용합니다.
.PHONY: all clean fclean re