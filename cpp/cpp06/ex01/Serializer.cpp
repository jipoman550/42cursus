#include "Serializer.hpp"

// 생성자, 복사 생성자, 대입 연산자, 소멸자는 private으로 선언되었으며,
// 인스턴스화를 막기 위한 용도이므로 빈 구현체를 가집니다.
Serializer::Serializer() {}
Serializer::Serializer(const Serializer& other) { (void)other; }
Serializer& Serializer::operator=(const Serializer& other) {
	(void)other;
	return *this;
}
Serializer::~Serializer() {}

// 직렬화: Data 객체의 포인터를 정수형으로 변환
uintptr_t Serializer::serialize(Data* ptr) {
	// reinterpret_cast를 사용하여 포인터를 정수형(uintptr_t)으로 강제 변환
	return reinterpret_cast<uintptr_t>(ptr);
}

// 역직렬화: 정수형을 다시 Data 객체의 포인터로 변환
Data* Serializer::deserialize(uintptr_t raw) {
	// reinterpret_cast를 사용하여 정수형(uintptr_t)을 다시 포인터 타입으로 강제 변환
	return reinterpret_cast<Data*>(raw);
}