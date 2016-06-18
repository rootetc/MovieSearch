# MovieSearch
##사용 프로그램
MFC, FFMPEG, OPENCV

##Download the source code 
git clone git:://github.com/rootetc/MovieSearch

##Algorithm
![graph1](https://cloud.githubusercontent.com/assets/19329620/16171453/44722778-35aa-11e6-9410-db85fe9daf1f.png)
ffmpeg를 사용하여 사용자가 설정한 시간 간격과 크기를 가지도록 이미지 분할
ffmpeg -ss 00:00:15 -i video.mp4 -vf scale=800:-1 -vframes 1 image.jpg
0.15초 간격으로 이미지 분할 및 이미지에게 고유 id값 할당.
각각의 이미지를 10 by 10의 영역으로 분할 후 pixel들의 평균값을 추출.
평균 pixel들을 사용하여 key값 부여, chaind hash table을 사용하여 hash table 생성

### Make DB
![graph2](https://cloud.githubusercontent.com/assets/19329620/16171459/5626c53c-35aa-11e6-8393-5361b9c1b121.png)
이미지의 출력을 위하여 1열에는 해당되는 주소의 값을 cstring형태로 값을 저장.
ffmpeg를 분할 후 분할 된 이미지는 순차적으로 최대 5섯 자리 수를 가지도록 00000부터 99999까지 나타나도록 설정하였기 때문에 해당 되는 파일의 번호를 사용하면 영상에서 나타나는 시간을 알 수 있기 때문에 2열에 이미지가 해당되는 번호를 저장.
3열부터 102열 까지는 이미지들이 가지는 고유 100개의 pixel 평균값을 cstring 형태로 저장.

### Make chained hash table
![graph3](https://cloud.githubusercontent.com/assets/19329620/16171462/633390f2-35aa-11e6-8f83-0c042630311a.png)
Chained hash table은 중복 발생시 chain처럼 관계를 엮어 주는 알고리즘이다.

Chained hash table을 활용하기 위하여 linked list를 활용하여 중복 발생시 256 by 100의 배열에 깊이로 나타날 수 있도록 설계 

256 by 100의 배열도 linked list의 구조를 가진 배열로 설계. 

256은 평균 pixel들이 나타낼 수 있는 범위를 포함 하기 위하여 행의 길이를 256으로 설정 및 100열은 이미지들이 가지는 평균 pixel값 100개를 가지기 때문에 열의 길이를 100으로 설정
행과 열이 설정되면 Hash_table에는 N by 103에 저장된 이미지의 번호가 저장되도록 설정

### Search
비교이미지의 평균 픽셀값들을 사용하여 hash table의 row, col index에 접근
해당 id를 사용하여 이미지 count buffer에 접근 후 count 증가
