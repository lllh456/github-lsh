#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "NWUNET-6G";
const char* password = "nwunet6g";

WebServer server(80);

#define LED_PIN 2

void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>ex07 无极调光</title>
</head>
<body style="text-align:center; margin-top:50px;">
<h1>ESP32 Web 无极调光</h1>
<p>亮度：<span id="val">0</span></p>
<input type="range" min="0" max="255" id="slider" style="width:80%;height:30px;">

<script>
const slider = document.getElementById('slider');
const val = document.getElementById('val');

slider.oninput = function() {
  val.textContent = this.value;
  fetch('/set?bright=' + this.value);
};
</script>
</body>
</html>
)rawliteral";
  server.send(200, "text/html; charset=utf-8", html);
}

void handleSet() {
  if (server.hasArg("bright")) {
    int bright = server.arg("bright").toInt();
    analogWrite(LED_PIN, bright);
  }
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  analogWrite(LED_PIN, 0);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n连接成功");
  Serial.print("访问地址: http://");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/set", handleSet);
  server.begin();
}

void loop() {
  server.handleClient();
}