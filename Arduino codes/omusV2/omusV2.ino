#define TRIG_PIN 10
#define ECHO_PIN 9
#define IR_sensor_front 8  // front sensor
#define IR_sensor_back 7   // rear senson

const int IN1LF = 6;
const int IN2LB = 5;
const int IN3RB = 4;
const int IN4RF = 3;

float duration, distance;
bool compensate = true;
const float fflf = 0.9;   // frictionFactorLeftForward
const float ffrf = 1;     // frictionFactorRightForward
const float fflb = 0.72;  // frictionFactorLeftForward
const float ffrb = 1;     // frictionFactorRightForward

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  delay(1000);  // as per sumo compat roles if has to be 5000
  backward(255);
  delay(700);
  turnAround();
}

void loop() {
  int IR_front = digitalRead(IR_sensor_front);
  int IR_back = digitalRead(IR_sensor_back);

  if (IR_back == 0 && IR_front == 0) {
    Serial.println("Out of the arena");
    stop();
    // break;
  } else if (IR_front == 0) {
    stop();
    backward(255);
    delay(800);
    rotateRight(255);
    delay(200);
  } else if (IR_back == 0) {
    stop();
    forward(255);
  }

  // Write a pulse to the HC-SR04 Trigger Pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the response from the HC-SR04 Echo Pin
  duration = pulseIn(ECHO_PIN, HIGH);

  // Determine distance from duration
  // Using 343 metres per second as speed of sound
  distance = (duration / 2) * 0.0343;

  Serial.print("distance: ");
  Serial.println(distance);

  if (IR_front != 0 && IR_back != 0) {

    if (distance > 35) {
      Serial.println("looking around...");
      shortSpin();
    } else if (distance < 15) {
      if (compensate) compensateSpin();
      forward(255);
      compensate = false;
    } else {
      forward(100);
      compensate = true;
    }
  }
}

void forward(int speed) {
  Serial.print("forward with speed ");
  Serial.println(speed);
  analogWrite(IN1LF, speed * fflf);
  analogWrite(IN2LB, 0);
  analogWrite(IN3RB, 0);
  analogWrite(IN4RF, speed * ffrf);
  delay(50);
}

void backward(int speed) {  //gets rotated to the right side
  analogWrite(IN1LF, 0);
  analogWrite(IN2LB, speed * fflb);
  analogWrite(IN3RB, speed * ffrb);
  analogWrite(IN4RF, 0);
  delay(50);
}

void rotateLeft(int speed) {
  analogWrite(IN1LF, 0);
  analogWrite(IN2LB, 0);
  analogWrite(IN3RB, 0);
  analogWrite(IN4RF, speed);
  delay(50);
}

void rotateRight(int speed) {
  analogWrite(IN1LF, speed);
  analogWrite(IN2LB, 0);
  analogWrite(IN3RB, 0);
  analogWrite(IN4RF, 0);
  delay(50);
}

void spin(int speed) {
  analogWrite(IN1LF, 0);
  analogWrite(IN2LB, speed);
  analogWrite(IN3RB, 0);
  analogWrite(IN4RF, speed);
}

void stop() {
  analogWrite(IN1LF, 0);
  analogWrite(IN2LB, 0);
  analogWrite(IN3RB, 0);
  analogWrite(IN4RF, 0);
  delay(100);
}

void turnAround() {
  spin(255);
  delay(250);
  stop();
}

void thirtyDegreeSpin() {
  spin(255);
  delay(95);
  stop();
}

void shortSpin() {
  spin(255);
  delay(30);
  stop();
}

void compensateSpin() {
  analogWrite(IN1LF, 255);
  analogWrite(IN2LB, 0);
  analogWrite(IN3RB, 255);
  analogWrite(IN4RF, 0);
  delay(15);
}