/*
 * 2024년도 CanSat Capstone Bus Tracker 개발 코드 입니다.
 * 객체 지향으로 설계
 * 사용 센서: MPU 6050, Ultimate Gps Breakout V3, ESP
*/
/*
  참고 링크 모음
  GPS 프로토콜 정보 : https://wsstudynote.tistory.com/11
*/

//--선언문-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// 라이브러리 선언 부분
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>   // Software Serial 라이브러리

// 상,변수, 객체 선언, 함수 부분
//--상수 선언-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define GPSSerial Serial1

Adafruit_GPS GPS(&GPSSerial);
HardwareSerial mySerial = Serial1;
#define GPSECHO false

// GPS 프로토콜 정보
#define GPS_FIX_DATA "$GPGGA" // 시간, 위도, 경도, 해수면 기준 고도, 지구의 고도차이
#define GPS_RECOMMENDED_MINIMUM_DATA "$GPRMC" // 시간, 신호의 신뢰성, 위도, 경도, 속도계
#define GPS_SATELLITES_IN_VIEW "$GPGSV" // 위성 개수

//--변수 선언-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 설정값
long gps_Latitude = 0; //위도
long gps_Latitude_decimal = 0; //위도 소수
long gps_Longitude = 0; //경도
long gps_Longitude_decimal = 0; //경도 소수

//--void 함수 선언---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 초기화 함수
void GPS_Init();
void MPU_Init();

// 센서 값 가져오는 함수
void GPS_Loop();
void MPU_Loop();

void setup() {
  Serial.begin(9600);
  GPS_Init();
  MPU_Initi();
}

void loop() {
  GPS_Loop();
  MPU_Loop();
}

void GPS_Init(){
  Serial.println("Adafruit GPS library basic parsing test!");

  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
}

void GPS_Loop(){
  char c = GPS.read();

   if (GPSECHO)
    if (c) Serial.print(c);
  if (GPS.newNMEAreceived()) {
    Serial.print(GPS.lastNMEA());
    if (!GPS.parse(GPS.lastNMEA()))
      return;
    gps_latitude = (int)(GPS.latitude / 100) + fmod(GPS.latitude, 100) / 60.0;
    gps_longitude = (int)(GPS.longitude / 100) + fmod(GPS.longitude, 100) / 60.0;
    Serial.print("위도: ");
    Serial.println(gps_latitude);
    Serial.print("경도: ");
    Serial.println(gps_longitude);
    delay(1000);
  }
}

void MPU_Init(){
  //dd
}

void MPU_Loop(){
  //dd
}
