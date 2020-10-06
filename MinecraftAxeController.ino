//poorly written code by raccoon facts
//feel free to steal, but keep it spaghetti 
//plz sub to my youtube channel 
//http://www.youtube.com/raccoonfacts
//k
#include <Mouse.h> 
#include <Keyboard.h>                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
const int xAxis = A1;
const int yAxis = A0;
const int xAxis2 = A2;
const int yAxis2 = A3;
const int joystickButton2 = 9;
const int joystickButton1 = 8;
const int clickSwitch = 7;
const int mouseroll = 10;
const int eButton= 11;

int range= 12;
int responseWait = 5;
int threshold = range / 4;
int center = range / 2;
const unsigned long scrollDelay = 6;
const unsigned long keyboardDelay = 5;
const unsigned long clickDelay = 1;
unsigned long oldTime = 0;
unsigned long oldClickTime = 0;
int led = 12;
int led1 = 13;
int currStateYup;
int prevStateYup;
int currStateYdown;
int prevStateYdown;
int currStateXleft;
int prevStateXleft;
int currStateXright;
int prevStateXright;
                                                                                                                                                                                                    

void setup()
{
  Serial.begin(9600);
  pinMode(joystickButton1, INPUT_PULLUP); 
  pinMode(joystickButton2, INPUT_PULLUP); 
  pinMode(clickSwitch, INPUT_PULLUP);
  pinMode(mouseroll, INPUT);
  pinMode(eButton, INPUT );
  pinMode(led1, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led, LOW);
  Mouse.begin(); 
  Keyboard.begin();

}
void loop()
{
  thumbstick();
  joystick1();
  joystick2();
  wasd();
  leftClickSwitch(); 
  mouseScroll();
  eButt();
}

void leftClickSwitch()
{
  int leftClickStatus = digitalRead(clickSwitch);
  unsigned long clickTime = millis();
  if (leftClickStatus == HIGH)
  {
    
    digitalWrite(led, HIGH);
    Mouse.release();
    
  }
  else 
  {
   
    digitalWrite(led,LOW);
    Mouse.press();

  }
}

void thumbstick() 
{
  unsigned long timeNow = millis();
  
  int xRead = readXAxis(A1);
  int yRead = readYAxis(A0);
  if (timeNow - oldTime >= keyboardDelay)
  {
  Mouse.move(xRead, yRead, 0);
  oldTime = timeNow;
  }

}
void wasd()
{
int sensorValueY = analogRead(yAxis2);
  int sensorValueX = analogRead(xAxis2);

  { // Y up )
    currStateYup = sensorValueY > 404;
    if (currStateYup != prevStateYup)
    {
      if (currStateYup == (sensorValueY < 50))
      {
        Keyboard.press('s');
      }
      else
      {
        Keyboard.release('s');
      }
    }
    prevStateYup = currStateYup;
  }

  { //Y down 
    currStateYdown = sensorValueY < 594;
    if (currStateYdown != prevStateYdown)
    {
      if (currStateYdown == (sensorValueY > 973))
      {
        Keyboard.press('w');
      }
      else
      {
        Keyboard.release('w');
      }
    }
    prevStateYdown = currStateYdown;
  }

  { //X left
    currStateXleft = sensorValueX > 408;
    if (currStateXleft != prevStateXleft)
    {
      if (currStateXleft == (sensorValueX < 50))
      {
        Keyboard.press('d');
      }
      else
      {
        Keyboard.release('d');
      }
    }
    prevStateXleft = currStateXleft;
  }

  { //X right
    currStateXright = sensorValueX < 598;
    if (currStateXright != prevStateXright)
    {
      if (currStateXright == (sensorValueX > 973))
      {
        Keyboard.press('a');
      }
      else
      {
        Keyboard.release('a');
      }
    }
    prevStateXright = currStateXright;
  }

}
void eButt()
{
  int ekey = digitalRead(eButton);
  if (ekey == HIGH) 
  {
    digitalWrite(led1, HIGH);
    Keyboard.press('e'); 
   
  }
  else 
  {
  digitalWrite(led1, LOW);
  Keyboard.release('e');
  
  }
}
void joystick2()
{
  int rightClick = digitalRead(joystickButton2);
  if (rightClick == HIGH) 
  {
    digitalWrite(led, LOW);
    Keyboard.release(' '); 
   
  }
  else 
  {
  digitalWrite(led, HIGH);
  Keyboard.press(' ');
  
  }
}
void joystick1() //Switched joystick clicks cant be fucked to change name 
{
 int spaceBar = digitalRead(joystickButton1);
  if (spaceBar == HIGH)
{
   digitalWrite(led, LOW);
   Mouse.release(MOUSE_RIGHT);

}
else
{
  digitalWrite(led, HIGH);
  Mouse.press(MOUSE_RIGHT);
}
 
}
void mouseScroll() 
{
  int scrollyboi = digitalRead(mouseroll);
  unsigned long timeNow = millis();
  if (scrollyboi == HIGH) 
  {
    digitalWrite(led1, HIGH);
    if (timeNow - oldTime >= scrollDelay)
  {
  Mouse.move(0,0,-1);
  oldTime = timeNow;
  }
    
  } 
  else
  digitalWrite(led1, LOW);
  
}

int readXAxis(int thisAxis) {
  // reads the initial analog 
  int reading = analogRead(thisAxis);

 //Change range location to invert this mother fucker
  reading = map(reading, 0, 1023, range, 0);

 
  int distance = reading - center;

  if (abs(distance) < threshold) {
    distance = 0;
  }

  return distance;
  
}

int readYAxis(int thisAxis) {
  
  int reading = analogRead(thisAxis);
  //change range position to 4th if inverting
  
  reading = map(reading, 0, 1023, 0, range);
  
  int distance = reading - center;
  
  if (abs(distance) < threshold) {
    distance = 0;
  }

  return distance;
  
}
