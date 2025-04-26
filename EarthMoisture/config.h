// Set your local WiFi username and password. Please use a 2.4GHz access point
#define WIFI_SSID     ""
#define WIFI_PASSWORD ""

// For more information on where to get these values see: https://github.com/grafana/diy-iot/blob/main/README.md#sending-metrics
#define GC_INFLUX_URL ""  // example: "influx-blocks-prod-us-central1.grafana.net"
#define GC_USER ""
#define GC_PASS ""

// Set to 1 to show debug information on the LCD screen, or 0 to not display
// The debug information will show if you are able to connect to the WiFi or not, and whether writing the metrics to Prometheus was successful or not
#define LCD_SHOW_DEBUG_INFO "1"