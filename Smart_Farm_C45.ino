/**
  Stable using library Firebase ESP32 Client V3.12.5
**/

#include <WiFiManager.h>
#include <FirebaseESP32.h>
#include <ArduinoJson.h>
#include "time.h"
#include <HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <EEPROM.h>

#define DHTPIN 4
#define DHTTYPE DHT11

//Timer
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

WiFiManager wm;
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define valve1_pin  16
#define valve2_pin  17
#define pump_pin    18
#define lamp_pin    19

const char* ntpServer = "id.pool.ntp.org";
const long  gmtOffset_sec = 25200; // WIB (25200) | WITA (28800) | WIT (32400)
const int   daylightOffset_sec = 0;

#define FIREBASE_HOST "https://smart-farming-apps-default-rtdb.firebaseio.com/" 
#define FIREBASE_AUTH "0utKVYSasGhEI3zFDgkve0SKTkSjOokUJPurqyjN"

// data sensor
int sens_sm[2] = {34, 35};
int adc_plot[2], sm_plot[2];
char mHumd[3], mTemp[3], mPlot1[3], mPlot2[3];

int x = 0, rst_conuter = 0;
String data_settings_p1, data_settings_p2, data_settings_lamp, data_control;
String current_time, current_date, current_day;
int current_second, current_minute;

int humidity, humidity_val;
int temperature, temperature_val;

// Settings data
boolean day1[3], day2[3], day3[3], day4[3], day5[3], day6[3], day7[3];
int duration1[2], duration2[2];
unsigned int mDuration1[2], mDuration2[2];
String time1[2], time2[2], unit1[2], unit2[2];
String time_on, time_off;

// Control data
boolean auto_plot1, auto_plot2, auto_lamp, plot1, plot2, lamp;
boolean state_pump_plot1, state_pump_plot2;
String state;

// Post data
unsigned long startPost, currentPost;
int post_counter = 0;

// Timer
unsigned long startTimer[4], currentTimer[4];
boolean active_timer[4] = {false, false};
boolean active_event[4] = {false, false};
unsigned int timer_on[4] = {0, 0, 0, 0};

unsigned long startDelay, currentDelay;

FirebaseData fbdo;

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  for (int i = 0; i <= 3; i++) {
    if (active_timer[i] == true) {
      currentTimer[i] = millis();
      if (currentTimer[i] - startTimer[i] >= 1000) {
        startTimer[i] = currentTimer[i];
        timer_on[i]++;
        Serial.println("Timer ON : " + String(timer_on[i]));
      }
    }
    if (i >= 4)i = 0;
  }
  portEXIT_CRITICAL_ISR(&timerMux);
}

void setup() {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0); lcd.print("CONNECT TO Wi-FI");
  for(x; x<=15; x++){
    lcd.setCursor(x, 1); lcd.print("."); delay(100);
    Serial.println(x);
  }

  if(wm.autoConnect("SF-WiFi-Manager")) {
    Serial.println("connected...yeey :)");
  }else {
    Serial.println("Config portal running");
  }

  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000, true);
  timerAlarmEnable(timer);

  dht.begin();
  EEPROM.begin(4096);

  /** Accuracy Improvement ADC **/
  analogReadResolution(12);
  analogSetWidth(12);
  for (int i = 0; i <= 3; i++) {
    adcAttachPin(sens_sm[i]);
  }
  analogSetClockDiv(255); // clock 1338mS
  /** Accuracy Improvement ADC **/
  pinMode(valve1_pin, OUTPUT); digitalWrite(valve1_pin, LOW);
  pinMode(valve2_pin, OUTPUT); digitalWrite(valve2_pin, LOW);
  pinMode(pump_pin, OUTPUT);   digitalWrite(pump_pin, LOW);
  pinMode(lamp_pin, OUTPUT);   digitalWrite(lamp_pin, LOW);

  lcd.setCursor(0, 0); lcd.print("    NAMA HERI     ");
  lcd.setCursor(0, 1); lcd.print("   NIM 10121914   ");
  delay(2000);
  lcd.clear();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  post_counter = EEPROM.read(1);
  get_time(); control(); settings_plot1(); settings_plot2(); settings_lamp();
}

void loop() {
  wm.process();
  
  control(); get_time(); set_data(); post_data(); sensor();
  //Baca Setting
  if (state == "set-change") {
    settings_plot1(); settings_plot2(); settings_lamp();
    Firebase.setString(fbdo, "control/state", "set-apply");
  }
  // Reset Counter
  if (state == "rst-post-counter") {
    post_counter = 0;
    EEPROM.write(1, post_counter); EEPROM.commit();
    Firebase.setString(fbdo, "control/state", "set-apply");
  }

  //otomatis plot1
  if (auto_plot1 == true) {
    automatic_plot1();
    //Serial.println("Plot 1 - Mode auto");
  } else {
    if (plot1 == true) {
      state_pump_plot1 = true;
      digitalWrite(valve1_pin, HIGH);
    }
    if (plot1 == false) {
      state_pump_plot1 = false;
      digitalWrite(valve1_pin, LOW);
    }
  }

  //otomatis plot2
  if (auto_plot2 == true) {
    automatic_plot2();
    //Serial.println("Plot 2 - Mode auto");
  } else {
    if (plot2 == true) {
      state_pump_plot2 = true;
      digitalWrite(valve2_pin, HIGH);
    }
    if (plot2 == false) {
      state_pump_plot2 = false;
      digitalWrite(valve2_pin, LOW);
    }
  }

  if (state_pump_plot1 == true || state_pump_plot2 == true) {
    digitalWrite(pump_pin, HIGH);
    //lcd.noBacklight();
    //delay(100);
    lcd.backlight();
  } else {
    digitalWrite(pump_pin, LOW);
    //lcd.backlight();
    display_sens();
  }

  //otomatis lamp
  if (auto_lamp == true) {
    automatic_lamp();
    //Serial.println("Lamp - Mode auto");
  } else {
    if (lamp == true) {
      digitalWrite(lamp_pin, HIGH);
    } else {
      digitalWrite(lamp_pin, LOW);
    }
  }
}
