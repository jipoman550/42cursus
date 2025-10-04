# so_long

## 📌 프로젝트 목적

> **MiniLibX** 라이브러리를 활용하여 간단한 2D 게임을 구현하는 C 프로그램. 창 관리, 키보드 이벤트, 그래픽 요소(텍스처, 스프라이트)를 다루는 기술을 습득하고, C 언어 실력과 문제 해결 능력을 향상시키는 것이 목표.

-----

## 🧠 과제 개요

  - **프로그램 이름**: `so_long`
  - **제출 파일**: `Makefile`, `*.h`, `*.c`, `maps/`, `textures/`
  - **실행 인자**: `.ber`
  - **허용 외부 함수**: `open`, `close`, `read`, `write`, `malloc`, `free`, `perror`, `strerror`, `exit`, 수학 라이브러리(`-lm`), MiniLibX의 모든 함수, `ft_printf` 또는 직접 구현한 동등 함수
  - **Libft 사용**: 가능

**게임 시나리오**:
플레이어는 W, A, S, D 키로 이동하며 맵에 있는 모든 **수집품(C)**을 모은 후, **출구(E)**로 탈출해야 합니다.

-----

## 🚀 구현 계획 및 진행 상황

### 1단계: 맵 파싱 및 유효성 검사

  - [x] `.ber` 파일 확장자 확인
  - [x] 맵이 직사각형인지 확인
  - [x] 맵이 벽('1')으로 둘러싸여 있는지 확인
  - [x] 맵에 '0', '1', 'C', 'E', 'P' 외의 문자가 포함되어 있지 않은지 확인
  - [x] 맵에 1개의 'E', 1개의 'P', 1개 이상의 'C'가 있는지 확인
  - [x] 플레이어 위치에서 모든 수집품과 출구로 가는 유효한 경로가 있는지 확인
  - [x] 유효성 검사 실패 시 "Error\n"와 함께 명시적인 에러 메시지 출력 후 종료

### 2단계: 그래픽 및 이벤트 관리

  - [x] MiniLibX를 사용하여 창을 생성하고 이미지를 표시
  - [x] 맵의 각 문자에 해당하는 스프라이트(벽, 빈 공간, 수집품, 출구, 플레이어) 로드 및 출력
  - [x] W, A, S, D 키보드 이벤트 처리
  - [x] ESC 키를 누르거나 창 닫기 버튼을 클릭했을 때 프로그램 정상 종료
  - [x] 창 전환 및 최소화 시 정상 동작 유지

### 3단계: 게임 로직 구현

  - [x] 플레이어 이동 로직 구현 (벽 통과 불가)
  - [x] 이동할 때마다 이동 횟수를 셸(터미널)에 출력
  - [x] 플레이어가 수집품(C)에 닿으면 해당 수집품 제거
  - [x] 모든 수집품을 모은 후 출구(E)로 탈출 가능하도록 로직 구현

### 4단계: 보너스 기능 구현 (선택 사항)

  - [ ] 적(Enemy) 추가 및 충돌 시 게임 종료
  - [ ] 스프라이트 애니메이션 추가
  - [ ] 이동 횟수를 터미널 대신 화면에 표시

-----

## 🛠️ 디버깅 및 문제 해결 히스토리

이 섹션은 개발 과정에서 발생한 주요 버그와 그 해결 과정을 기록합니다.

  - **[날짜] - [문제 요약]**
      - **증상**: (발생 시 기록)
      - **원인 분석**: (발생 시 기록)
      - **해결 방안**: (발생 시 기록)
      - **배운 점**: (발생 시 기록)

  - **[2025-10-02] - [game logic error]**
      - **증상**: WASD 이동 시 플레이어(P)의 위치가 갱신되지 않고, 이미지만 변경되는 문제 발생. 특히 W, A 키는 이미지도 변경되지 않음.
      - **원인 분석**: `t_game` 구조체에 플레이어의 현재 위치(`player_x`, `player_y`)를 기록하는 변수가 없어, 키 입력 후 **실제 위치 갱신 로직이 누락**됨.
      - **해결 방안**: `t_game` 구조체에 플레이어 위치 변수 추가 후, 키 입력 핸들러에서 이 변수들을 기반으로 위치를 갱신하도록 수정.
      - **변경 사항 확인**:
        * **오류 상태 커밋 ID**: `c2e2fc3`
        * **수정 완료 커밋 ID**: `989896d`
        * **변경 내용 확인 명령어**: `git diff c2e2fc3 989896d`
      - **배운 점**: 게임 상태를 관리하는 방식에 구조체를 추가했을 때, 기존코드에서 구조체를 활용하는 방안을 생각해야 된다.

-----

## 📂 디렉토리 구조

<details>
<summary>전체 디렉토리 구조 펼쳐보기 (클릭)</summary>

