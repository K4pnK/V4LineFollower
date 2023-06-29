int  leftLimit = 189;
int  middleLimit = 133;
int  rightLimit = 201;

bool lineBlack = true;

int  rightMotorSpeed = 80;
int  leftMotorSpeed = 80;
float  slowTurningMultiplier = 0.6;
float  fastTurningMultiplier = 1.4;

const char* studentName = "test";
/////////////////////////////////////////////////////////////
int  window = 0;             // 0 = Menu    
                             // 1 = Driving
                             // 2 = Calibrating Step One
                             // 3 = Calibrating Step Two
                             // 4 = Calibrating Step Three
                             // 5 = Info
bool STOP = true;
int  buttonOne = A7;
int  buttonTwo = A6;
bool buttonOnePressed =false;
bool buttonTwoPressed = false;
int  buttonOneLimit = 1000;
int  buttonTwoLimit = 1000;
int  selection = 1;
int  menuOptions = 3;

bool leftLine = false;
bool middleLine = false;
bool rightLine = false;

int  leftIR = A0;
int  middleIR = A1;
int  rightIR = A2;
int  leftIRValue = 0;
int  rightIRValue = 0;
int  middleIRValue = 0;

int  leftBackground = 0;
int  middleBackground = 0;
int  rightBackground = 0;
int  leftLineShade = 0;
int  middleLineShade = 0;
int  rightLineShade = 0;
int  leftTempLimit = 0;
int  middleTempLimit = 0;
int  rightTempLimit = 0;
bool lineTempBlack = false;
/////////////////////////////////////////////////////////////
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Scheduler.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

#define rightMotor_P1 3
#define rightMotor_P2 8

#define leftMotor_P1 10
#define leftMotor_P2 9

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
/////////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.clearDisplay();
  Wire.begin();
  Serial.begin(9600); 
  Scheduler.startLoop(b1);
  Scheduler.startLoop(b2);
  Scheduler.startLoop(sensorRead);
  pinMode(rightMotor_P1, OUTPUT);
  pinMode(rightMotor_P2, OUTPUT);
  pinMode(leftMotor_P1, OUTPUT);
  pinMode(leftMotor_P2, OUTPUT);
  digitalWrite(rightMotor_P1, LOW);
  digitalWrite(leftMotor_P1, LOW);
}

