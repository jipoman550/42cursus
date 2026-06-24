#include "PmergeMe.hpp"
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <algorithm>
#include <iomanip>

// --- Orthodox Canonical Class Form (private) ---

/**
 * @brief 기본 생성자 (비공개).
 * @details 이 클래스는 인스턴스화되지 않으므로 생성자는 private으로 선언됩니다.
 */
PmergeMe::PmergeMe() {}

/**
 * @brief 복사 생성자 (비공개).
 */
PmergeMe::PmergeMe(const PmergeMe& src) { (void)src; }

/**
 * @brief 복사 대입 연산자 (비공개).
 */
PmergeMe& PmergeMe::operator=(const PmergeMe& rhs) { (void)rhs; return *this; }

/**
 * @brief 소멸자 (비공개).
 */
PmergeMe::~PmergeMe() {}

// --- Custom Exception ---

/**
 * @brief 예외 발생 시 "Error" 메시지를 반환합니다.
 */
const char* PmergeMe::ErrorException::what() const throw()
{
	return ("Error");
}

// --- Main execution function ---

/**
 * @brief 인자를 파싱하고, 각 컨테이너에 대해 정렬을 수행 및 시간을 측정하여 결과를 출력합니다.
 * @param argc 인자의 개수.
 * @param argv 인자 배열.
 */
void PmergeMe::process(int argc, char **argv)
{
	// 1. 데이터 파싱 및 컨테이너 채우기
	std::vector<int> vec;
	std::deque<int> deq;

	// 인자들을 순회하며 파싱 (실행 파일 이름 제외)
	for (int i = 1; i < argc; ++i)
	{
		char* endptr;
		// 문자열을 long 타입으로 변환하여 오버플로우를 1차적으로 검사
		long val = std::strtol(argv[i], &endptr, 10);

		// 유효성 검사: 변환 후 남은 문자가 있거나, 숫자가 아니거나, 음수이거나, int 범위를 초과하는 경우 에러
		if (errno == ERANGE || val > INT_MAX || val < 0 || *endptr != '\0' || argv[i] == endptr)
		{
			throw ErrorException();
		}
		// 유효한 양의 정수만 각 컨테이너에 추가
		vec.push_back(static_cast<int>(val));
		deq.push_back(static_cast<int>(val));
	}

	// 검증용 복사본 저장
	std::vector<int> original_vec(vec);

	// 2. 정렬 전 데이터 출력
	std::cout << "Before: ";
	for (size_t i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i] << (i == vec.size() - 1 ? "" : " ");
	}
	std::cout << std::endl;

	// 3. std::vector 정렬 및 시간 측정
	struct timeval start, end;
	gettimeofday(&start, NULL);
	fordJohnsonSort(vec);
	gettimeofday(&end, NULL);
	long vec_time = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);

	// 4. std::deque 정렬 및 시간 측정
	gettimeofday(&start, NULL);
	fordJohnsonSort(deq);
	gettimeofday(&end, NULL);
	long deq_time = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);

	// 5. 정렬 후 데이터 및 결과 출력
	std::cout << "After:  ";
	for (size_t i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i] << (i == vec.size() - 1 ? "" : " ");
	}
	std::cout << std::endl;

	std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << vec_time << " us" << std::endl;
	std::cout << "Time to process a range of " << deq.size() << " elements with std::deque  : " << deq_time << " us" << std::endl;

	// 검증 수행
	std::sort(original_vec.begin(), original_vec.end());
	bool is_vec_sorted = (vec == original_vec);
	std::vector<int> check_deq(deq.begin(), deq.end());
	bool is_deq_sorted = (check_deq == original_vec);

	if (!is_vec_sorted || !is_deq_sorted)
	{
		std::cerr << "Error: Sorting verification failed!" << std::endl;
		if (!is_vec_sorted) std::cerr << "  - std::vector is not sorted correctly!" << std::endl;
		if (!is_deq_sorted) std::cerr << "  - std::deque is not sorted correctly!" << std::endl;
	}
	else
	{
		std::cout << "[Verification] Sorting verification: OK (Both std::vector and std::deque match std::sort)" << std::endl;
	}
}

// --- Jacobsthal Number Generation ---

