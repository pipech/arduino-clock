// include library
// lcd
#include <LiquidCrystal.h>
// speaker
#include <Tone.h>
Tone left_tone;

// initialize interface pin
// lcd
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 10, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// buttons
int b_h = 8;
int b_m = 7;
int b_startstop = 3;
// speaker
int left_sp = 9;

// setup variable
// clock
volatile int sec=0, minute = 0, hour = 0;
// buttons
bool set_clock = true;
// speaker
const int DTMF_freq1[] = { 1336, 1209, 1336, 1477, 1209, 1336, 1477, 1209, 1336, 1477 };

void setup() {

  // setup the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // setup buttons
  pinMode(b_h, INPUT_PULLUP);
  pinMode(b_m, INPUT_PULLUP);
  pinMode(b_startstop, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(b_startstop), set_btn_click, FALLING);

  // setup speaker
  left_tone.begin(left_sp);

  // debug
  Serial.begin(9600);
  Serial.println('HELLO WORLD!');
  play_sound();
}

void loop() {
  if (set_clock == false) {
    delay(1000);
    print_time();
    cal_time();
  } else {
    delay(100);
    print_time();
    set_time();
  }
}

void cal_time() {
  sec++;

  if (sec > 59)
  {
    minute++;
    sec = 0;
  }

  if (minute > 59)
  {
    hour++;
    minute = 0;
  }

  if (hour > 23)
  {
    hour = 0;
  }
}

void set_time() {
  sec = 0;

  if (digitalRead(b_h) == LOW)
  {
    hour++;
    if (hour > 23)
      hour = 0;
  }

  if (digitalRead(b_m) == LOW)
  {
    minute++;
    if (minute > 59)
      minute = 0;
  }

  if (digitalRead(b_m) == LOW && digitalRead(b_h) == LOW) {
    play_sound();
  }
}

void print_time() {
  lcd.setCursor(0, 0);

  lcd.print("Time: ");
  // hour
  if (hour < 10)
  {
    lcd.print("0");
    lcd.print(hour);
  }
  else
  {
    lcd.print(hour);
  }

  lcd.print(":");
  // minute
  if (minute < 10)
  {
    lcd.print("0");
    lcd.print(minute);
  }
  else
  {
    lcd.print(minute);

  }

  lcd.print(":");
  // sec
  if (sec < 10)
  {
    lcd.print("0");
    lcd.print(sec);
  }
  else
  {
    lcd.print(sec);
  }
  lcd.print(" ");
}

void set_btn_click() {
  lcd.clear();
  set_clock = !set_clock;
}

void play_sound() {
  Serial.println('playsound');
  for (int i=0; i<6; i++) {
    Serial.println(i);
    left_tone.play(DTMF_freq1[i], 500);
    delay(600);
  }
}