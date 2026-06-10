#ifndef DATA_HPP
#define DATA_HPP

#include <string>

/**
 * @brief 직렬화/역직렬화 테스트를 위한 단순 데이터 구조체
 *
 * 과제 요구사항에 따라 내부에 복잡한 로직 없이
 * 샘플 데이터(int, std::string)만 저장하도록 구현되었습니다.
 */
struct Data {
	int id;
	std::string name;
};

#endif