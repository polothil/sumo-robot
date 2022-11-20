
// #include <hcsr04.h>

#define TRIG_PIN 10
#define ECHO_PIN 9

// HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);


const int IN1 = 6;
const int IN2 = 5;
const int IN3 = 4;
const int IN4 = 3;
#define IR_sensor_front 8  // front sensor
#define IR_sensor_back 7   // rear senson

float duration, distance;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  delay(1000);  // as per sumo compat roles
}
void loop() {

  int IR_front = digitalRead(IR_sensor_front);
  int IR_back = digitalRead(IR_sensor_back);

  // Write a pulse to the HC-SR04 Trigger Pin

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the response from the HC-SR04 Echo Pin

  duration = pulseIn(ECHO_PIN, HIGH);

  // Determine distance from duration
  // Use 343 metres per second as speed of sound

  distance = (duration / 2) * 0.0343;

  Serial.print("distance: ");
  Serial.println(distance);

  if (IR_front != 0 && IR_back != 0) {
    if (distance < 60 && distance > 30) {
      Serial.println("Out of range");
      ROTATE(255);
    } else {
      FORWARD(255);
    }
  }

  // delay(500);


  if (IR_front == 0) {
    Stop();
    delay(50);
    BACKWARD(255);
    delay(500);
  }

  if (IR_back == 0) {
    Stop();
    delay(50);
    ESCAPE(255);
    BACKWARD(255);
    delay(500);
  }

  // distance = hcsr04.distanceInMillimeters() / 10;
  // Serial.print("distance: ");
  // Serial.println(distance);
  // if (distance > 30) {
  //   ROTATE(255);
  // }

  // if (distance < 30) {
  //   // ROTATE(0);
  //   // Stop();
  //   while (distance < 30) {

  //     FORWARD(255);

  //     // distance = hcsr04.distanceInMillimeters() / 10;
  //     IR_front = digitalRead(IR_sensor_front);
  //     IR_back = digitalRead(IR_sensor_back);
  //     if (IR_front == 0 || IR_back == 0) { break; }
  //     delay(10);
  //   }
  // }





  // if (IR_front == 0) {
  //   Stop();
  //   delay(50);
  //   BACKWARD(255);
  //   delay(500);
  // }

  // if (IR_back == 0)  //
  // {
  //   Stop();
  //   delay(50);
  //   FORWARD(255);
  //   delay(500);
  // }


  // Serial.println(distance);
  //Serial.println("cm");
  //Serial.println("IR front :");
  //Serial.println(IR_front);
  //Serial.println("IR back :");
  //Serial.println(IR_back);


}  //--------------------------------------------
void FORWARD(int Speed) {
  //When we want to let Motor To move forward,
  // just void this part on the loop section .
  Serial.println("Attack!");
  analogWrite(IN1, Speed);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, Speed);
  delay(100);
}  //--------------------------------------------
void BACKWARD(int Speed) {
  //When we want to let Motor To move forward,
  // just void this part on the loop section .
  Serial.println("Retreat!");
  analogWrite(IN1, 0);
  analogWrite(IN2, Speed);
  analogWrite(IN3, Speed);
  analogWrite(IN4, 0);
}  //--------------------------------------------
void ROTATE(int Speed) {
  //When we want to let Motor To Rotate ,
  // just void this part on the loop section .
  Serial.println("Looking for enemy!");
  analogWrite(IN1, Speed);
  analogWrite(IN2, 0);
  analogWrite(IN3, Speed);
  analogWrite(IN4, 0);
  delay(100);
  Stop();
  delay(500);
}  //--------------------------------------------
void ESCAPE(int Speed) {
  //When we want to let Motor To Rotate ,
  // just void this part on the loop section .
  Serial.println("Escape!");
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, Speed);
  analogWrite(IN4, 0);
  delay(500);
}  //--------------------------------------------

void Stop() {
  //When we want to  Motor To stop ,
  // just void this part on the loop section .
  Serial.println("STOP");
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}
