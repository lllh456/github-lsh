#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "NWUNET-6G";
const char* password = "nwunet6g";

WebServer server(80);
#define TOUCH_PIN T0

void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>ex09 传感器实时显示</title>
<style>#val{font-size:60px; color:blue;}</style>
</head>
<body style="text-align:center;">
<h1>实时触摸传感器值</h1>
<div id="val">0</div>

<script>
function update(){
  fetch('/data').then(res=>res.text()).then(v=>{
    document.getElementById('val').textContent = v;
  });
}
setInterval(update, 100);
</script>
</body>
</html>
)rawliteral";
  server.send(200, "text/html; charset=utf-8", html);
}

void handleData() {
  int val = touchRead(TOUCH_PIN);
  server.send(200, "text/plain", String(val));
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
}

void loop() {
  server.handleClient();
}