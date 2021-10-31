// Originally written by Dr. Sumith Yesudasan
// Other contributors: Ms. Emily Westerman

#include <LobotServoController.h>

LobotServoController myse(Serial);

#define GET_LOW_BYTE(A) (uint8_t)((A))
#define GET_HIGH_BYTE(A) (uint8_t)((A) >> 8)
#define FRAME_HEADER 0x55
#define CMD_SERVO_MOVE 0x03
#define CMD_MULT_SERVO_POS_READ 0x15

const int GRIP = 10;
const int NECK = 11;
const int THIRD = 12;
const int FORTH = 13;
const int FIFTH = 14;
const int BOTTOM = 15;

//servo min and max

const int GRIP_OPEN = 1860;
const int GRIP_CLOSE = 1400;

const int NECK_LEFT = 500;
const int NECK_RITE = 2500;

const int THIRD_LEFT = 580;
const int THIRD_RITE = 2420;

const int FORTH_LEFT = 560;
const int FORTH_RITE = 2460;

const int FIFTH_LEFT = 720;
const int FIFTH_RITE = 2500;

const int BOTTOM_LEFT = 500;
const int BOTTOM_RITE = 2500;

//------equilibrium positions
//grip 1860 to 1400 (1860 open),  neck 500 to 2500, third 580 to 2420, forth 560 to 2460, fifth 720 to 2500, bottom 500 to 2500

int FIFTH_MID = 1500;
const int BOT_MID = (BOTTOM_LEFT + BOTTOM_RITE) / 2;

int MAX_ITER = 2;

int iteration = 0;
int exec_dely = 1000;
int norm_dely = 1000;

uint8_t send_buf[15];
uint8_t rece_buf[25];
int prev_val = 30000;
int cur_val;
int lengt;
uint8_t dummy_val;
int servo_pos[7]; // 1 to 6

//----------------------------------------------------------------------

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  myse.moveServo(BOTTOM, BOT_MID, exec_dely);
  delay(norm_dely);
  myse.moveServo(BOTTOM, BOT_MID - 200, exec_dely);
  delay(norm_dely);
  myse.moveServo(BOTTOM, BOT_MID + 200, exec_dely);
  delay(norm_dely);
  
  stop_servos();
}
//----------------------------------------------------------------------
void loop() {

  if (iteration < MAX_ITER)  {
    
    pick_grasp();    
    change_pos();

    drop_object();
    stop_servos();
  }
  else  {
   
    stop_servos();
    
  }
  
  iteration = iteration + 1;
  delay(500);
  Serial.flush();
}

//----------------------------------------------------------------------

void pick_grasp() {

  myse.moveServo(FIFTH, 2020 , exec_dely);
  delay(norm_dely);
  myse.moveServo(FORTH, 600, exec_dely);
  delay(norm_dely);
  myse.moveServo(THIRD, 1600, exec_dely);
  delay(norm_dely);

  myse.moveServo(GRIP,  GRIP_OPEN, exec_dely);
  delay(norm_dely);

  myse.moveServo(GRIP, 1300, exec_dely);
  delay(norm_dely);
  
  myse.moveServo(NECK, (NECK_LEFT + NECK_RITE) / 2, exec_dely);
  delay(norm_dely);
  myse.moveServo(THIRD, (THIRD_LEFT + THIRD_RITE ) / 2, exec_dely);
  delay(norm_dely);
  myse.moveServo(FORTH, (FORTH_LEFT + FORTH_RITE) / 2, exec_dely);
  delay(norm_dely);
  myse.moveServo(FIFTH, FIFTH_MID, exec_dely);
  delay(norm_dely);
  myse.moveServo(BOTTOM, (BOTTOM_LEFT + BOTTOM_RITE) / 2, exec_dely);
  delay(norm_dely);

}

//----------------------------------------------------------------------

void change_pos(){
  
  myse.moveServo(BOTTOM, 1000, exec_dely);
  delay(norm_dely);
  myse.moveServo(THIRD, 700, exec_dely);
  delay(norm_dely);
}

//----------------------------------------------------------------------

void drop_object(){
  
  myse.moveServo(GRIP,  GRIP_OPEN, exec_dely);
  delay(norm_dely);
  
}

//----------------------------------------------------------------------

void move_grip() {
  myse.moveServo(GRIP, GRIP_CLOSE, exec_dely);
  delay(norm_dely);
  myse.moveServo(GRIP, GRIP_OPEN, exec_dely);
  delay(norm_dely);
}

//----------------------------------------------------------------------

void rotate_neck() {
  myse.moveServo(NECK, NECK_LEFT, exec_dely);
  delay(norm_dely);
  myse.moveServo(NECK, NECK_RITE, exec_dely);
  delay(norm_dely);
}

//----------------------------------------------------------------------

void move_third() 
{
  myse.moveServo(THIRD, THIRD_LEFT, exec_dely);
  delay(norm_dely);
  myse.moveServo(THIRD, THIRD_RITE, exec_dely);
  delay(norm_dely);
}

//----------------------------------------------------------------------

void move_forth() 
{
  myse.moveServo(FORTH, FORTH_LEFT, exec_dely);
  delay(norm_dely);
  myse.moveServo(FORTH, FORTH_RITE, exec_dely);
  delay(norm_dely);
}

//----------------------------------------------------------------------

void move_fifth() 
{
  myse.moveServo(FIFTH, FIFTH_LEFT, exec_dely);
  delay(norm_dely);
  myse.moveServo(FIFTH, FIFTH_RITE, exec_dely);
  delay(norm_dely);
}

//----------------------------------------------------------------------

void rotate_base() 
{
  myse.moveServo(BOTTOM, BOTTOM_LEFT, exec_dely);
  delay(norm_dely);
  myse.moveServo(BOTTOM, BOTTOM_RITE, exec_dely);
  delay(norm_dely);
}

//----------------------------------------------------------------------

void stop_servos() 
{
  myse.moveServo(GRIP, (GRIP_CLOSE + GRIP_OPEN) / 2, exec_dely);
  delay(norm_dely);
  myse.moveServo(NECK, (NECK_LEFT + NECK_RITE) / 2, exec_dely);
  delay(norm_dely);
  myse.moveServo(THIRD, (THIRD_LEFT + THIRD_RITE ) / 2, exec_dely);
  delay(norm_dely);
  myse.moveServo(FORTH, (FORTH_LEFT + FORTH_RITE) / 2, exec_dely);
  delay(norm_dely);
  myse.moveServo(FIFTH, FIFTH_MID, exec_dely);
  delay(norm_dely); // This guy is an exception
  myse.moveServo(BOTTOM, (BOTTOM_LEFT + BOTTOM_RITE) / 2, exec_dely);
  delay(norm_dely);
}

//----------------------------------------------------------------------
