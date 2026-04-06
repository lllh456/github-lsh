#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "NWUNET-6G";
const char* password = "nwunet6g";

WebServer server(80);

#define LED_PIN 18
#define TOUCH_PIN T0

bool isArmed = false;
bool isAlarm = false;

void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>ex08 安防报警器</title>
<style>button{font-size:24px; padding:15px;}</style>
</head>
<body style="text-align:center;">
<h1>安防报警系统</h1>
<p><a href="/arm"><button>布防 Arm</button></a></p>
<p><a href="/disarm"><button>撤防 Disarm</button></a></p>
</body>
</html>
)rawliteral";
  server.send(200, "text/html; charset=utf-8", html);
}

void handleArm() {
  isArmed = true;
  isAlarm = false;
  server.send(200, "text/html", "已布防 <a href='/'>返回</a>");
}

void handleDisarm() {
  isArmed = false;
  isAlarm = false;
  digitalWrite(LED_PIN, LOW);
  server.send(200, "text/html", "已撤防 <a href='/'>返回</a>");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/arm", handleArm);
  server.on("/disarm", handleDisarm);
  server.begin();
}

void loop() {
  server.handleClient();

  if (isArmed && !isAlarm) {
    if (touchRead(TOUCH_PIN) <50) isAlarm = true;
  }

  if (isAlarm) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
}