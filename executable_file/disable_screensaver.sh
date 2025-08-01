#!/bin/bash

# 화면 보호기 비활성화
xset s off
xset -dpms
xset q

echo "화면 보호기 및 DPMS(Display Power Management Signaling)가 비활성화되었습니다."
echo "현재 설정:"
xset q | grep "timeout"
xset q | grep "DPMS"