```

so_long/
.
├── Makefile
├── README.md
├── en.subject_so_long.pdf
├── include
│   └── so_long.h
├── libft
│   ├── Makefile
│   ├── ft_atoi.c
│   ├── ft_bzero.c
│   ├── ft_calloc.c
│   ├── ft_isalnum.c
│   ├── ft_isalpha.c
│   ├── ft_isascii.c
│   ├── ft_isdigit.c
│   ├── ft_isprint.c
│   ├── ft_itoa.c
│   ├── ft_lstadd_back_bonus.c
│   ├── ft_lstadd_front_bonus.c
│   ├── ft_lstclear_bonus.c
│   ├── ft_lstdelone_bonus.c
│   ├── ft_lstiter_bonus.c
│   ├── ft_lstlast_bonus.c
│   ├── ft_lstmap_bonus.c
│   ├── ft_lstnew_bonus.c
│   ├── ft_lstsize_bonus.c
│   ├── ft_memchr.c
│   ├── ft_memcmp.c
│   ├── ft_memcpy.c
│   ├── ft_memmove.c
│   ├── ft_memset.c
│   ├── ft_putchar_fd.c
│   ├── ft_putendl_fd.c
│   ├── ft_putnbr_fd.c
│   ├── ft_putstr_fd.c
│   ├── ft_split.c
│   ├── ft_strchr.c
│   ├── ft_strdup.c
│   ├── ft_striteri.c
│   ├── ft_strjoin.c
│   ├── ft_strlcat.c
│   ├── ft_strlcpy.c
│   ├── ft_strlen.c
│   ├── ft_strmapi.c
│   ├── ft_strncmp.c
│   ├── ft_strnstr.c
│   ├── ft_strrchr.c
│   ├── ft_strtrim.c
│   ├── ft_substr.c
│   ├── ft_tolower.c
│   ├── ft_toupper.c
│   ├── ftp
│   │   ├── Makefile
│   │   ├── ft_conversions.c
│   │   ├── ft_convert_char.c
│   │   ├── ft_convert_decimal.c
│   │   ├── ft_convert_hex.c
│   │   ├── ft_convert_percent.c
│   │   ├── ft_convert_pointer.c
│   │   ├── ft_convert_string.c
│   │   ├── ft_convert_unsigned.c
│   │   ├── ft_printf.c
│   │   ├── ft_printf.h
│   │   ├── ft_utils.c
│   │   └── libft
│   │       ├── ftp_putchar_fd.c
│   │       ├── ftp_putnbr_fd.c
│   │       ├── ftp_putstr_fd.c
│   │       ├── ftp_strlen.c
│   │       └── libft.h
│   ├── gnl
│   │   ├── get_next_line.c
│   │   ├── get_next_line.h
│   │   └── get_next_line_utils.c
│   ├── include
│   │   ├── ft_printf.h
│   │   ├── get_next_line.h
│   │   └── libft.h
│   └── libft2.h
├── memo.txt
├── minilibx-linux
│   ├── LICENSE
│   ├── Makefile
│   ├── Makefile.gen
│   ├── Makefile.mk
│   ├── README.md
│   ├── configure
│   ├── man
│   │   ├── man1
│   │   │   ├── mlx.1
│   │   │   ├── mlx_loop.1
│   │   │   ├── mlx_new_image.1
│   │   │   ├── mlx_new_window.1
│   │   │   └── mlx_pixel_put.1
│   │   └── man3
│   │       ├── mlx.3
│   │       ├── mlx_loop.3
│   │       ├── mlx_new_image.3
│   │       ├── mlx_new_window.3
│   │       └── mlx_pixel_put.3
│   ├── mlx.h
│   ├── mlx_clear_window.c
│   ├── mlx_destroy_display.c
│   ├── mlx_destroy_image.c
│   ├── mlx_destroy_window.c
│   ├── mlx_expose_hook.c
│   ├── mlx_ext_randr.c
│   ├── mlx_flush_event.c
│   ├── mlx_get_color_value.c
│   ├── mlx_get_data_addr.c
│   ├── mlx_hook.c
│   ├── mlx_init.c
│   ├── mlx_int.h
│   ├── mlx_int_anti_resize_win.c
│   ├── mlx_int_do_nothing.c
│   ├── mlx_int_get_visual.c
│   ├── mlx_int_param_event.c
│   ├── mlx_int_set_win_event_mask.c
│   ├── mlx_int_str_to_wordtab.c
│   ├── mlx_int_wait_first_expose.c
│   ├── mlx_key_hook.c
│   ├── mlx_lib_xpm.c
│   ├── mlx_loop.c
│   ├── mlx_loop_hook.c
│   ├── mlx_mouse.c
│   ├── mlx_mouse_hook.c
│   ├── mlx_new_image.c
│   ├── mlx_new_window.c
│   ├── mlx_pixel_put.c
│   ├── mlx_put_image_to_window.c
│   ├── mlx_rgb.c
│   ├── mlx_screen_size.c
│   ├── mlx_set_font.c
│   ├── mlx_string_put.c
│   ├── mlx_xpm.c
│   ├── mlx_xpm.c.ok
│   ├── rgb2c.pl
│   └── test
│       ├── Makefile.gen
│       ├── Makefile.mk
│       ├── main.c
│       ├── new_win.c
│       ├── open.xpm
│       ├── open24.xpm
│       ├── open30.xpm
│       └── run_tests.sh
├── src
│   ├── event_handler.c
│   ├── game_logic.c
│   ├── main.c
│   ├── map_parsing.c
│   ├── map_utils.c
│   ├── map_validation.c
│   ├── path_validation.c
│   ├── path_validation_utils.c
│   ├── rendering.c
│   └── utils.c
├── tests
│   ├── initial_fail
│   │   ├── empty_file.ber
│   │   ├── invalid_ber.txt
│   │   ├── invalid_map_C_cnt_0.ber
│   │   ├── invalid_map_E_cnt_0.ber
│   │   ├── invalid_map_E_cnt_2.ber
│   │   ├── invalid_map_P_cnt_0.ber
│   │   ├── invalid_map_P_cnt_2.ber
│   │   ├── invalid_map_include_other_char.ber
│   │   ├── invalid_map_shape.ber
│   │   ├── invalid_map_small.ber
│   │   ├── invalid_map_small_ver2.ber
│   │   └── invalid_map_surrounding_by_1.ber
│   ├── path_fail
│   │   ├── unreachable_collectible.ber
│   │   └── unreachable_exit.ber
│   └── success_cases
│       ├── edge_cases.ber
│       ├── large_map.ber
│       ├── valid_path.ber
│       └── valid_path_complex.ber
├── textures
│   ├── c.xpm
│   ├── d.xpm
│   ├── enemy.xpm
│   ├── error.xpm
│   ├── es.xpm
│   ├── exit.xpm
│   ├── l.xpm
│   ├── r.xpm
│   ├── u.xpm
│   └── w.xpm
└── valgrind_log.txt

```

