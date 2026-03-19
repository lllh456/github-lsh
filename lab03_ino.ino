const int ledPin = 2;  
const int ledPin_R = 17;

const int freq = 5000;
const int resolution = 8;

void setup() {
  Serial.begin(115200);
  ledcAttach(ledPin, freq, resolution);
  ledcAttach(ledPin_R, freq, resolution);
}

void loop() {
  // 灯1渐亮，灯2渐暗
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    ledcWrite(ledPin, dutyCycle);   
    ledcWrite(ledPin_R, 255 - dutyCycle); 
    delay(10);
  }

  // 灯1渐暗，灯2渐亮
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    ledcWrite(ledPin, dutyCycle);   
    ledcWrite(ledPin_R, 255 - dutyCycle);  
    delay(10);
  }
}
