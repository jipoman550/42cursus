#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int main() {
	// 1. Data 객체 생성 및 초기화
	Data myData;
	myData.id = 42;
	myData.name = "Arthur Dent";

	// 2. 원본 객체 정보 및 메모리 주소값 출력
	std::cout << "========== [ ORIGINAL DATA ] ==========" << std::endl;
	std::cout << "Memory Address : " << &myData << std::endl;
	std::cout << "Data ID        : " << myData.id << std::endl;
	std::cout << "Data Name      : " << myData.name << std::endl;
	std::cout << std::endl;

	// 3. 직렬화(Serialize): 주소값을 정수(uintptr_t)로 변환
	uintptr_t serializedPtr = Serializer::serialize(&myData);
	std::cout << "========== [ SERIALIZATION ] ==========" << std::endl;
	std::cout << "Serialized (uintptr_t) : " << serializedPtr << std::endl;
	std::cout << std::endl;

	// 4. 역직렬화(Deserialize): 정수를 다시 포인터(Data*)로 되돌림
	Data* deserializedPtr = Serializer::deserialize(serializedPtr);
	std::cout << "========== [ DESERIALIZATION ] ========" << std::endl;
	std::cout << "Deserialized (Data *)  : " << deserializedPtr << std::endl;
	std::cout << std::endl;

	// 5. 검증: 원본 주소와 되돌린 주소 비교 (시각적 피드백 제공)
	std::cout << "========== [ VALIDATION ] =============" << std::endl;
	if (&myData == deserializedPtr) {
		std::cout << "Result: [SUCCESS] The addresses match perfectly!" << std::endl;
	} else {
		std::cout << "Result: [FAIL] The addresses do not match." << std::endl;
	}

	// 6. 무결성 확인: 역직렬화된 포인터를 통해 내부 실제 값 접근 및 출력
	std::cout << std::endl;
	std::cout << "========== [ DATA INTEGRITY ] =========" << std::endl;
	std::cout << "Deserialized ID   : " << deserializedPtr->id << std::endl;
	std::cout << "Deserialized Name : " << deserializedPtr->name << std::endl;
	if (myData.id == deserializedPtr->id && myData.name == deserializedPtr->name) {
		std::cout << "Result: [SUCCESS] Data remained intact!" << std::endl;
	}

	return 0;
}