
// Written for Grafana Labs to demonstrate how to use the M5Stick CPlus2 with Grafana Cloud at GrafanaCon 2025
// 2025/04/25
// Willie Engelbrecht - willie.engelbrecht@grafana.com
// Introduction to time series: https://grafana.com/docs/grafana/latest/fundamentals/timeseries/
// M5StickCPlus2: https://docs.m5stack.com/en/core/M5StickC%20PLUS2
// Register for a free Grafana Cloud account including free metrics and logs: https://grafana.com
#include <M5StickCPlus.h>
#include <HTTPClient.h>
#include <WiFi.h>

#define soil_moisture_pin 33

// ===================================================
// All the things that needs to be changed 
// Your local WiFi details
// Your Grafana Cloud details
// ===================================================
#include "config.h"

//TFT_eSprite Disbuff = TFT_eSprite(&M5.Lcd);
HTTPClient http;

void setup() {
    Serial.begin(9600);

    M5.begin();  
    // set Lcd
/*    M5.Lcd.setRotation(3);
    M5.Lcd.setSwapBytes(false);
    Disbuff.createSprite(240, 135);
    Disbuff.setSwapBytes(true);
    Disbuff.createSprite(240, 135);
*/

    initWifi();

    http.begin("https://" + String(GC_USER) + ":" + String(GC_PASS) + "@" + String(GC_INFLUX_URL) + "/api/v1/push/influx/write");  // Specify the URL
    http.addHeader("Content-Type", "application/json");  // Set content type
}



void initWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi");
  int wifi_loop_count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

    // Restart the device if we can't connect to WiFi after 2 minutes
    wifi_loop_count += 1;
    if (wifi_loop_count > 40) {
      ESP.restart();
    }
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
  int soilMoisture = analogRead(soil_moisture_pin);
  int soilMoisturePCT = map(soilMoisture, 1000, 4095, 0, 100);
  Serial.println("Soil Dryness in percent: " + String(soilMoisturePCT) + "%" + " Raw Data: " + String(soilMoisture));

  // Send to Grafana Cloud
  String postData = "";
  postData = "m5Soil,location=home moisture=" + String(soilMoisturePCT);
  int httpResponseCode = http.POST(postData);

/*
  Disbuff.setTextSize(3);
  Disbuff.fillRect(0, 0, 240, 135, BLACK);
  Disbuff.setCursor(15, 25);
  if (soilMoisturePCT < 75) {
      Disbuff.setTextColor(GREEN);
      Disbuff.println("Soil is wet!");
      Disbuff.setCursor(15, 55);
      Disbuff.println(String(soilMoisturePCT) + "% dry");
  } else {
      Disbuff.setTextColor(RED);
      Disbuff.println("Soil is dry!");      
      Disbuff.setCursor(15, 55);
      Disbuff.println(String(soilMoisturePCT) + "% dry");
  }
  Disbuff.pushSprite(0, 0);
*/

  delay(2000);
}
