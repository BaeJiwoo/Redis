# 🚀 Redis Study Repository

이 저장소는 게임 백엔드 개발에 필수적인 **Redis**를 C++ 환경에서 다루는 법을 익히기 위한 통합 학습 공간입니다. 기초적인 연동부터 시작하여, 실제 게임 서버에서 사용되는 다양한 시나리오(랭킹, 세션, 메시징 등)를 단계별로 구현합니다.

---

## 📂 프로젝트 목록 (Project Overview)

프로젝트가 추가될 때마다 아래 표를 갱신하여 관리합니다.

| 프로젝트명 | 주요 기능 및 학습 목적 | 기술 스택 | 상태 |
| :--- | :--- | :--- | :--- |
| **[RedisTest](./RedisTest)** | **기초 연동**: hiredis 설정 및 기본 명령어(SET/GET) 실습 | C++17, hiredis | 완료 |


---

## 🛠 개발 환경 (Environment)
- **Language**: C++ 17 이상
- **IDE**: Visual Studio 2022
- **Client Library**: [hiredis](https://github.com/redis/hiredis)
- **Database**: Redis (Docker 또는 WSL2 환경 권장)

---

## 🚀 시작하기 (Quick Start)

### 1. Redis 서버 실행
로컬 환경에서 Redis 서버가 구동 중이어야 합니다.

- **Docker 사용 시**:
  ```bash
  docker run --name my-redis -p 6379:6379 -d redis
  ```
- **Windows (WSL2) 사용 시**:
  ```bash
  sudo apt update && sudo apt install redis-server
  redis-server
  ```

### 2. 의존성 설치 (vcpkg 권장)
라이브러리 파일을 직접 관리하는 대신 `vcpkg` 사용을 강력히 권장합니다.
```bash
vcpkg install hiredis:x64-windows
```
*Visual Studio 프로젝트 속성에서 `Use vcpkg`를 **Yes**로 설정하세요.*

### 3. 빌드 및 실행
1. `RedisStudy.sln` 파일을 엽니다.
2. 솔루션 구성을 `Debug` / `x64`로 설정합니다.
3. `F5`를 눌러 실행합니다.

---

## 📝 학습 및 구현 핵심 노트

### 1. hiredis 인터페이스
- `redisConnect`: 서버 연결 및 컨텍스트 생성
- `redisCommand`: 가변 인자 형식을 통한 Redis 명령어 전달
- `freeReplyObject`: 응답 객체의 명시적 메모리 해제

### 2. 메모리 및 자원 관리 (RAII)
- C 기반의 hiredis를 C++에서 안전하게 사용하기 위해 **RAII 패턴**을 적용한 래퍼 클래스를 구현합니다.
- 스마트 포인터나 커스텀 소멸자를 통해 `redisReply`와 `redisContext`가 자동으로 해제되도록 설계합니다.

---

## ⚠️ 주의사항 (Git Management)
- **바이너리 제외**: `.lib`, `.dll`, `.exe` 및 빌드 중간 산출물은 `.gitignore`에 등록하여 push하지 않습니다.
- **라이브러리 경로**: `vcpkg`를 사용하지 않고 `Libs/` 폴더를 직접 사용할 경우, 팀원 간의 환경 동기화를 위해 상대 경로 설정을 반드시 확인해야 합니다.
