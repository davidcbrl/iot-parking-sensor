#include <Arduino.h>
#include <Ultrasonic.h>

#define pin_trigger 5
#define pin_echo 6
#define pin_buzzer 7
#define pin_led_1 8
#define pin_led_2 9
#define pin_led_3 10

#define buzzer_tone 1000

#define min_distance 30
#define breakpoint min_distance/3
#define far breakpoint*3
#define normal breakpoint*2
#define close breakpoint*1

Ultrasonic ultrasonic(pin_trigger, pin_echo);

void setup() {
  Serial.begin(9600);

  pinMode(pin_buzzer, OUTPUT);
  pinMode(pin_led_1, OUTPUT);
  pinMode(pin_led_2, OUTPUT);
  pinMode(pin_led_3, OUTPUT);
}

void bip() {
  tone(pin_buzzer, buzzer_tone);
  delay(25);
  noTone(pin_buzzer);
}


void loop() {
  long microsec = ultrasonic.timing();
  float distance = ultrasonic.convert(microsec, Ultrasonic::CM);

  Serial.print("\n");
  Serial.print(distance);

  if (distance < min_distance) {
    
    if (distance <= close) {
      digitalWrite(pin_led_1, HIGH);
      delay(50);
      bip();
    } else {
      digitalWrite(pin_led_1, LOW);
    }
    
    if (distance >= close && distance <= normal) {
      digitalWrite(pin_led_2, HIGH);
      delay(200);
      bip();
    } else if (distance >= close) {
      digitalWrite(pin_led_2, LOW);
    }
    
    if (distance >= normal && distance <= far) {
      digitalWrite(pin_led_3, HIGH);
      delay(400);
      bip();
    }
  
  } else {
    digitalWrite(pin_led_1, LOW);
    digitalWrite(pin_led_2, LOW);
    digitalWrite(pin_led_3, LOW);
    noTone(pin_buzzer);
  }
}
