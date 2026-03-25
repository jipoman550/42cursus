#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP // 중복 포함 방지를 위한 인클루드 가드

# include <string>

class Zombie
{
	private:
		std::string	name; // 좀비의 이름 (private 속성)

	public:
		Zombie(std::string name);	// 생성자: 좀비를 만들 때 이름을 지어줌
		~Zombie();					// 소멸자: 좀비가 사라질 때 할 일을 정의함
		void	announce(void);		// 좀비가 자신을 알리는 함수
};

// 함수 프로토타입: 이 함수들이 외부 파일에 있음을 알려줌
Zombie*	newZombie(std::string name);	// 힙 할당용 함수
void	randomChump(std::string name);	// 스택 할당용 함수

#endif