void loop() {
  ////////////////////////////////////     Main Menu       /////////////////////////
  if (window == 0)
  { 
    display.setTextColor(WHITE);
    display.fillRect(0, 0, 128, 16, BLACK);
    display.setCursor(26, 50);
    display.print("Next");
    display.setCursor(74, 50);
    display.print("Select");
    if ((buttonOnePressed == true) && (selection < menuOptions))
      {
        buttonOnePressed = false;
        selection = (selection + 1);
      }
    else if ((buttonOnePressed == true) && (selection >= menuOptions))
      {
        buttonOnePressed = false;
        selection = 1;
        
      }
    if (selection == 1)
      {
        display.fillRect(0, 0, 34, 16, WHITE);
        display.setTextColor(BLACK);
        display.setCursor(2, 4);
        display.print("DRIVE");
      }
    else
      {
        display.drawRect(0, 0, 34, 16, WHITE);
        display.setTextColor(WHITE);
        display.setCursor(2, 4);
        display.print("DRIVE");
      }
    if (selection == 2)
      {
        display.fillRect(33, 0, 65, 16, WHITE);
        display.setTextColor(BLACK);
        display.setCursor(39, 4);
        display.print("CALIBRATE");
      }
    else
      {
        display.drawRect(33, 0, 65, 16, WHITE);
        display.setTextColor(WHITE);
        display.setCursor(39, 4);
        display.print("CALIBRATE");
      }
      if (selection == 3)
      {
        display.fillRect(97, 0, 31, 16, WHITE);
        display.setTextColor(BLACK);
        display.setCursor(100, 4);
        display.print("INFO");
      }
    else
      {
        display.drawRect(97, 0, 31, 16, WHITE);
        display.setTextColor(WHITE);
        display.setCursor(100, 4);
        display.print("INFO");
      }
    if ((buttonTwoPressed == true) && (selection == 1))   // Open Drive Window
      {
        buttonTwoPressed == false;
        display.clearDisplay();
        window = 1;
        delay (350);
      }
    else if ((buttonTwoPressed == true) && (selection == 2))   // Open Calibration Window
      {
        buttonTwoPressed == false;
        display.clearDisplay();
        window = 2;
        delay (350);
      }
    else if ((buttonTwoPressed == true) && (selection == 3))   // Open Info Window
      {
        buttonTwoPressed == false;
        display.clearDisplay();
        window = 5;
        delay (350);
      }
      display.display();
  }
    ////////////////////////////////////     Driving       /////////////////////////
  if (window == 1)
  { 
    display.fillRect(0, 0, 128, 28, BLACK);
    display.fillRect(110, 0, 21, 64, BLACK);
    display.setTextColor(WHITE);
    display.setCursor(0,0);                     // Left Sensor Stats (1st row)
    display.print("Left");                      
    display.setCursor(50,0);                    
    display.print(leftIRValue);
    display.setCursor(0,10);                    // Middle sensor stats (2nd row)
    display.print("Middle");
    display.setCursor(50,10);
    display.print(middleIRValue);
    display.setCursor(0,20);                    // Right sensor stats (3rd row)
    display.print("Right");
    display.setCursor(50,20);
    display.print(rightIRValue);
    display.setCursor(26, 51);
    display.print("STOP");
    display.setCursor(80, 51);
    display.print("STOP");
    if (leftLine == true)
      {
      display.fillRect(110, 0, 18, 21, WHITE);
      }
    else
      {
      display.drawRect(110, 0, 18, 21, WHITE);
      }
    if (middleLine == true)
      {
      display.fillRect(110, 20, 18, 22, WHITE);
      }
    else
      {
      display.drawRect(110, 20, 18, 22, WHITE);
      }
    if (rightLine == true)
      {
      display.fillRect(110, 41, 18, 21, WHITE);
      }
    else
      {
      display.drawRect(110, 41, 18, 21, WHITE);
      }
 
      if (((middleLine == true) && (leftLine == true)) && (rightLine == true))      // STOP
        {
          analogWrite(rightMotor_P2, 0);
          analogWrite(leftMotor_P2, 0);
        }
      else if ((leftLine == true)  && (rightLine == false))                         // Turn Left
        {
          analogWrite(rightMotor_P2, (rightMotorSpeed * fastTurningMultiplier));
          analogWrite(leftMotor_P2, (leftMotorSpeed * slowTurningMultiplier));
        }
      else if ((leftLine == false)  && (rightLine == true))                         // Turn Right
        {
          analogWrite(rightMotor_P2, (rightMotorSpeed * slowTurningMultiplier));
          analogWrite(leftMotor_P2, (leftMotorSpeed * fastTurningMultiplier));
        }
      else                                                                          //Straight
        {
          analogWrite(rightMotor_P2, rightMotorSpeed);
          analogWrite(leftMotor_P2, leftMotorSpeed);
        }
      if (buttonOnePressed == true)   // Go Back to Menu
      {
        buttonOnePressed = false;
        display.clearDisplay();
        window = 0;
        delay (10);
      }
      if (buttonTwoPressed == true)   // Go Back to Menu
      {
        buttonTwoPressed = false;
        display.clearDisplay();
        window = 0;
        delay (10);
      }
     display.display();
  }
    ////////////////////////////////////     Calibrate Background       ///////////////////////// 
  if (window == 2)
  {
    display.fillRect(0, 0, 128, 28, BLACK);
    display.setTextColor(WHITE);
    display.setCursor(2, 2);
    display.print("Place over background");
    
    display.setCursor(2, 15);
    display.print("L:");
    display.print(leftIRValue);
    
    display.setCursor(50, 15);
    display.print("M:");
    display.print(middleIRValue);
    
    display.setCursor(98, 15);
    display.print("R:");
    display.print(rightIRValue);
    
    display.setCursor(26, 51);
    display.print("BACK");
    
    display.setCursor(72, 51);
    display.print("CAPTURE");
    display.display();
    
    if (buttonOnePressed == true)   // Go Back to Menu
      {
        buttonOnePressed = false;
        display.clearDisplay();
        window = 0;
        delay (10);
      }
    else if (buttonTwoPressed == true)   // Go Back to Menu
      {
        buttonTwoPressed == false;
        delay (500);
        leftBackground = leftIRValue;
        middleBackground = middleIRValue;
        rightBackground = rightIRValue;
        display.clearDisplay();
        window = 3;
        delay (10);
      }
  }
    ////////////////////////////////////     Calibrate Line       ///////////////////////// 
  if (window == 3)
  {
    display.fillRect(0, 0, 128, 28, BLACK);
    display.setTextColor(WHITE);
    display.setCursor(15, 2);
    display.print("Place over Line");
    
    display.setCursor(2, 15);
    display.print("L:");
    display.print(leftIRValue);
    
    display.setCursor(50, 15);
    display.print("M:");
    display.print(middleIRValue);
    
    display.setCursor(98, 15);
    display.print("R:");
    display.print(rightIRValue);
    
    display.setCursor(26, 51);
    display.print("BACK");
    
    display.setCursor(72, 51);
    display.print("CAPTURE");
    display.display();
    
    if (buttonOnePressed == true)   // Go Back to Menu
      {
        buttonOnePressed = false;
        display.clearDisplay();
        window = 2;
        delay (10);
      }
    else if (buttonTwoPressed == true)   // Go Back to Menu
      {
        buttonTwoPressed == false;
        delay (500);
        leftLineShade = leftIRValue;
        middleLineShade = middleIRValue;
        rightLineShade = rightIRValue;

        leftTempLimit = (leftBackground + leftLineShade);
        middleTempLimit = (middleBackground + middleLineShade);
        rightTempLimit = (rightBackground + rightLineShade);

        leftTempLimit = (leftTempLimit/2);
        middleTempLimit = (middleTempLimit/2);
        rightTempLimit = (rightTempLimit/2);

        if (middleLineShade > middleBackground)
          lineTempBlack = false;
        else
          lineTempBlack = true;
          
        display.clearDisplay();
        window = 4;
      }
  }
    ////////////////////////////////////     Calibrate Confirm       ///////////////////////// 
  if (window == 4)
  {
    display.fillRect(0, 0, 128, 28, BLACK);
    display.setTextColor(WHITE);
    display.setCursor(9, 2);
    display.print("Are these correct?");
    
    display.setCursor(2, 15);
    display.print("L:");
    display.print(leftTempLimit);
    
    display.setCursor(50, 15);
    display.print("M:");
    display.print(middleTempLimit);
    
    display.setCursor(98, 15);
    display.print("R:");
    display.print(rightTempLimit);

    display.setCursor(54, 29);
    display.print("Line");
    
    display.setCursor(51, 40);
    if (lineTempBlack == true)
      display.print("BLACK");
    else
      display.print("WHITE");
          
    display.setCursor(19, 51);
    display.print("RESTART");
    
    display.setCursor(78, 51);
    display.print("Apply");
    display.display();
    if (buttonOnePressed == true)   // Go Back to Menu
      {
        buttonOnePressed = false;
        display.clearDisplay();
        window = 2;
      }
    else if (buttonTwoPressed == true)   // Go Back to Menu
      {
        buttonTwoPressed == false;
        leftLimit = leftTempLimit;
        middleLimit = middleTempLimit;
        rightLimit = rightTempLimit;
        lineBlack = lineTempBlack;
        display.clearDisplay();
        window = 0;
        delay (250);
      }
  }
    ////////////////////////////////////     Info       ///////////////////////// 
  if (window == 5)
  {
    display.setTextColor(WHITE);
    display.setCursor(2, 2);
    display.print("Name:");
    display.print(studentName);
    
    display.setCursor(2, 15);
    display.print("L:");
    display.print(leftLimit);
    
    display.setCursor(50, 15);
    display.print("M:");
    display.print(middleLimit);
    
    display.setCursor(98, 15);
    display.print("R:");
    display.print(rightLimit);

    display.setCursor(54, 29);
    display.print("Line");
    
    display.setCursor(51, 40);
    if (lineBlack == true)
      display.print("BLACK");
    else
      display.print("WHITE");

    display.setCursor(26, 51);
    display.print("MENU");
    if (buttonOnePressed == true)   // Go Back to Menu
      {
        buttonOnePressed = false;
        display.clearDisplay();
        window = 0;
         delay (100);
      }
    display.display();
  }
  
}


