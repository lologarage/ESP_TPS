#include <Arduino.h>

// An Emulated TPS for testing purposes.

// Motor Pins are GPIO signals from ESP_ECM for testing.
int MOTOR_PWM_PIN = 12; // high (+) or low(-) 
int MOTOR_IN_PIN = 14; // high (+) or low(-)

int TPS_1_PIN = 25; // analog signal out
int TPS_2_PIN = 26; // analog signal out

int tps_1_state = 0; // 1 = closed, 4 = open
int tps_2_state = 0; // 1 = closed, 4 = open

int motor_state = 0; // 0 off, -1 reverse, 1 foward

void setup() {
  Serial.begin(9600);
}

void runMotor() {
  int in = digitalRead(MOTOR_IN_PIN);
  int pwm = digitalRead(MOTOR_PWM_PIN);

  if(in == 0 && pwm == 0) {
    motor_state = 0; // stopped
  }

  if(in == 1 && pwm == 0) {
    motor_state = 1; // forward
    // TODO: count time running
  }
  if(in == 0 && pwm == 1) {
    motor_state = -1; // reverse
    // TODO: count time running
  }
}

void outputTPS() {
  // amount of time motor is "running" determines fake position
  // 0 - 255 ( 0v - 3.2v)
  dacWrite(TPS_1_PIN, 0);
}

void loop() {
  runMotor();

}