#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <SoftwareSerial.h>

// 2023.11.04 @mint3100 제작
// 2023.11.05 수정

// paper, normal, pet, pp 만 감지함 (기존 계획에서 삭제된건 제거요망)

int Tx = 2; //전송 보내는핀  
int Rx = 1; //수신 받는핀

SoftwareSerial BtSerial(Tx, Rx);

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo; // paper
Servo servo2; // normal
Servo servo3; // pet
Servo servo4; // pp

void setup() {
  // 초기 시작 서보모터 디지털 단자 셋팅
  servo.attach(4);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(7);
  clsall();
  // 초기 시작 LCD
  lcd.init();
  lcd.backlight();
  lcd.print("Ready");
  lcd.setCursor(0, 1);
  lcd.print("Waiting waste...");
  Serial.begin(9600);
  BtSerial.begin(9600); // BtSerial 초기화
  Serial.println("Setup OK");
}

void loop() {
  // 블루투스 시리얼, 시리얼 입력 확인
  if (Serial.available() > 0) {
    String input = Serial.readString();
    processInput(input);
  }
  if (BtSerial.available() > 0) {
    String input = BtSerial.readString();
    processInput(input);
  }
}

void processInput(String input) {
  input.trim();
  // 물건 감지 Serial 입력으로 String input
  // 그 값은 물건 값
  if (input == "paper") {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Paper");
    Serial.println("OK");
    servo2.write(180);
    delay(2000);
    servo2.write(0);
    setup();
  } else if (input == "normal") {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("normal");
    Serial.println("OK");
    servo3.write(180);
    delay(2000);
    servo3.write(0);
    setup(); // 초기화
  } else if (input == "pet") {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("pet");
    Serial.println("OK");
    servo.write(180);
    delay(2000);
    servo.write(0);
    setup();
  } else if (input == "pp") {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("pp");
    Serial.println("OK");
    servo4.write(180);
    delay(2000);
    servo4.write(0);
    setup(); //초기화
  } else if (input == "openall") {
    messageR("openall");
    servo.write(180);
    servo2.write(180);
    servo3.write(180);
    servo4.write(180);
  } else if (input == "closeall") {
    messageR("closeall");
    clsall();
    setup();
  } else if (input == "debug0") {
    messageR("0");
    servo.write(0);
  } else if (input == "debug180") {
    messageR("180");
    servo.write(180);
  } else if (input == "debug") {
    // 디버그 모드 (서보모터 동작 체크)
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Debug Mode");
    messageR("Servo_0");
    servo.write(90);
    messageR("Servo_2");
    servo2.write(90);
    messageR("Servo_3");
    servo3.write(90);
    messageR("Servo_4");
    servo4.write(90);
    messageR("END");
    setup();
  } else {
    // 에러 처리
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Invalid Input.");
    lcd.setCursor(0, 1);
    lcd.print("Resetting....");
    Serial.println("ERROR: Invalid Input");
  }
}

// 메시지 표시하고 LCD 클리어하고 message Sting 표시
void messageR(String message) {
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
}

void clsall() {
    servo.write(0);
    servo2.write(0);
    servo3.write(0);
    servo4.write(0);
}
