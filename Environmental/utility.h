#include "M5Unified.h"

// ===================================================
// Includes - Needed to write Prometheus or Loki metrics/logs to Grafana Cloud
// No need to change anything here
// ===================================================
#include "certificates.h"
#include <PromLokiTransport.h>
#include <PrometheusArduino.h>

int upload_fail_count = 0;

void check_buttonA(PromClient::SendResult res) {
  M5.update();
        // Check if Button A (front) was pressed
        if (M5.BtnA.wasPressed()) {
            M5.Lcd.fillRect(0,0,256,256,BLACK);
            M5.Display.setCursor(10, 10);
            M5.Display.setTextColor(ORANGE, BLACK);
            M5.Display.printf("== System Status ==");
            M5.Display.setTextColor(WHITE, BLACK);

            if (LCD_SHOW_DEBUG_INFO == "1") {                 
                // Are we connected to WiFi or not ?
                M5.Display.setCursor(0, 45);
                if (WiFi.status() != WL_CONNECTED) {
                    M5.Display.setTextColor(WHITE, BLACK);
                    M5.Display.printf("  Wifi: ");
                    M5.Display.setTextColor(RED, BLACK);
                    M5.Display.printf("Not connected!");
                }
                else {          
                    M5.Display.printf("  Wifi: ");
                    M5.Display.setTextColor(GREEN, BLACK);
                    M5.Display.printf("Connected");
                }

                // Are we able to upload metrics or not - display on the LCD screen if configured in config.h
                M5.Display.setCursor(0, 75);
                    if (res == 0) {
                    upload_fail_count = 0;
                    M5.Display.setTextColor(WHITE, BLACK);
                    M5.Display.printf("  Upload ");
                    M5.Display.setTextColor(GREEN, BLACK);
                    M5.Display.printf("Complete");
                } else {
                    upload_fail_count += 1;
                    M5.Display.setTextColor(WHITE, BLACK);
                    M5.Display.printf("  Upload ");
                    M5.Display.setTextColor(RED, BLACK);
                    M5.Display.printf("Failed: %s", String(upload_fail_count));
                }
            }
        }
        delay(250);
}