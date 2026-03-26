// 定义触摸引脚 (T0对应GPIO4)
#define TOUCH_PIN 4
// 定义LED引脚 (ESP32 DevKit板载LED通常是GPIO2)
#define LED_PIN 2
// 中断模式设置：0为轮询模式，1为中断模式
#define EXT_ISR_MODE 0

// 阈值，需要通过串口监视器观察并调整
int threshold = 20; 
// 触摸值
int touchValue;
bool ledState = false;       // LED当前状态
bool lastTouched = false;    // 上一次是否触摸
unsigned long lastDebounce = 0;
unsigned long debounceTime = 150;  // 防抖时间

void setup() {
  Serial.begin(115200);
  delay(1000); // 等待串口稳定

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
}

void loop() {
  touchValue = touchRead(TOUCH_PIN);
  Serial.print("Touch Value: ");
  Serial.println(touchValue);

  bool isTouched = (touchValue < threshold);
  unsigned long now = millis();

  // 防抖 + 边缘检测（只在刚触摸的瞬间触发）
  if (now - lastDebounce > debounceTime) {
    // 从 未触摸 → 触摸 的跳变沿
    if (isTouched && !lastTouched) {
      ledState = !ledState;    // 翻转状态
      digitalWrite(LED_PIN, ledState);
      lastDebounce = now;
    }
    lastTouched = isTouched;
  }
  delay(100);
}
