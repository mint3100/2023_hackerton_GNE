# 2023_hackerton_GNE
2023년 11월 4일 ~ 5일까지 진행된 경상남도교육청 해커톤 대회에서 사용한 코드입니다.\
Tensorflow와 Arduino를 사용하여 물체 재질을 감지하고 그에 해당하는 칸을 자동으로 열어주는 코드입니다.
## 코드 설명
### 사용 라이브러리
* Pyserial, Tensorlfow, Keras 라이브러리를 사용합니다.
### 로직
1. web_Py/integrate_camera.py 파일이 물체를 감지합니다. (모델은 keras_model.h5를 사용합니다.)
2. web_Py/integrate_camera.py에서 Serial 통신으로 main.ino가 설치된 아두이노로 pp, pet, 등등 물체 재질 정보를 보냅니다.
3. 아두이노에서는 적절한 쓰레기통 칸을 개방해줍니다.

### 사용 시 주의점
* web_Py/integrate_camera.py애 Serial 포트가 하드코딩되어있습니다. 수정 후 적절하게 활용바랍니다.
---------------------
본 코드는 GNU AGPL 3.0 라이선스를 따릅니다.
