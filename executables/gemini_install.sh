#!/bin/bash

# 설정 변수 (필요에 따라 수정)
NODE_VERSION="22.17.0" # 설치하려는 Node.js LTS 버전
# ==============================================================================
# TODO: 아래 API_KEY 변수에 자신의 Gemini API 키를 입력하세요.
# https://aistudio.google.com/app/apikey 에서 키를 발급받을 수 있습니다.
API_KEY="AIzaSyDFZga3rmauMKmNE3fpQO28tmm48L6H_IU" # 자신의 API_KEY
# ==============================================================================
NODE_FILENAME="node-v${NODE_VERSION}-linux-x64.tar.xz"
NODE_DOWNLOAD_URL="https://nodejs.org/dist/v${NODE_VERSION}/${NODE_FILENAME}"

GOINFRE_DIR="$HOME/goinfre"
MY_NODEJS_DIR="$GOINFRE_DIR/my_nodejs"
NODE_EXTRACT_DIR_NAME="node-v${NODE_VERSION}-linux-x64" # 압축 해제 후 생성될 디렉토리 이름
NODE_BIN_DIR="$MY_NODEJS_DIR/$NODE_EXTRACT_DIR_NAME/bin"
NPM_CACHE_DIR="$GOINFRE_DIR/.npm_cache"

# API_KEY 확인
if [ -z "$API_KEY" ]; then
    echo "오류: 스크립트 상단의 API_KEY 변수를 설정해야 합니다."
    echo "하는 김에 설치하려는 Node.js 버전도 확인하세요."
    exit 1
fi

echo "=== Gemini CLI 환경 설정 자동화 스크립트 시작 ==="

# 1. Node.js 설치 디렉토리 확인 및 생성
echo "Node.js 설치 디렉토리 확인 및 생성: $MY_NODEJS_DIR"
mkdir -p "$MY_NODEJS_DIR"
cd "$MY_NODEJS_DIR"

if [ ! -d "$NODE_EXTRACT_DIR_NAME" ]; then
    echo "Node.js 바이너리가 없습니다. 다운로드 및 압축 해제 시작..."
    wget -q --show-progress "$NODE_DOWNLOAD_URL"
    if [ $? -ne 0 ]; then
        echo "오류: Node.js 다운로드 실패. URL 또는 네트워크를 확인하세요."
        exit 1
    fi
    tar -xf "$NODE_FILENAME"
    if [ $? -ne 0 ]; then
        echo "오류: Node.js 압축 해제 실패."
        exit 1
    fi
    rm "$NODE_FILENAME" # 압축 파일 삭제
    echo "Node.js 설치 완료."
else
    echo "Node.js 바이너리가 이미 존재합니다. 스킵합니다."
fi

# 2. 스크립트 실행을 위해 PATH 임시 설정
export PATH="$NODE_BIN_DIR:$PATH"

# 3. npm 캐시 경로 설정
echo "npm 캐시 경로 설정: $NPM_CACHE_DIR"
mkdir -p "$NPM_CACHE_DIR"
npm config set cache "$NPM_CACHE_DIR"

# 4. Gemini CLI 설치
echo "Gemini CLI 설치..."
npm install -g @google/gemini-cli

# 5. .zshrc에 환경 변수 추가 여부 확인
read -p ".zshrc 파일에 Gemini CLI 환경 변수를 추가하시겠습니까? (y/n) " -n 1 -r
echo
if [[ $REPLY =~ ^[Yy]$ ]]; then
    echo "기존 .zshrc 파일을 백업합니다: ~/.zshrc.bak"
    cp ~/.zshrc ~/.zshrc.bak 2>/dev/null || true

    echo ".zshrc 파일에 환경 변수 추가 중..."
    # Gemini 설정이 이미 있는지 확인
    if ! grep -q "# Gemini CLI Settings" ~/.zshrc; then
        cat <<EOF >> ~/.zshrc

# Gemini CLI Settings
export PATH="$NODE_BIN_DIR:\$PATH"
export GOOGLE_API_KEY=$API_KEY
export GEMINI_API_KEY=$API_KEY
EOF
        echo ".zshrc 파일에 환경 변수가 추가되었습니다."
    else
        echo ".zshrc 파일에 이미 Gemini CLI 설정이 존재합니다. 건너뜁니다."
    fi
else
    echo "환경 변수 추가를 건너뜁니다."
    echo "수동으로 .zshrc에 다음을 추가해야 합니다:"
    echo "
# Gemini CLI Settings
export PATH=\"$NODE_BIN_DIR:\$PATH\"
export GOOGLE_API_KEY=$API_KEY
export GEMINI_API_KEY=$API_KEY
"
fi

echo "=== Gemini CLI 환경 설정 완료! ==="
echo "이제 새 터미널을 열거나 'source ~/.zshrc'를 실행하여 환경을 적용하고 Gemini CLI를 사용하세요."