</details>

-----

## 빌드방법, 컴파일 명령어, 테스트 명령어

#### **1. 프로젝트 빌드**

프로젝트 루트 디렉터리에서 `make` 명령어를 사용하여 `so_long` 실행 파일을 빌드합니다.

```bash
make
```

#### **2. 프로그램 실행**

유효한 `.ber` 맵 파일을 인자로 전달하여 프로그램을 실행합니다.

```bash
./so_long maps/map1.ber
```

#### **3. 보너스 빌드**

보너스 기능을 구현했다면 `make bonus` 명령어로 보너스 버전을 빌드할 수 있습니다.

```bash
make bonus
./so_long_bonus maps/map1.ber
```

#### **4. 메모리 누수 검사**

`valgrind`를 사용하여 프로그램 실행 중 메모리 누수가 없는지 확인합니다.

```bash
valgrind --leak-check=full ./so_long maps/map1.ber
```

#### **5. Norm 규정 확인**

`norminette`를 사용하여 모든 `.c` 및 `.h` 파일이 42 Norm을 준수하는지 확인합니다.

```bash
norminette src includes
```

#### **6. 통합 테스트 (Exit Code 및 메모리 누수 검사)**

제공된 테스트 맵 파일들을 기반으로 **Exit Code(종료 코드)**의 정상 여부와 Valgrind를 이용한 메모리 누수 검사를 한 번에 실행합니다.`norminette`를 사용하여 모든 `.c` 및 `.h` 파일이 42 Norm을 준수하는지 확인합니다.

```bash
make test
```

**테스트 결과 확인**

Valgrind 검사 결과는 실행 완료 후 valgrind_log.txt 파일에 전체 내용이 기록됩니다. 메모리 누수 발생 시 해당 파일을 열어 상세 내용을 확인하십시오.

```bash
cat valgrinde_log.txt
```

-----

## ✅ 최종 제출 점검표

  - [ ] **프로그램 동작**:

      - [ ] 유효하지 않은 맵 파일에 대해 "Error\\n"와 함께 오류 메시지 출력 후 종료
      - [ ] ESC 키 또는 창 닫기 버튼으로 정상 종료
      - [ ] 모든 수집품을 모은 후 탈출 가능
      - [ ] 매 이동마다 터미널에 이동 횟수 출력

  - [ ] **코드 품질 및 규정**:

      - [ ] 모든 `.c`, `.h` 파일이 Norm 규정을 완벽히 준수하는지(`norminette` 통과)
      - [ ] `valgrind` 검사를 통해 메모리 누수가 전혀 없는지 확인
      - [ ] [cite\_start]Segfault, Bus error 등 예기치 않은 프로그램 종료 없음
      - [ ] 허용되지 않은 외부 함수 사용 여부 재확인

  - [ ] **Makefile**:

      - [ ] `$(NAME)`, `all`, `clean`, `fclean`, `re` 규칙 모두 정상 작동
      - [ ] 불필요한 재링크 발생 안 함
      - [ ] (보너스 구현 시) `bonus` 규칙 정상 작동

-----

## 📝 메모

  - [ ] 텍스처 및 스프라이트는 무료 리소스를 사용하거나 직접 제작
  - [ ] 보너스는 필수 과제가 완벽하게 구현된 경우에만 평가됨

-----
