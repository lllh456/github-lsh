#define TOUCH_PIN 4
#define LED_PIN 2

// 设置PWM属性
const int freq = 5000;          // 频率 5000Hz
const int resolution = 8;   
int speedLevel = 1;       // 默认1档（慢）
int delayTime;           // 延时时间，由档位决定

// 触摸防抖变量
bool lastTouched = false;
unsigned long lastDebounce = 0;
const unsigned long debounceTime = 200;    // 分辨率 8位 (0-255)

void setup() {
  Serial.begin(115200);
  ledcAttach(LED_PIN , freq, resolution);
}

void loop() {
  // 逐渐变亮
   int touchValue = touchRead(TOUCH_PIN);
  bool isTouched = (touchValue < 20); // 触摸判断
  unsigned long now = millis();

  // 防抖 + 边缘检测
  if (now - lastDebounce > debounceTime) {
    // 刚触摸时切换档位
    if (isTouched && !lastTouched) {
      speedLevel++;          // 档位+1
      if (speedLevel > 3) {  // 超过3档回到1档
        speedLevel = 1;
      }
      lastDebounce = now;
      Serial.print("当前档位：");
      Serial.println(speedLevel);
    }
    lastTouched = isTouched;
  }

  // ====================== 【根据档位设置速度】 ======================
  if (speedLevel == 1) {
    delayTime = 15;  // 1档：慢
  } else if (speedLevel == 2) {
    delayTime = 8;   // 2档：中
  } else {
    delayTime = 3;   // 3档：快
  }

  // ====================== 【呼吸灯效果】 ======================
  // 逐渐变亮
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
    ledcWrite(LED_PIN, dutyCycle);
    delay(delayTime); // 使用档位延时
  }
  // 逐渐变暗
  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
    ledcWrite(LED_PIN, dutyCycle);
    delay(delayTime); // 使用档位延时
  }
}