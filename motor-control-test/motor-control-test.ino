#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *left_motor = AFMS.getMotor(1);
Adafruit_DCMotor *right_motor = AFMS.getMotor(2);
int sensor_pin_left = A0;    // select the input pin for the potentiometer
int sensor_value_left = 0;  // variable to store the value coming from the sensor
int sensor_pin_right = A1;    // select the input pin for the potentiometer
int sensor_value_right = 0;  // variable to store the value coming from the sensor

int delta_speed = 5;
int start_speed = 25;



void setup() {
  // put your setup code here, to run once:
  AFMS.begin();
  Serial.begin(9600);
  restart_speed();
}

void loop() {
  // put your main code here, to run repeatedly:


  read_sensor();

}

void read_sensor(){
  sensor_value_left = analogRead(sensor_pin_left);
  sensor_value_right = analogRead(sensor_pin_right);

  Serial.print(sensor_value_left);
  Serial.print(sensor_value_right);

//  determine_direction();
}

void determine_direction(){
  if (sensor_value_left > sensor_value_right){
    turn_left();
  } else if (sensor_value_right > sensor_value_left) {
    turn_right();
  } else {
    restart_speed();
  }
}

void restart_speed(){
  left_motor->setSpeed(start_speed);
  right_motor->setSpeed(start_speed);
  run_motors();
}

void turn_left(){
  left_motor->setSpeed(start_speed - delta_speed);
  right_motor->setSpeed(start_speed + delta_speed);
  run_motors();
}

void turn_right(){
  right_motor->setSpeed(start_speed - delta_speed);
  left_motor->setSpeed(start_speed + delta_speed);
  run_motors();
}

void run_motors(){
  left_motor->run(FORWARD);
  right_motor->run(FORWARD);
}
