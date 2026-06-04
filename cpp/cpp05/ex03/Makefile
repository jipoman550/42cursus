# 프로그램 이름
NAME = intern

# 컴파일러 설정
CXX = c++

# 컴파일 플래그 (-std=c++98 필수)
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# 소스 파일 및 오브젝트 파일
SRCS = main.cpp \
	   Bureaucrat.cpp \
	   AForm.cpp \
	   ShrubberyCreationForm.cpp \
	   RobotomyRequestForm.cpp \
	   PresidentialPardonForm.cpp \
	   Intern.cpp

OBJS = $(SRCS:.cpp=.o)

# 기본 타겟
all: $(NAME)

# 실행 파일 생성 규칙
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

# 오브젝트 파일 생성 규칙 (헤더 파일 변경 시 재컴파일 되도록 종속성 추가)
%.o: %.cpp Bureaucrat.hpp AForm.hpp ShrubberyCreationForm.hpp RobotomyRequestForm.hpp PresidentialPardonForm.hpp Intern.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 생성된 오브젝트 파일 제거
clean:
	rm -f $(OBJS)

# 실행 파일 및 오브젝트 파일 모두 제거
fclean: clean
	rm -f $(NAME)

# 재빌드 규칙
re: fclean all

# Phony 타겟 지정
.PHONY: all clean fclean re