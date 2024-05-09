#define SERVO_SPEED 5// servo speed in ms
#include <Servo.h>
#include <Arduino.h>

//front left and back right curl when all are 0
int front_left_pos = 0;   // desired angle for front left leg
int front_right_pos = 180;  // desired angle for front right leg
int rear_left_pos = 180;    // desired angle for rear left leg
int rear_right_pos = 0;   // desired angle for rear right leg

// create servo objects
Servo front_right; // front right leg
Servo front_left;  // front left leg
Servo rear_right;  // rear right leg
Servo rear_left;   // rear left leg

// define servo pins
#define front_left_pin 9
#define front_right_pin 7
#define rear_left_pin 11
#define rear_right_pin 5

//this gets used in the gait functions
int gait_step = 1;

bool servoPosCheck()
{
    if (front_right_pos != front_right.read()) return false;
    if (front_left_pos != front_left.read()) return false;
    if (rear_right_pos != rear_right.read()) return false;
    if (rear_left_pos != rear_left.read()) return false;
    return true;
}

// gait_step desired servo positions, right_front and left_rear are inverted, so 0, 180, 180, 0 is position 0
void setServoPosOld(int left_front, int right_front, int left_rear, int right_rear)
{
  front_left_pos = left_front;
  front_right_pos = right_front;
  rear_left_pos = left_rear;
  rear_right_pos = right_rear;
}

//adjusted version, use this for clearer code ?
void setServoPos(int left_front, int right_front, int left_rear, int right_rear)
{
  front_left_pos = left_front;
  front_right_pos = 180 - right_front;
  rear_left_pos = 180 - left_rear;
  rear_right_pos = right_rear;
}

void setup()
{
  // initialize serial communication
  Serial.begin(9600);
  
  // initialize servos
  front_right.attach(front_right_pin); // front right leg
  front_left.attach(front_left_pin); // front left leg
  rear_right.attach(rear_right_pin); // rear right leg
  rear_left.attach(rear_left_pin); // rear left leg

}

void crawlingGait() {
  // if all servos are in desired position, update desired position
    if (gait_step == 1) {
        setServoPos(120, 0, 0, 120);
        gait_step = 2;
        //Gait 1 crosslegged
    } else if (gait_step == 2) {
        setServoPos(0, 120, 120, 0);
        gait_step = 1;
    }
}

void undulatingGait() {
    if (gait_step == 1) {
      setServoPos(0, 0, 0, 0);
      gait_step = 2;
    } else if (gait_step==2) {
      setServoPos(80, 80, 0, 0);
      gait_step = 3;
    } else if (gait_step == 3) {
      setServoPos(80, 80, 80, 80);
      gait_step = 4;
    } else if (gait_step == 4) {
      setServoPos(0, 0, 80, 80);
      gait_step = 1;
    }
}

void pusherGait(){
  if (gait_step == 1) {
    setServoPos(120, 120, 0, 0);
    gait_step = 2;
  } else if (gait_step == 2) {
    setServoPos(0, 0, 120, 120);
    gait_step = 3;
  } else if (gait_step == 3) {
    setServoPos(0, 0, 0, 0);
    gait_step = 1;
  }

}

void simulLegGait() {
  if (gait_step == 1) {
        setServoPos(0, 0, 0, 0);
        gait_step = 2;
    } else if (gait_step == 2) {
        setServoPos(80, 80, 80, 80);
        gait_step = 1;
  }
}

void rippleGait() {
    if (gait_step == 1) {
    setServoPos(120, 0, 0, 120);
    gait_step = 2;
  } else if (gait_step == 2) {
    setServoPos(0,120,120,0);
    gait_step = 3;
  } else if (gait_step == 3) {
    setServoPos(0,0,120,120);
    gait_step = 4;
  } else if (gait_step == 4) {
    setServoPos(120,120,0,0);
    gait_step = 1;
  }
}

void stefanGait(){
  if (gait_step == 1) {
    //Serial.println("Step 1");
    setServoPos(120, 120, 0, 0);
    gait_step = 2;
  } else if (gait_step == 2) {
    //Serial.println("Step 2");
    setServoPos(0,0,120,120);
    gait_step = 3;
  } else if (gait_step == 3) {
    //Serial.println("Step 3");
    setServoPos(120,0,120,0);
    gait_step = 4;
  } else if (gait_step == 4) {
    //Serial.println("Step 4");
    setServoPos(0,120,0,0);
    gait_step = 1;
  }
}

void crawlingGait2() {
  // if all servos are in desired position, update desired position
    if (gait_step == 1) {
        setServoPos(120, 0, 120, 0);
        gait_step = 2;
        //Gait 1 crosslegged
    } else if (gait_step == 2) {
        setServoPos(0, 120, 0, 120);
        gait_step = 1;
    }
}

void turningGait(String direction) {
  if (direction == "left") {
    if (gait_step == 1) {
      setServoPos(0,120,0,0);
      gait_step = 2;
    } else if (gait_step == 2) {
      setServoPos(0,120,0,120);
      gait_step = 3;
    } else if (gait_step == 3) {
      setServoPos(0,0,0,120);
      gait_step = 4;
    } else if (gait_step == 4) {
      setServoPos(0,0,0,0);
      gait_step = 1;
    }
  } else {
    if (gait_step == 1) {
      setServoPos(120,0,0,0);
      gait_step = 2;
    } else if (gait_step == 2) {
      setServoPos(120,0,120,0);
      gait_step = 3;
    } else if (gait_step == 3) {
      setServoPos(0,0,120,0);
      gait_step = 4;
    } else if (gait_step == 4) {
      setServoPos(0,0,0,0);
      gait_step = 1;
    }
  }
}

unsigned long turning_time = millis();
static unsigned long turn_time = 10000;
void turning() {
  if((millis()-turning_time) < turn_time/2) {
    Serial.println("Turning left");
    turningGait("right");
  } 
  if (millis() - turning_time >= turn_time/2) {
    Serial.println("Turning right");
    turningGait("left");
  }
  if((millis()-turning_time) >= turn_time*2) {
    turning_time = millis();
  }
}
//declare and innitialise servo_time
static unsigned long servo_time = millis();
void loop()
{
  // check if all servos are in desired position and if they are start the next step in the gait
  if (servoPosCheck()) {
    //crawlingGait();
    //undulatingGait(); 
    //pusherGait();
    //simulLegGait();
    //rippleGait();


    //stefanGait(); 
    //crawlingGait2();
    turningGait("right");
    //turning();
    Serial.println("Step " + String(gait_step));
  }
  
  // check time since last servo position update 
  if ((millis()-servo_time) >= SERVO_SPEED) {
    servo_time = millis(); // save time reference for next position update
    
    // update front_right position
    // if desired position is different from current position move one step left or right
    if (front_right_pos > front_right.read()) front_right.write(front_right.read() + 1);
    else if (front_right_pos < front_right.read()) front_right.write(front_right.read() - 1);
    // update front_left position
    if (front_left_pos > front_left.read()) front_left.write(front_left.read() + 1);
    else if (front_left_pos < front_left.read()) front_left.write(front_left.read() - 1);
    // update rear_right position
    if (rear_right_pos > rear_right.read()) rear_right.write(rear_right.read() + 1);
    else if (rear_right_pos < rear_right.read()) rear_right.write(rear_right.read() - 1);
    // update rear_left position
    if (rear_left_pos > rear_left.read()) rear_left.write(rear_left.read() + 1);
    else if (rear_left_pos < rear_left.read()) rear_left.write(rear_left.read() - 1);
    
  }

  //delay(1000);
}