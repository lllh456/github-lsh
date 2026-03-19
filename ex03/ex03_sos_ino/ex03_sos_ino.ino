const int ledPin = 2;

const int dotTime = 200;    // 短亮
const int dashTime = 600;   // 长亮
const int betweenTime = 200;// 闪与闪之间的间隔
const int charSpace = 500;   // 字母间隔
const int wordSpace = 2000; // 一组结束间隔

unsigned long previousTime = 0;
int step = 0; // 一步一步走流程

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long now = millis();

  // 三次短闪 
  if (step == 0) {
    digitalWrite(ledPin, HIGH);
    if (now - previousTime >= dotTime) {
      digitalWrite(ledPin, LOW);
      previousTime = now;
      step = 1;
    }
  }
  else if (step == 1) {
    if (now - previousTime >= betweenTime) {
      previousTime = now;
      step = 2;
    }
  }
  else if (step == 2) {
    digitalWrite(ledPin, HIGH);
    if (now - previousTime >= dotTime) {
      digitalWrite(ledPin, LOW);
      previousTime = now;
      step = 3;
    }
  }
  else if (step == 3) {
    if (now - previousTime >= betweenTime) {
      previousTime = now;
      step = 4;
    }
  }
  else if (step == 4) {
    digitalWrite(ledPin, HIGH);
    if (now - previousTime >= dotTime) {
      digitalWrite(ledPin, LOW);
      previousTime = now;
      step = 5;
    }
  }
  else if (step == 5) {
    if (now - previousTime >= charSpace) {
      previousTime = now;
      step = 6;
    }
  }

  //  三次长闪 
  else if (step == 6) {
    digitalWrite(ledPin, HIGH);
    if (now - previousTime >= dashTime) {
      digitalWrite(ledPin, LOW);
      previousTime = now;
      step = 7;
    }
  }
  else if (step == 7) {
    if (now - previousTime >= betweenTime) {
      previousTime = now;
      step = 8;
    }
  }
  else if (step == 8) {
    digitalWrite(ledPin, HIGH);
    if (now - previousTime >= dashTime) {
      digitalWrite(ledPin, LOW);
      previousTime = now;
      step = 9;
    }
  }
  else if (step == 9) {
    if (now - previousTime >= betweenTime) {
      previousTime = now;
      step = 10;
    }
  }
  else if (step == 10) {
    digitalWrite(ledPin, HIGH);
    if (now - previousTime >= dashTime) {
      digitalWrite(ledPin, LOW);
      previousTime = now;
      step = 11;
    }
  }
  else if (step == 11) {
    if (now - previousTime >= charSpace) {
      previousTime = now;
      step = 12;
    }
  }

  // 三次短闪 
  else if (step == 12) {
    digitalWrite(ledPin, HIGH);
    if (now - previousTime >= dotTime) {
      digitalWrite(ledPin, LOW);
      previousTime = now;
      step = 13;
    }
  }
  else if (step == 13) {
    if (now - previousTime >= betweenTime) {
      previousTime = now;
      step = 14;
    }
  }
  else if (step == 14) {
    digitalWrite(ledPin, HIGH);
    if (now - previousTime >= dotTime) {
      digitalWrite(ledPin, LOW);
      previousTime = now;
      step = 15;
    }
  }
  else if (step == 15) {
    if (now - previousTime >= betweenTime) {
      previousTime = now;
      step = 16;
    }
  }
  else if (step == 16) {
    digitalWrite(ledPin, HIGH);
    if (now - previousTime >= dotTime) {
      digitalWrite(ledPin, LOW);
      previousTime = now;
      step = 17;
    }
  }
  else if (step == 17) {
    if (now - previousTime >= wordSpace) {
      previousTime = now;
      step = 0; // 重头再来
    }
  }
}
