#include <Arduino.h>

// An Emulated TPS for testing purposes.

// Motor Pins are GPIO signals from ESP_ECM for testing.
int MOTOR_PWM_PIN = 12; // high (+) or low(-) 
int MOTOR_IN_PIN = 14; // high (+) or low(-)

int TPS_1_PIN = 25; // analog signal out
int TPS_2_PIN = 26; // analog signal out

// Fake Signals
int tps_1_state = 0; // 0- 255, (closed - open) represents a voltage 0 - 3.3v
int tps_2_state = 0; // 0- 255, (closed - open) represents a voltage 0 - 3.3v
int motor_state = 0; // 0 off, -1 reverse, 1 foward
int tps_signal = 0; 

void setup() {
  Serial.begin(115200);
}

void runMotor() {
  int in = digitalRead(MOTOR_IN_PIN);
  int pwm = digitalRead(MOTOR_PWM_PIN);

  Serial.println("Motor " + String(in) + " , " + String(pwm));

  if(in == 0 && pwm == 0) {
    motor_state = 0; // stopped
  }

  if(in == 1 && pwm == 0) {
    motor_state = 1; // forward
    // fake tps reading
    if(tps_1_state < 255) {
      tps_1_state++;
    }
  }
  if(in == 0 && pwm == 1) {
    motor_state = -1; // reverse
    // fake tps reading
    if(tps_1_state > 0) {
      tps_1_state--;
    }
  }
}

void outputTPS() {
  dacWrite(TPS_1_PIN, tps_1_state);
  dacWrite(TPS_2_PIN, tps_1_state);
}

void loop() {
  runMotor();
  outputTPS();
}