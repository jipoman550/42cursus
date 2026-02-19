# 📋 cub3D 작업 변경 로그 (CHANGELOG)

> 이 문서는 AI가 수행한 코드 변경 사항을 단계별로 기록합니다.

---

## [2026-02-20] Step 1: 파싱 기초 구현

### 📌 변경된 파일 목록

| 파일 | 변경 유형 | 설명 |
|------|-----------|------|
| `cub3d.h` | 수정 | `libft2.h` 인클루드 추가, `parse_map()` 프로토타입 추가 |
| `srcs/parsing.c` | 수정 | 임시 `t_list` 제거, libft 함수 기반 파싱 구현 |
| `srcs/parsing_utils.c` | 수정 | 임시 함수 제거, `ft_split`/`ft_atoi` 기반 `parse_color()` 구현 |
| `Makefile` | 수정 | 소스 파일 경로 수정, `make -C libft bonus` 적용 |

### 🔧 상세 변경 내용

#### 1. `cub3d.h`
- **Before**: `libft.h` 인클루드가 주석 처리되어 있었음.
- **After**: `# include "libft2.h"` 추가 → `libft.h` + `get_next_line.h` + `ft_printf.h` 통합 헤더.
- `parse_map()` 함수 프로토타입 추가. (`#endif` 직전)

#### 2. `srcs/parsing.c`

##### `parse_map()` — 메인 파싱 함수
- `get_next_line(fd)`으로 파일을 한 줄씩 읽음.
- 각 라인을 `parse_line()`에 전달하여 설정(NO/SO/WE/EA/F/C) 또는 맵 데이터로 분류.
- 설정 6개가 모두 수집되지 않으면 에러 반환.
- `convert_map_list_to_array()`로 연결 리스트 → 2D 배열 변환.
- `validate_map_and_player()`로 맵 유효성 검사.
- 모든 경로에서 `ft_lstclear()`로 메모리 해제 보장.

##### `parse_line()` — 라인별 파서
- `ft_strtrim(line, "\n")`으로 개행 제거.
- 빈 줄은 무시 (return 0).
- `config_count < 6`이면 설정 라인으로 처리:
  - `ft_split(trimmed_line, ' ')`으로 토큰화.
  - `ft_strncmp`로 식별자(NO/SO/WE/EA/F/C) 매칭.
  - `ft_strdup`으로 경로 복사.
- `config_count == 6`이면 모든 라인을 맵 데이터로 간주.
- 맵 라인은 **원본 라인에서 `\n`만 제거**하여 공백 보존.

##### `convert_map_list_to_array()` — 리스트 → 배열
- `ft_lstsize()`로 높이 계산.
- 모든 라인을 순회하여 최대 너비(`width`) 결정.
- 각 행을 `width` 크기로 `malloc`, 짧은 행은 공백(' ')으로 패딩.

##### `validate_map_and_player()` — 맵 유효성 검사
- 유효 문자: `' '`, `'0'`, `'1'`, `'N'`, `'S'`, `'W'`, `'E'`
- 플레이어 정확히 1명 존재 확인.
- `'0'` 또는 플레이어 위치가 맵 가장자리이거나 공백(`' '`)에 인접하면 에러 (벽 미둘러싸임).

##### `init_player_direction()` — 방향 벡터 초기화
- N: dir(0,-1), plane(0.66,0)
- S: dir(0,1), plane(-0.66,0)
- W: dir(-1,0), plane(0,-0.66)
- E: dir(1,0), plane(0,0.66)

#### 3. `srcs/parsing_utils.c`

##### `parse_color()` 리팩토링
- **Before**: `simple_split()`, `simple_atoi()`, `is_digit_str()` 등 임시 함수 사용.
- **After**: `ft_split(rgb_str, ',')`, `ft_atoi()`, `ft_isdigit()` 사용.
- 정확히 3개의 토큰 존재 여부 검사.
- RGB 값 범위 검사 (0~255).
- 결과를 `(R << 16) | (G << 8) | B` 형태로 저장.
- `free_split()` 헬퍼로 토큰 배열 해제.

#### 4. `Makefile`
- `SRCS`에 `srcs/parsing.c`, `srcs/parsing_utils.c` 추가.
- `MANDATORY_DIR`, `BONUS_DIR` 등 불필요한 변수 제거.
- libft 빌드 시 `make -C $(LIBFT_DIR) bonus` → 연결 리스트 함수 포함.

---

## [2026-02-20] Step 2: 테스트 인프라 구축

### 📌 변경된 파일 목록

| 파일 | 변경 유형 | 설명 |
|------|-----------|------|
| `tests/test_parsing.c` | 신규 | 파싱 자동 테스트 프로그램 |
| `tests/maps/valid_*.cub` | 신규 | 유효한 맵 테스트 케이스들 |
| `tests/maps/invalid_*.cub` | 신규 | 유효하지 않은 맵 테스트 케이스들 |
| `Makefile` | 수정 | `test` 타겟 추가 |

### 🔧 상세 변경 내용
- `make test`로 파싱 테스트 자동 실행 가능.
- 유효한 맵: 정상 파싱 및 데이터 검증.
- 유효하지 않은 맵: `parse_map()`이 `-1`을 반환하는지 확인.
- 각 테스트의 PASS/FAIL 결과를 색상으로 출력.
