#!/bin/bash

# X 서버가 실행 중인지 확인
if [ -z "$DISPLAY" ]; then
    echo "DISPLAY 환경 변수가 설정되어 있지 않습니다. X 세션 내에서 실행하십시오."
    exit 1
fi

# 스크린 세이버 및 절전 기능 끄기
xset s off            # 스크린 세이버 비활성화
xset s noblank        # 화면 공백 비활성화
xset -dpms            # DPMS(절전모드) 끄기

# GNOME 환경에서 자동 잠금 끄기 (필요 시)
if command -v gsettings &> /dev/null; then
    gsettings set org.gnome.desktop.session idle-delay 0 2>/dev/null
    gsettings set org.gnome.desktop.screensaver lock-enabled false 2>/dev/null
fi

echo "[완료] 화면 보호기 및 자동 잠금 기능 비활성화됨"
xset q | grep "timeout"
xset q | grep "DPMS"

