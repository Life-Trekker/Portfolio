

/*
For the AvenueE Transportation Project, myself and two other UC Davis students
were asked to design a system to add to some form of transportation
using the arduino starter kit.  We were given 4 days to brainstorm, research an idea and craft a prototype.

My group created a Drowsy Drifting Detection System.
It's an alarm which will go off whenever the car turns too far in a direction
where the turn signal isn't signaling.  This will help wake tired drivers and get their attention back on the road.

I was responsible for programming the system, and I also assisted with the circuitry.
*/

//include the servo library
#include <Servo.h>

//define constants for joy stick controls
const int STICK_PIN = 2;
const int X_PIN = A1;
const int Y_PIN = A0;

//define constants for right and left lights
const int RIGHT_LIGHT = 9;
const int LEFT_LIGHT = 8;

//define constants for right and left buttons
const int RIGHT_BUTTON = 12;
const int LEFT_BUTTON = 13;

//define constant for buzzer
const int BUZZER = 11;

//define constant for servo
const int SERVO_PIN = 6;

//define servo
Servo myservo;

//define int for the position of the servo
int pos = 0;

//define constants for the intervals of time to trigger certain events after
#define TURN_INTERVAL 15
#define BLINK_INTERVAL 1000
#define CHECK_INTERVAL 10

//create variables to track the last executed times for all intervals
unsigned long lastExecutedMillis1 = 0;
unsigned long lastExecutedMillis2 = 0;
unsigned long lastExecutedMillis3 = 0;
unsigned long lastExecutedMillis4 = 0;

//create ints to determine whether each light has been toggled on or off
int toggleValueRight = -1;
int toggleValueLeft = -1;

//create ints to track the value and previous value of the right button
int rightButtonVal = 0;
int rightButtonOldVal = 0;

//create ints to track the value and previous value of the left button
int leftButtonVal = 0;
int leftButtonOldVal = 0;

//create long to track the current number of milliseconds since the program began
unsigned long currentMillis = 0;

void setup() {

  //set the pin mode of the control pins going to the lights and buzzer to output
  pinMode(RIGHT_LIGHT, OUTPUT);
  pinMode(LEFT_LIGHT, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  //set the pin mode of the control pins going to the buttons to input
  pinMode(RIGHT_BUTTON, INPUT);
  pinMode(LEFT_BUTTON, INPUT);

  //attach the servo to the servo control pin
  myservo.attach(SERVO_PIN);
}

void loop() {

  //set the currentMillis to the number of milliseconds since the program began
  currentMillis = millis();

  //excute this statement everytime the Turn Interval time has passed
  if (currentMillis - lastExecutedMillis1 >= TURN_INTERVAL) {
    //save the last executed time
    lastExecutedMillis1 = currentMillis;

    //if the stick isn't in the neutral position,
    if (analogRead(Y_PIN) != 512 || analogRead(X_PIN) != 512) {
      //adjust the servo position variable based on the Y position of the stick
      pos = map(analogRead(Y_PIN), 0, 512, 20, 110);

      //move the servo to that new position
      myservo.write(pos);
    }
  }
  
  //set the right button value variable to the value from the right button
  rightButtonVal = digitalRead(RIGHT_BUTTON);

  //set the left button value variable to the value from the left button
  leftButtonVal = digitalRead(LEFT_BUTTON);

  //if the right button is on and it was previously off
  if (rightButtonVal == HIGH && rightButtonOldVal == LOW) {
    //toggle the right value to off if it was on or to on if it was off
    toggleValueRight *= -1;
  }

  //if the left button is on and it was previously off
  if (leftButtonVal == HIGH && leftButtonOldVal == LOW) {
    //toggle the right value to off if it was on or to on if it was off
    toggleValueLeft *= -1;
  }

  //set the previous button values to the current button values
  rightButtonOldVal = rightButtonVal;
  leftButtonOldVal = leftButtonOldVal;

  //excute this statement everytime the Blink Interval time has passed
  if (currentMillis - lastExecutedMillis2 >= BLINK_INTERVAL) {
    //save the last executed time
    lastExecutedMillis2 = currentMillis;

    //if the right button is toggled on,
    if(toggleValueRight == 1)
    {
      //turn on the right light
      digitalWrite(RIGHT_LIGHT, HIGH);
    }


    //if the left button is toggled on,
    if(toggleValueLeft == 1)
    {
      //turn on the left light
      digitalWrite(LEFT_LIGHT, HIGH);
    }


  }

  //excute this statement everytime the Blink Interval time has passed
  if (currentMillis - lastExecutedMillis3 >= BLINK_INTERVAL * 2) {
    //save the last executed time
    lastExecutedMillis3 = currentMillis;

    //turn both lights off
    //this will cause the lights to flash when toggled on
    //and to remain off when toggled off
    digitalWrite(RIGHT_LIGHT, LOW);
    digitalWrite(LEFT_LIGHT, LOW);

  }

// 
  //excute this statement everytime the Check Interval time has passed
  if (currentMillis - lastExecutedMillis4 >= CHECK_INTERVAL) {
    //save the last executed time
    lastExecutedMillis4 = currentMillis;

    //if the right light is on but the servo is turned left
    //or if the left light is on but the servo is turned right
    //or if both lights are off but the servo is turned in any direction
    if ( (pos > 150 && toggleValueRight == 1) || (pos < 70 && toggleValueLeft == 1) || (toggleValueRight == -1 && toggleValueLeft == -1 && (pos > 150 || pos < 70)) )
    {
      //sound the buzzer
      tone(BUZZER, 1000);
    }
    else
    {
      //otherwise, turn off the buzzer
     noTone(BUZZER);
    }


  }
  
}