/**
 * @brief 주어진 크기 n까지의 Jacobsthal 수열을 생성합니다. (vector 버전)
 * @param jacob 수열을 저장할 벡터.
 * @param n 수열에 포함될 원소의 최대 개수.
 */
void PmergeMe::generateJacobsthal(std::vector<int>& jacob, int n)
{
	if (n <= 0)
	{
		return ;
	}
	jacob.push_back(0);
	jacob.push_back(1);
	int last = 1, before_last = 0;
	while (true)
	{
		int next = last + 2 * before_last;
		jacob.push_back(next);
		if (next >= n)
		{
			break;
		}
		before_last = last;
		last = next;
	}
}

/**
 * @brief 주어진 크기 n까지의 Jacobsthal 수열을 생성합니다. (deque 버전)
 * @param jacob 수열을 저장할 덱.
 * @param n 수열에 포함될 원소의 최대 개수.
 */
void PmergeMe::generateJacobsthal(std::deque<int>& jacob, int n)
{
	if (n <= 0)
	{
		return ;
	}
	jacob.push_back(0);
	jacob.push_back(1);
	int last = 1, before_last = 0;
	while (true)
	{
		int next = last + 2 * before_last;
		jacob.push_back(next);
		if (next >= n)
		{
			break ;
		}
		before_last = last;
		last = next;
	}
}

// --- Vector specific Ford-Johnson implementation ---

/**
 * @brief std::vector에 대해 Ford-Johnson (Merge-Insert Sort) 알고리즘을 수행합니다.
 * @param vec 정렬할 벡터.
 */
void PmergeMe::fordJohnsonSort(std::vector<int>& vec)
{
	// 원소 개수가 1개 이하면 이미 정렬된 상태
	if (vec.size() <= 1)
	{
		return ;
	}

	// 홀수 개인 경우 마지막 원소(straggler)를 따로 보관
	int straggler = -1;
	if (vec.size() % 2 != 0)
	{
		straggler = vec.back();
		vec.pop_back();
	}

	// 1. 페어 생성 및 페어 내 정렬: (큰 값, 작은 값)
	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i < vec.size(); i += 2)
	{
		if (vec[i] > vec[i+1])
		{
			pairs.push_back(std::make_pair(vec[i], vec[i+1]));
		}
		else
		{
			pairs.push_back(std::make_pair(vec[i+1], vec[i]));
		}
	}

	// 2. 메인 체인(S)과 펜드 체인(pend) 생성
	std::vector<int> main_chain;
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		main_chain.push_back(pairs[i].first);
	}

	// 3. 메인 체인을 재귀적으로 정렬
	fordJohnsonSort(main_chain);

	// 4. 정렬된 메인 체인에 맞춰 펜드 체인 재구성
	std::vector<int> pend_chain;
	std::vector<bool> pair_used(pairs.size(), false);
	for (size_t i = 0; i < main_chain.size(); ++i)
	{
		int main_val = main_chain[i];
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (!pair_used[j] && pairs[j].first == main_val)
			{
				pend_chain.push_back(pairs[j].second);
				pair_used[j] = true;
				break ;
			}
		}
	}

	// 5. 펜드 체인을 메인 체인에 삽입
	// 첫 번째 펜드 원소는 항상 메인 체인의 첫 번째 원소보다 작거나 같으므로 맨 앞에 삽입
	int inserted_count = 0;
	if (!pend_chain.empty())
	{
		main_chain.insert(main_chain.begin(), pend_chain[0]);
		inserted_count = 1;
	}

	// Jacobsthal 수열을 이용한 최적 삽입
	std::vector<int> jacob_indices;
	generateJacobsthal(jacob_indices, pend_chain.size());

	size_t last_jacob_k = 1;
	for (size_t i = 2; i < jacob_indices.size(); ++i)
	{
		size_t k = jacob_indices[i];
		// Jacobsthal 인덱스부터 이전 Jacobsthal 인덱스까지 역순으로 삽입
		for (size_t j = k; j > last_jacob_k; --j)
		{
			if (j - 1 < pend_chain.size())
			{
				int value_to_insert = pend_chain[j - 1];
				// 삽입할 위치를 이진 탐색(lower_bound)으로 찾음
				// 탐색 범위: 현재까지 정렬된 메인 체인 부분 + 현재 삽입할 그룹의 원소들
				size_t search_range = (j - 1) + inserted_count;
				std::vector<int>::iterator end_it = main_chain.begin() + std::min(search_range, main_chain.size());
				std::vector<int>::iterator pos = std::lower_bound(main_chain.begin(), end_it, value_to_insert);
				main_chain.insert(pos, value_to_insert);
				inserted_count++;
			}
		}
		last_jacob_k = k;
	}

	// 남은 펜드 원소들을 순차적으로 삽입 (백업)
	for (size_t i = last_jacob_k; i < pend_chain.size(); ++i)
	{
		int value_to_insert = pend_chain[i];
		size_t search_range = i + inserted_count;
		std::vector<int>::iterator end_it = main_chain.begin() + std::min(search_range, main_chain.size());
		std::vector<int>::iterator pos = std::lower_bound(main_chain.begin(), end_it, value_to_insert);
		main_chain.insert(pos, value_to_insert);
		inserted_count++;
	}

	// 6. Straggler 삽입
	if (straggler != -1)
	{
		std::vector<int>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), straggler);
		main_chain.insert(pos, straggler);
	}

	// 원본 벡터를 정렬된 메인 체인으로 교체
	vec = main_chain;
}

