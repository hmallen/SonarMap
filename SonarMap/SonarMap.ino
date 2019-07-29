/*
   SonarMap

   - Externally-tiggered HC-SR04 sonar mapper with
     servo-controlled sweep and data dump to serial.

   by Hunter Allen, 2019
*/

#include <Servo.h>

#define SERVO_PIN     9
#define SERVO_MIN     5
#define SERVO_MID     90
#define SERVO_MAX     175
#define SWEEP_TRIGGER 2
#define SAMPLE_COUNT  1
#define STEP_DELAY    65  // Higher than required for servo to optimize sonar read

#define SONAR_TRIGGER 11
#define SONAR_ECHO    12

Servo sonarServo;

bool debug_mode = true;

int servoPos = SERVO_MID;  // Center position
int relativePos = servoPos - 90;

void setup() {
  pinMode(SONAR_TRIGGER, OUTPUT);
  pinMode(SONAR_ECHO, INPUT);
  pinMode(SWEEP_TRIGGER, INPUT_PULLUP);

  sonarServo.attach(SERVO_PIN);
  //sonarServo.writeMicroseconds(1500); // Center servo
  sonarServo.write(servoPos); // Center servo

  delay(1000);

  Serial.begin(115200);

  /*if (debug_mode) {
    for (int x = 0; x < x <= 3; x++) {
      //FXN
      delay(3000);  //DELAY
    }

    while (true) {
      ;
    }
    }*/
}

void loop() {
  if (digitalRead(SWEEP_TRIGGER) == LOW) {
    while (digitalRead(SWEEP_TRIGGER) == LOW) {
      delay(1);
    }
    delay(10);

    sweepDistance();
  }
  else if (debug_mode) {
    sweepDistance();
    delay(3000);
  }
}

void sweepDistance() {
  for (servoPos = SERVO_MID; servoPos >= SERVO_MIN; servoPos = servoPos - 7) {
    if (servoPos < SERVO_MIN) break;//servoPos = SERVO_MIN;
    sonarServo.write(servoPos);
    delay(10);

    //Serial.print(servoPos);
    //relativePos = x - 90;
    //Serial.print(relativePos);
    Serial.print(servoPos);
    Serial.print(",");
    Serial.println(sonarDistance());
    delay(STEP_DELAY);
  }
  for (servoPos = SERVO_MIN; servoPos <= SERVO_MAX; servoPos = servoPos + 7) {
    if (servoPos > SERVO_MAX) break;//servoPos = SERVO_MAX;
    sonarServo.write(servoPos);
    delay(10);

    //Serial.print(servoPos);
    //relativePos = x - 90;
    //Serial.print(relativePos);
    Serial.print(servoPos);
    Serial.print(",");
    Serial.println(sonarDistance());
    delay(STEP_DELAY);
  }
  for (servoPos = SERVO_MAX; servoPos >= SERVO_MID; servoPos = servoPos - 7) {
    if (servoPos < SERVO_MID) break;//servoPos = SERVO_MID;
    sonarServo.write(servoPos);
    delay(10);

    //Serial.print(servoPos);
    //relativePos = servoPos - 90;
    //Serial.print(relativePos);
    Serial.print(servoPos);
    Serial.print(",");
    Serial.println(sonarDistance());
    delay(STEP_DELAY);
  }
}

int sonarDistance() {
  digitalWrite(SONAR_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(SONAR_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(SONAR_TRIGGER, LOW);

  long pingDuration = pulseIn(SONAR_ECHO, HIGH);
  long distanceIn = (pingDuration / 2) / 74;

  return distanceIn;
}
