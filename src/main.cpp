#include <Arduino.h>
#include <Servo.h>

#define dirPin 12
#define stepPin 13
#define stepsPerRevolution 200
int accel = 3000;
const int speed = 2000;
const float dist_per_rev = 20.7345;

// creating objects of class servo
Servo s1;
Servo s2;
Servo s3;
Servo gripper;
Servo wheel;


void setup() {
  Serial.begin(115200);
  // Attaching servos to pins (Make sure these are PWM pins on arduino board)
  delay(3000);
  // home servos
  s1.write(65);
  s2.write(5);
  s3.write(15);
  gripper.write(40);
  delay(1000);

  s1.attach(11);
  s2.attach(10);
  s3.attach(9);
  gripper.attach(7);
  wheel.attach(8);


  pinMode (dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  delay(2000);
}

// Read the position of each servo
void read_arm_position() {
  Serial.print("Position of arm");
  Serial.println("");
  Serial.print("Bottom Servo: ");
  Serial.print(s1.read());
  Serial.print("    Middle Servo: ");
  Serial.print(s2.read());
  Serial.print("    Top Servo: ");
  Serial.print(s3.read());
  Serial.print("    Gripper: ");
  Serial.print(gripper.read());
  Serial.println("");
}

void read_wheel_position() {
  Serial.print("Position of wheel: ");
  Serial.println(wheel.read());
  Serial.print("\n");
}

void drive(float dist, int dir) {
      // Set the spinning direction clockwise:
    digitalWrite(dirPin, dir);

    // Spin the stepper motor 1 revolution:
    for (int i = 2; i < stepsPerRevolution; i++) {
      // These four lines result in 1 step:
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(accel - (i*3));
      digitalWrite(stepPin, LOW);
      delayMicroseconds(accel - (i*3));
    }

  for (int i = 0; i < ((dist / dist_per_rev)-1)*stepsPerRevolution; i++) {
      // These four lines result in 1 step:
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(speed);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(speed);
    }
}

void wheel_home() {
  wheel.write(90);
}

void servo_home() {
  s1.write(65);
  s2.write(5);
  s3.write(15);
  delay(1000);
}

void servo_down() {
  s2.write(25);
  delay(1000);
  s1.write(120);
  delay(1000);
  s2.write(18);
  delay(1000);
}

void pickup () {
  delay(1000);
  s3.write(33);
  delay(1000);
  gripper.write(8);
  delay(1000);
}

void loop() {
  /*-----------------------------*/// Drive to cubes
  wheel.write(32);
  delay(2000);
  drive(3.745*dist_per_rev,HIGH);
  delay(1000);
  wheel.write(90);
  servo_down();
  delay(1000);
  drive(30.5, HIGH);
  delay(1500);
  
  /*-----------------------------*/// pickup cubes
  pickup();
  delay(1500);
  servo_home();
  delay(1000);
  /*-----------------------------*/// drive back to start
  drive(30.5, LOW);
  delay(1000);
  wheel.write(34);
  drive(3.80 * dist_per_rev, LOW);
  delay(1000);
  /*-----------------------------*/// drive to pyramid
  wheel.write(92);
  delay(1000);
  drive(230, HIGH);
  delay(1000);
  /*-----------------------------*/// turn right
  wheel.write(45);
  delay(1000);
  drive(20, HIGH);
  delay(1000);
  /*----------------------------*/ // drive to right
  drive(70, HIGH);
  delay(1000);
  /*-----------------------------*/// turn left
  wheel.write(135);
  delay(1000);
  drive(20,HIGH);
  delay(1000);
  /*-----------------------------*/// drive forward
  drive(150, HIGH);
  delay(1000);
  /*-----------------------------*/// turn left
  wheel.write(135);
  delay(1000);
  drive(20,HIGH);
  delay(1000);
  /*-----------------------------*/// drive left
  wheel.write(90);
  delay(1000);
  drive(200, HIGH);
  delay(1000);
   /*-----------------------------*/// turn right
  wheel.write(45);
  delay(1000);
  drive(20, HIGH);
  delay(1000);
  /*-----------------------------*/// drive forward to goal!
  wheel.write(115);
  delay(1000);
  drive(200, HIGH);
  /*-----------------------------*/// raise arm to basket

  delay(30000);
}
