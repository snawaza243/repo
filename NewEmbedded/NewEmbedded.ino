#include <Servo.h>
#include <Wire.h>
#include "esp_camera.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <LiquidCrystal_I2C.h>

#define TRIG_PIN 12
#define ECHO_PIN 14
#define SERVO_PIN 27
#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

Servo myservo;
int angle = 0;

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* gdrive_token = "your_GDRIVE_TOKEN";

WiFiClientSecure client;
HTTPClient http;

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

String get_gdrive_folder_id() {
  client.setAuthorization("Bearer " + String(gdrive_token));
  http.begin(client, "https://www.googleapis.com/drive/v3/files?q=name%3D%27SmartParking%27+and+mimeType%3D%27application%2Fvnd.google-apps.folder%27&fields=files(id)&key=YOUR_API_KEY");
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.GET();
  String folder_id = "";
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, payload);
    if (!error) {

      http.beginRequest();
      http.write(request_body.c_str(), request_body.length());
      int bytes_sent = 0;
      while (bytes_sent < file_size) {
        int bytes_to_read = file_size - bytes_sent;
        if (bytes_to_read > 1024) { bytes_to_read = 1024; }
        uint8_t buffer[bytes_to_read];
        int bytes_read = file.read(buffer, bytes_to_read);
        http.write(buffer, bytes_read);
        bytes_sent += bytes_read;
      }
      http.endRequest();
      String response = http.getString();
      http.end();
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  myservo.attach(SERVO_PIN);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Parking");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = 5;
  config.pin_d1 = 18;
  config.pin_d2 = 19;
  config.pin_d3 = 21;
  config.pin_d4 = 36;
  config.pin_d5 = 39;
  config.pin_d6 = 34;
  config.pin_d7 = 35;
  config.pin_xclk = 0;
  config.pin_pclk = 22;
  config.pin_vsync = 25;
  config.pin_href = 23;
  config.pin_sscb_sda = 26;
  config.pin_sscb_scl = 27;
  config.pin_pwdn = -1;
  config.pin_reset = -1;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  if (psramFound()) {
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Parking");
  lcd.setCursor(0, 1);
  lcd.print("Ready");
  delay(2000);
}

void loop() {
  float duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;
  int available_slots = distance / 50;
  if (available_slots < 0) { available_slots = 0; }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Available slots:");
  lcd.setCursor(0, 1);
  lcd.print(String(available_slots));
  if (available_slots > 0) {

    float angle = map(available_slots, 0, MAX_SLOTS, 0, 180);
    myservo.write(angle);
    delay(500);
    camera_fb_t* fb = NULL;
    fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Failed to capture image");
      return;
    }
    Serial.printf("Captured image with size %u\n", fb->len);
    uploadToGoogleDrive(fb);
    esp_camera_fb_return(fb);
    delay(5000);
  }
}
