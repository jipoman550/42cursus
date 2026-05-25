#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>

class Zombie
{
	private:
		std::string	_name; // 멤버 변수 구분을 위한 '_' 접두어 사용

	public:
		// 중요: new Zombie[N]으로 배열을 만들 때 호출되는 인자 없는 생성자
		Zombie();

		// 특정 이름을 가진 좀비를 직접 만들 때 사용하는 생성자 (ex00용)
		Zombie(std::string name);

		// 좀비가 죽을 때 메시지를 남기는 소멸자
		~Zombie();

		// 자신을 알리는 함수
		void	announce(void);

		// 중요: 배열로 생성된 후 이름을 나중에 설정하기 위한 함수
		void	setName(std::string name);
};

// 좀비 군단을 만드는 외부 함수 프로토타입
Zombie*	zombieHorde(int N, std::string name);

#endif
