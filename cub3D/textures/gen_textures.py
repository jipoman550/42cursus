#!/usr/bin/env python3
import os

# 5x5 해상도의 픽셀 아트 폰트
LETTERS = {
    'N': ["10001", "11001", "10101", "10011", "10001"],
    'S': ["11111", "10000", "11111", "00001", "11111"],
    'W': ["10001", "10001", "10101", "11011", "10001"],
    'E': ["11111", "10000", "11111", "10000", "11111"]
}

# 방향별 색상: (글자색, 배경색)
COLORS = {
    'N': ('#FF5555', '#330000'), # Red
    'S': ('#5555FF', '#000033'), # Blue
    'W': ('#55FF55', '#003300'), # Green
    'E': ('#FFFF55', '#333300')  # Yellow
}

def generate_xpm(direction, filename):
    fg, bg = COLORS[direction]
    letter = LETTERS[direction]

    with open(filename, 'w') as f:
        f.write("/* XPM */\n")
        f.write(f"static char *{direction}_test[] = {{\n")
        f.write('"64 64 3 1",\n')
        f.write(f'"  c {bg}",\n')   # 배경
        f.write(f'"X c {fg}",\n')   # 글자
        f.write(f'". c #FFFFFF",\n') # 좌측 상단 마커 (흰색)

        for y in range(64):
            row = ""
            for x in range(64):
                # 1. 절대 비대칭 마커: 좌측 상단(Top-Left) 8x8 픽셀은 무조건 흰색
                if x < 8 and y < 8:
                    row += "."
                # 2. 정중앙에 방향 알파벳 렌더링 (5x5 폰트를 30x30 사이즈로 스케일업)
                elif 16 <= x < 46 and 16 <= y < 46:
                    lx = (x - 16) // 6
                    ly = (y - 16) // 6
                    if letter[ly][lx] == '1':
                        row += "X"
                    else:
                        row += " "
                else:
                    row += " "

            comma = "," if y < 63 else ""
            f.write(f'"{row}"{comma}\n')

        f.write("};\n")

if __name__ == "__main__":
    os.makedirs("textures", exist_ok=True)
    generate_xpm('N', 'textures/NO_test.xpm')
    generate_xpm('S', 'textures/SO_test.xpm')
    generate_xpm('W', 'textures/WE_test.xpm')
    generate_xpm('E', 'textures/EA_test.xpm')
    print("✅ 4개의 비대칭 테스트용 XPM 텍스처가 textures/ 폴더에 생성되었습니다!")