void b1()
{
  
  if (analogRead(buttonOne) > buttonOneLimit)
    {
      display.fillCircle(37, 38, 9, WHITE);
      delay(75);
      buttonOnePressed = true;
      delay(5);
      buttonOnePressed = false;
      delay(500);
      display.fillCircle(37, 38, 9, BLACK);
    }
  else 
    {
      buttonOnePressed = false; 
      display.drawCircle(37, 38, 9, WHITE);
    }
  yield();
}
void b2()
{
  
  if (analogRead(buttonTwo) > buttonTwoLimit)
    {
      display.fillCircle(91, 38, 9, WHITE);
      delay(75);
      buttonTwoPressed = true;
      delay(5);
      buttonTwoPressed = false;      
      delay (500);
      display.fillCircle(91, 38, 9, BLACK);
    }
  else 
    {
      buttonTwoPressed = false;
      display.drawCircle(91, 38, 9, WHITE);
    }   
    yield();
}

void sensorRead()
{
    leftIRValue = analogRead(leftIR);
    middleIRValue = analogRead(middleIR);
    rightIRValue = analogRead(rightIR);
    
  if   (((leftIRValue < leftLimit) && (lineBlack == true)) || ((leftIRValue > leftLimit) && (lineBlack == (false))))
    {
      leftLine = true;
    }
  else
    {
      leftLine = false;
    }
  
  if   (((middleIRValue < middleLimit) && (lineBlack == true)) || ((middleIRValue > middleLimit) && (lineBlack == (false))))
    {
      middleLine = true;
    }
  else
    {
      middleLine = false;
    }

  if   (((rightIRValue < rightLimit) && (lineBlack == true)) || ((rightIRValue > rightLimit) && (lineBlack == (false))))
    {
      rightLine = true;
    }
  else
    {
      rightLine = false;
    }

  //exit(0);
  yield();
}