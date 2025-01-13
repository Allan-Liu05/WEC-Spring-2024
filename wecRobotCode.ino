#include <Servo.h>

Servo boomArmServo;

const int servoPin = 7;

// controller analog inputs for potentiometer
const int leftPOT = A1;
const int boomArmPOT = A2;
const int rightPOT = A3;

// motor driver fwd/backwd toggle
const int left_one = 34;
const int left_two = 36;

const int right_one = 38;
const int right_two = 40;
// motor driver speed control -- PWM output
const int left_speed_pin = 11;
const int right_speed_pin = 12;

int leftVal = 0;
int boomArmAngle = 0;
int rightVal = 0;




int pot2Speed(int input) {
  int output = 0;
  if (input >= 0 && input <= 65){
    output = -255; //slow back speed
  }
  else if (input>65 && input <= 130){
    output = 0; //no speed
  }
  // else if (input>130 && input <= 195) {
  //   output = 65; //slow foward speed 1/3 of 255 (33% power)
  // }
   else if (input>195 && input <= 255) {
    output = 255; //max foward speed
  }
  return output;
}

void speed2PWM(int left, int right) {
  int leftSpeed = pot2Speed(left);
  int rightSpeed = pot2Speed(right);

  if (leftSpeed < 0) {
    leftSpeed *= -1;
    digitalWrite(left_one, LOW);
    digitalWrite(left_two, HIGH);
  } else if (leftSpeed > 0) {
    digitalWrite(left_one, HIGH);
    digitalWrite(left_two, LOW);
  }
  analogWrite(left_speed_pin, leftSpeed);

  if (rightSpeed < 0) {
    rightSpeed *= -1;
    digitalWrite(right_one, LOW);
    digitalWrite(right_two, HIGH);
  } else if (rightSpeed > 0) {
    digitalWrite(right_one, HIGH);
    digitalWrite(right_two, LOW);
  }
  analogWrite(right_speed_pin, rightSpeed);



  // // motor direction control
  // if (leftSpeed < 0 && rightSpeed > 0) {
  //   // ASSUMPTION - if one is high and two is low it means we are going forward, vice versa for backwards

  //   // left turn
  //   leftSpeed = leftSpeed * -1;
  //   digitalWrite(left_one, LOW);
  //   digitalWrite(left_two, HIGH);

  //   digitalWrite(right_one, HIGH);
  //   digitalWrite(right_two, LOW);
  // }
  // else if (leftSpeed > 0 && rightSpeed < 0) {
  //   // right turn
  //   rightSpeed = rightSpeed * -1;
  //   digitalWrite(left_one, HIGH);
  //   digitalWrite(left_two, LOW);

  //   digitalWrite(right_one, LOW);
  //   digitalWrite(right_two, HIGH);
  // }
  // else if (leftSpeed < 0 && right < 0) {
  //   // both backwards
  //   leftSpeed = leftSpeed * -1;
  //   rightSpeed = rightSpeed * -1;
  //   digitalWrite(left_one, LOW);
  //   digitalWrite(left_two, HIGH);

  //   digitalWrite(right_one, LOW);
  //   digitalWrite(right_two, HIGH);
  // }
  // else {
  //   // both forwards
  //   digitalWrite(left_one, HIGH);
  //   digitalWrite(left_two, LOW);

  //   digitalWrite(right_one, HIGH);
  //   digitalWrite(right_two, LOW);
  // }
  // // PWM output
  // analogWrite(left_speed_pin, leftSpeed);
  // analogWrite(right_speed_pin, rightSpeed);

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  boomArmServo.attach(servoPin);

  pinMode(left_one, OUTPUT);
  pinMode(left_two, OUTPUT);
  pinMode(right_one, OUTPUT);
  pinMode(right_two, OUTPUT);
  pinMode(left_speed_pin, OUTPUT);
  pinMode(right_speed_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  leftVal = map(analogRead(leftPOT),0,1023,0,255);
  boomArmAngle = map(analogRead(boomArmPOT),0,1023,0,180);
  rightVal = map(analogRead(rightPOT),0,1023,0,255);
  Serial.println("Left: " + String(leftVal) + " Right: " + String(rightVal) + " Boom: " + String(boomArmAngle));

  // below function controls motor speed and direction based off potentiometer readings!
  speed2PWM(leftVal, rightVal);

  //below function controls boom arm angle
 boomArmServo.write(boomArmAngle);

  // testing 
    //  analogWrite(left_speed_pin,255);
    //  analogWrite(right_speed_pin,255);
    // digitalWrite(right_one, LOW);
    // digitalWrite(right_two, HIGH);
    // digitalWrite(left_one, LOW);
    // digitalWrite(left_two, HIGH);
    }
