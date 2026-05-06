const int DS = 12;
const int SH_CP = 11;
const int ST_CP = 10;
const int green_LED_Indicator = 3;
const int button = 2;
const int totalSettings = 2;
bool LED_State = false;
int number;
int setting = 0;
unsigned long previous_LED_activation = 0;
unsigned long previous_click = 0;


bool buttonPressed() {
  if (!digitalRead(button)) {
    return 1;
  } else
    return 0;
}

bool LED_Interval(int interval) {
  unsigned long current = millis();
  if (current - previous_LED_activation >= interval) {
    previous_LED_activation = current;
    return true;
  } else {
    return false;
  }
}

void updateCooldownIndicator() {
  unsigned long current = millis();
  if (current - previous_click > 1500) {
    digitalWrite(green_LED_Indicator, LOW);
  } else {
    digitalWrite(green_LED_Indicator, HIGH);
  }
}
bool buttonCooldownReady() {
  unsigned long current_click = millis();
  if (buttonPressed() && current_click - previous_click >= 1500) {
    previous_click = current_click;
    return true;
  } else
    return false;
}

void selectSetting() {
  updateCooldownIndicator();
  unsigned long current_click = millis();
  if (buttonPressed() && setting < totalSettings && buttonCooldownReady()) {
    setting++;
  }
  if (buttonPressed() && setting >= totalSettings && buttonCooldownReady()) {
    setting = 0;
  }
}

void setup() {
  pinMode(DS, OUTPUT);
  pinMode(SH_CP, OUTPUT);
  pinMode(ST_CP, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(green_LED_Indicator, OUTPUT);
}

void loop() {
  if (setting == 0) {
    LED_State = false;
    while (setting == 0) {
      selectSetting();
      if (setting != 0)
        break;
      bool LED = LED_Interval(500);
      if (LED && !LED_State) {
        digitalWrite(ST_CP, LOW);
        shiftOut(DS, SH_CP, LSBFIRST, B10101010);
        digitalWrite(ST_CP, HIGH);
        LED_State = true;
      } else if (LED && LED_State) {
        digitalWrite(ST_CP, LOW);
        shiftOut(DS, SH_CP, MSBFIRST, B10101010);
        digitalWrite(ST_CP, HIGH);
        LED_State = false;
      }
    }
  }
  if (setting == 1) {
    number = 1;
    while (setting == 1) {
      selectSetting();
      if (setting != 1)
        break;
      delay(50);
      digitalWrite(ST_CP, LOW);
      shiftOut(DS, SH_CP, LSBFIRST, number);
      if (number < 128) {
        number = number * 2;
      } else
        number = 1;
      digitalWrite(ST_CP, HIGH);
    }
  }
  if (setting == 2) {
    number = 0;
    int j = 7;
    while (setting == 2 && j >= 0) {
      selectSetting();
      if (setting != 2)
        break;
      delay(350);
      int temp_numb = 1;
      digitalWrite(ST_CP, LOW);
      number += 1;
      shiftOut(DS, SH_CP, LSBFIRST, number);
      digitalWrite(ST_CP, HIGH);
      for (int i = 0; i < j; i++) {
        selectSetting();
        if (setting != 2)
          break;
        delay(50);
        digitalWrite(ST_CP, LOW);
        number = number + temp_numb;
        temp_numb = temp_numb * 2;
        shiftOut(DS, SH_CP, LSBFIRST, number);
        digitalWrite(ST_CP, HIGH);
      }
      j--;
    }
    for (int i = 0; i < 9; i++) {
      selectSetting();
      if (setting != 2)
        break;
      delay(50);
      digitalWrite(ST_CP, LOW);
      shiftOut(DS, SH_CP, LSBFIRST, number);
      number = number * 2;
      digitalWrite(ST_CP, HIGH);
    }
  }
}