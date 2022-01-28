// MultiStepper.pde
// -*- mode: C++ -*-
// Use MultiStepper class to manage multiple steppers and make them all move to
// the same position at the same time for linear 2d (or 3d) motion.

#include <AccelStepper.h>
#include <MultiStepper.h>
#include <RTClib.h>

// Up to 10 steppers can be handled as a group by MultiStepper
MultiStepper steppers;

RTC_DS1307 rtc;



// EG X-Y position bed driven by 2 steppers
// Alas its not possible to build an array of these with different pins for each :-(
AccelStepper stepper1(AccelStepper::HALF4WIRE, 22, 26, 24, 28);
AccelStepper stepper2(AccelStepper::HALF4WIRE, 30, 34, 32, 36);
AccelStepper stepper3(AccelStepper::HALF4WIRE, 38, 42, 40, 44);
AccelStepper stepper4(AccelStepper::HALF4WIRE, 46, 50, 48, 52);

class TimerSetup {
      

  public:
    TimerSetup (uint8_t hourTens, uint8_t hourOnes, uint8_t minuteTens, uint8_t minuteOnes) {
      uint8_t hourTens = ((t.hour() / 10) % 3);
      uint8_t hourOnes = (t.hour() % 10);
      uint8_t minuteTens ((t.minute() / 10) % 6);
      uint8_t minuteOnes (t.minute() % 10);
    }




void timeSetup() {

  
  for (int hourTens = 0; hourTens < 3; hourTens++); {
    stepper1.moveTo(560.0);
  }
  
  for (int hourTens = 2; hourTens >= 0; hourTens--);{
    stepper1.moveTo(-560);
  
}

}

};

void setup() {

  Serial.begin(9600);

  // Configure each stepper
  stepper1.setMaxSpeed(1000);
  stepper1.setAcceleration(500.0);
  stepper2.setMaxSpeed(1000);
  stepper2.setAcceleration(500.0);
  stepper3.setMaxSpeed(1000);
  stepper3.setAcceleration(500.0);
  stepper4.setMaxSpeed(1000);
  stepper4.setAcceleration(500.0);

  // Then give them to MultiStepper to manage
  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);
  steppers.addStepper(stepper3);
  steppers.addStepper(stepper4);

  // Stop execution if the RTC clock is not present
  if (!rtc.begin()) {
    abort();
  }

}






void loop() {

  DateTime t = rtc.now();

  Serial.print((t.hour() / 10) % 3);
  Serial.print(t.hour() % 10);
  Serial.print(':');
  Serial.print((t.minute() / 10) % 6);
  Serial.print(t.minute() % 10);
  Serial.print(' ');

  long positions[4]; // Array of desired stepper positions

  positions[0] = ((t.hour() / 10) % 3);
  positions[1] = (t.hour() % 10);
  positions[2] = ((t.minute() / 10) % 6);
  positions[3] = (t.minute() % 10);
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(5000);


}