// --- Deque specific Ford-Johnson implementation ---

/**
 * @brief std::deque에 대해 Ford-Johnson (Merge-Insert Sort) 알고리즘을 수행합니다.
 * @param deq 정렬할 덱.
 */
void PmergeMe::fordJohnsonSort(std::deque<int>& deq) {
	if (deq.size() <= 1)
	{
		return ;
	}

	int straggler = -1;
	if (deq.size() % 2 != 0)
	{
		straggler = deq.back();
		deq.pop_back();
	}

	std::deque<std::pair<int, int> > pairs;
	for (size_t i = 0; i < deq.size(); i += 2)
	{
		if (deq[i] > deq[i+1])
		{
			pairs.push_back(std::make_pair(deq[i], deq[i+1]));
		}
		else
		{
			pairs.push_back(std::make_pair(deq[i+1], deq[i]));
		}
	}

	std::deque<int> main_chain;
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		main_chain.push_back(pairs[i].first);
	}

	fordJohnsonSort(main_chain);

	std::deque<int> pend_chain;
	std::vector<bool> pair_used(pairs.size(), false);
	for (size_t i = 0; i < main_chain.size(); ++i)
	{
		int main_val = main_chain[i];
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (!pair_used[j] && pairs[j].first == main_val)
			{
				pend_chain.push_back(pairs[j].second);
				pair_used[j] = true;
				break ;
			}
		}
	}

	int inserted_count = 0;
	if (!pend_chain.empty())
	{
		main_chain.insert(main_chain.begin(), pend_chain[0]);
		inserted_count = 1;
	}

	std::deque<int> jacob_indices;
	generateJacobsthal(jacob_indices, pend_chain.size());

	size_t last_jacob_k = 1;
	for (size_t i = 2; i < jacob_indices.size(); ++i)
	{
		size_t k = jacob_indices[i];
		for (size_t j = k; j > last_jacob_k; --j)
		{
			if (j - 1 < pend_chain.size())
			{
				int value_to_insert = pend_chain[j - 1];
				size_t search_range = (j - 1) + inserted_count;
				std::deque<int>::iterator end_it = main_chain.begin() + std::min(search_range, main_chain.size());
				std::deque<int>::iterator pos = std::lower_bound(main_chain.begin(), end_it, value_to_insert);
				main_chain.insert(pos, value_to_insert);
				inserted_count++;
			}
		}
		last_jacob_k = k;
	}

	for (size_t i = last_jacob_k; i < pend_chain.size(); ++i)
	{
		int value_to_insert = pend_chain[i];
		size_t search_range = i + inserted_count;
		std::deque<int>::iterator end_it = main_chain.begin() + std::min(search_range, main_chain.size());
		std::deque<int>::iterator pos = std::lower_bound(main_chain.begin(), end_it, value_to_insert);
		main_chain.insert(pos, value_to_insert);
		inserted_count++;
	}

	if (straggler != -1)
	{
		std::deque<int>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), straggler);
		main_chain.insert(pos, straggler);
	}

	deq = main_chain;
}
