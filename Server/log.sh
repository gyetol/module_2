#!/bin/sh

echo "$(date +%Y)/$(date +%m)/$(date +%d)  $(date +%H):$(date +%M):$(date +%S)  fileDanzi start" >> ./log/$(date +%Y)_$(date +%m)_$(date +%d).txt 


#리눅스 표준시 미국으로 되어있어서 현재 한국 날짜와 다른 날짜의 로그파일 생성, 접근하는 경우가 있습니다
#sudo mv /etc/localtime /etc/localtime_org
#sudo ln -s /usr/share/zoneinfo/Asia/Seoul /etc/localtime
#위의 2개 명령 실행한 후  (기존 시간을 _org파일로 세이브한 후 타임존을 한국으로 바꾸는 기능)
#셸에서 date 명령을 입력해 표준시가 KST로 뜨는지 확인한 후에 fileDanzi를 실행해야합니다

