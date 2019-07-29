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
}

void loop() {
  // put your main code here, to run repeatedly:

}

void servoSweep() {
  for (int x = servoPos; x >= SERVO_MIN; x--) {
    //Serial.print(servoPos);
    relativePos = servoPos - 90;
    Serial.print(relativePos);
    Serial.print(",");
    Serial.println(sonarDistance());
    delay(STEP_DELAY);
  }
  for (int x = SERVO_MIN; x <= SERVO_MAX; x++) {
    //Serial.print(servoPos);
    relativePos = servoPos - 90;
    Serial.print(relativePos);
    Serial.print(",");
    Serial.println(sonarDistance());
    delay(STEP_DELAY);
  }
  for (int x = SERVO_MAX; x >= SERVO_MID; x--) {
    //Serial.print(servoPos);
    relativePos = servoPos - 90;
    Serial.print(relativePos);
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
