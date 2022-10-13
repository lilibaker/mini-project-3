#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *left_motor = AFMS.getMotor(1);
Adafruit_DCMotor *right_motor = AFMS.getMotor(2);
int sensor_pin_left = A1;    // select the input pin for the potentiometer
float sensor_value_left = 0;  // variable to store the value coming from the sensor
int sensor_pin_right = A0;    // select the input pin for the potentiometer
float sensor_value_right = 0;  // variable to store the value coming from the sensor

int right_motor_speed = 40;
int left_motor_speed = 30;


void setup() {
  // put your setup code here, to run once:
  AFMS.begin();
  Serial.begin(9600);
  restart_speed();
}

void loop() {
  // put your main code here, to run repeatedly:

//  restart_speed();
  read_sensor();

}

void read_sensor(){
  sensor_value_left = analogRead(sensor_pin_left);
  sensor_value_right = analogRead(sensor_pin_right);

//  float sensor_value_left_scale = (sensor_value_left  - 743 ) / 87;
//  float sensor_value_right_scale = (sensor_value_right - 557) / 173;


  Serial.print("Left: ");
  Serial.print(sensor_value_left);
  Serial.print("  Right: ");
  Serial.println(sensor_value_right);

  determine_direction(sensor_value_left, sensor_value_right);
}

void determine_direction(float sensor_value_left, float sensor_value_right){
  // l 934 r 952
  // l 992 r 994
  if (sensor_value_left > 949){
    turn_right();
  } else if (sensor_value_right > 967) {
    turn_left();
  } else {
    restart_speed();
  }
  delay(50);
}

void restart_speed(){
  int current_left_motor = left_motor_speed;
  int current_right_motor = right_motor_speed;
  
  left_motor->setSpeed(current_left_motor);
  right_motor->setSpeed(current_right_motor);
  Serial.print("Left m: ");
  Serial.print(current_left_motor);
  Serial.print("  Right m: ");
  Serial.println(current_right_motor);
  
  left_motor->run(BACKWARD);
  right_motor->run(FORWARD);
}

void turn_left(){
  int current_left_motor = left_motor_speed;
  int current_right_motor = right_motor_speed - 10;
  
  left_motor->setSpeed(current_left_motor);
  right_motor->setSpeed(current_right_motor);

  Serial.print("Left m: ");
  Serial.print(current_left_motor);
  Serial.print("  Right m: ");
  Serial.println(current_right_motor);
  
  left_motor->run(BACKWARD);
  right_motor->run(BACKWARD);
}

void turn_right(){
  int current_left_motor = left_motor_speed - 10;
  int current_right_motor = right_motor_speed;
  
  left_motor->setSpeed(current_left_motor);
  right_motor->setSpeed(current_right_motor);

  Serial.print("Left m: ");
  Serial.print(current_left_motor);
  Serial.print("  Right m: ");
  Serial.println(current_right_motor);
  
  left_motor->run(FORWARD);
  right_motor->run(FORWARD);
}
