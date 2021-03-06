/*
 *   AUTHOR:  Samuel da Costa Araujo Nunes
 *   SINCE: April 2020
 *   VERSION: v0.1
*/

#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Keyboard.h>
#define MPU6050_ADDR

MPU6050 mpu6050(Wire);

//DECLARATION OF VARIABLES  
float angleX;//Variable that keeps the rotation angle on the X axis
float angleY;//Variable that keeps the rotation angle on the Y axis
float angleZ;//Variable that keeps the rotation angle on the Z axis
char orientation = 'l';//Control variable over the current monitor position

//DECLARATION OF KEYS FOR SHORTCUT
char ctrl = KEY_LEFT_CTRL;
char alt = KEY_LEFT_ALT;
char up = KEY_UP_ARROW;
char left = KEY_LEFT_ARROW;
char down = KEY_DOWN_ARROW;
char right = KEY_RIGHT_ARROW;

void setup() {
  //Initializes objects
  Wire.begin();
  mpu6050.begin();
  Keyboard.begin();
  mpu6050.calcGyroOffsets(false); 
}

void loop() {
  //Control variables over local angles
  float x = 0;
  float y = 0;
  float z = 0;
  int i;
  
  //Receives the current angle values, and increases the variable control locations by 20x
  for (i = 1; i < 21; ++i){
    mpu6050.update();
    x += mpu6050.getAngleX();
    y += mpu6050.getAngleY();
    z += mpu6050.getAngleZ();
  }

  //Performs the averages of the angles, to achieve a more precise result.
  angleX = x / 20;
  angleY = y / 20;
  angleZ = z / 20;

  //Checks whether it has rotated on the X axis
  if (angleX >= 37  && orientation != 'u'){//Landscape
    setOrientation(up);
    orientation = 'u';
  } else if (angleX <= -37 && orientation != 'd'){//Inverted Landscape
    setOrientation(down);
    orientation = 'd';
  }

  //Checks whether it has rotated on the Y axis
  if (angleY >= 37 && orientation != 'r'){//Portrait
    setOrientation(right);
    orientation = 'r';
  } else if (angleY <= -37 && orientation != 'l'){//Inverted Portrait
    setOrientation(left);
    orientation = 'l';
  }
  
}

//Shortcut function to rotate the orientation of the monitor
void setOrientation(char pos){
    Keyboard.press(ctrl);
    Keyboard.press(alt);
    Keyboard.press(pos);
    delay(50);
    Keyboard.releaseAll();
}
