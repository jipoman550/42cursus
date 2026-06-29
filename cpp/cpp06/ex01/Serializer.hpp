#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "Data.hpp"
#include <stdint.h> // C++98에서 uintptr_t를 사용하기 위한 헤더

class Serializer {
private:
	// OCCF(Orthodox Canonical Class Form) 규칙 준수
	// 인스턴스화(객체 생성)를 원천 차단하기 위해 모든 생성자 및 대입 연산자를 private에 둡니다.
	Serializer();
	Serializer(const Serializer& other);
	Serializer& operator=(const Serializer& other);
	~Serializer();

public:
	/**
	 * @brief Data 포인터를 부호 없는 정수형(uintptr_t)으로 직렬화
	 */
	static uintptr_t serialize(Data* ptr);

	/**
	 * @brief 부호 없는 정수형(uintptr_t)을 다시 Data 포인터로 역직렬화
	 */
	static Data* deserialize(uintptr_t raw);
};

#endif