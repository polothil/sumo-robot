const int IN1LF = 6;
const int IN2LB = 5;
const int IN3RB = 4;
const int IN4RF = 3;

const float fflf = 0.9;     // frictionFactorLeftForward
const float ffrf = 1;   // frictionFactorRightForward
const float fflb = 0.72;     // frictionFactorLeftForward
const float ffrb = 1;  // frictionFactorRightForward

void setup() {
  Serial.begin(9600);
  delay(1000);  // as per sumo compat roles if has to be 5000
}

void loop() {
  thirtyDegreeSpin();
  // forward(255);
  // delay(500);
  // stop();
  // delay(500);
  // rotateLeft(255);
  // delay(500);
  // stop();
  // delay(500);
  // rotateRight(255);
  // delay(500);
}

void forward(int speed) {
  analogWrite(IN1LF, speed * fflf);
  analogWrite(IN2LB, 0);
  analogWrite(IN3RB, 0);
  analogWrite(IN4RF, speed * ffrf);
}

void backward(int speed) {  //gets rotated to the right side 
  analogWrite(IN1LF, 0);
  analogWrite(IN2LB, speed * fflb);
  analogWrite(IN3RB, speed * ffrb);
  analogWrite(IN4RF, 0);
}

void rotateLeft(int speed) {
  analogWrite(IN1LF, 0);
  analogWrite(IN2LB, 0);
  analogWrite(IN3RB, 0);
  analogWrite(IN4RF, speed);
}

void rotateRight(int speed) {
  analogWrite(IN1LF, speed);
  analogWrite(IN2LB, 0);
  analogWrite(IN3RB, 0);
  analogWrite(IN4RF, 0);
}

void spin(int speed) {
  analogWrite(IN1LF, speed);
  analogWrite(IN2LB, 0);
  analogWrite(IN3RB, speed);
  analogWrite(IN4RF, 0);
}

void stop() {
  analogWrite(IN1LF, 0);
  analogWrite(IN2LB, 0);
  analogWrite(IN3RB, 0);
  analogWrite(IN4RF, 0);
  delay(500);
}

void thirtyDegreeSpin() {
  spin(255);
  delay(95);
  stop();
}