fileDanzi 파일은 fileDanzi.h / fileDanzi.c / serverStart.h / serverStart.c를 컴파일하여 만든 실행파일이다
이때 start 명령어 받는 쪽은 fileDanzi.c이며 serverStart.c에는 소켓 연결 코드를 추가해야됨
아직 사용할 자료구조를 정하지 않은 상태이기에 테스트ip로 192를 등록해둔 상태이다

<현재 완료된것>
./fileDanzi start 명령어 받아 실행
등록되지 않은 ip일 경우 계정추가
등록된 ip일 경우 비밀번호 확인

<해야하는것>
자료구조 선정 후 자료구조 함수들을 통해서 ip 비번 등의 확인작업을 거쳐야됨
이후 serverStart에 소켓연결
