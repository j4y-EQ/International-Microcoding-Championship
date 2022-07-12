#include <IBIT.h>

  int PA0, PA1, PA2, ADC0, ADC1;
  int white=2000;
  int result=0;

  int fullspeed=255;
  int checklast=0;

  const int buttonA = 5;    // button A on microbit
  const int buttonB = 11;   // button B on microbit

  
void setup() {
  //Serial.begin(115200);
  IBIT();  // initial ibit system
    pinMode(buttonA, INPUT);  
    pinMode(buttonB, INPUT); 

  // ========================  start the seqeunce ==================
  // function(curvespeed, forwardspeed)
  buttonApress();
  delay(1000);
  
  FL2CROSS(255,255);  forward(255);delay(25);
  
  FL2RT(255,255);  forward(255);//delay(75);
  
  FL2RT(200,180);  curveright(200);//delay(75);
  
  TurnRightAngle(200);

  FL2RT(255,255);  forward(255);//delay(75);

  FC2LT(255,255);  forward(255);//delay(75);
  FL2LT(255,255);  forward(255);//delay(75);    // org speed 240
  FL2LT(255,255);  forward(255);//delay(75);

  FC2LT(255,255);  forward(255);//delay(75);
  FL2LT(255,255);  forward(255);//delay(75);    // org speed 240
  FL2LT(255,255);  forward(255);//delay(75);

  FC2LT(255,255);  forward(255);//delay(100);
  FL2LT(255,255);  forward(255);//delay(100);

  FC2LT(255,255);  forward(255);//delay(100);
  FL2LT(255,255);  forward(255);//delay(100);

 FC2RT(255,255);  forward(255);delay(15);  //????
  
FL2RT(205,200);  curveright(180); delay(50);
  
  TurnRightAngle(200);

  //FL2RT(255,255);  forward(150);delay(110);
  FL2CROSS(255,255); 
  forward(255);delay(1000);
  brakeall();
  
}

void loop() 
{
  //checkallvalues();
}


void buttonApress()
{
  while(1)
  {  if (! digitalRead(buttonA)) { break;}
     else {}
  }
}

//============ line functions ==============================================

void FC2LT(int curvespd, int forwardspd)
{
  while(analog(A1)<white)
  {    followlinestraight(curvespd, forwardspd); }
  brakeall();
}

void FL2LT(int curvespd, int forwardspd)
{
  while(analog(A1)<white)
  {    followlinestraight(curvespd,forwardspd); }
  brakeall();
}

void TurnRightAngle(int speed)
{
  while(analog(P1)<white)
  { curveright(speed); }
  brakeall();
}

void FL2RT(int curvespd, int forwardspd)
{
  while(analog(A0)<white)
  {    followlinestraight(curvespd, forwardspd); }
  brakeall();
}

void FC2RT(int curvespd, int forwardspd)
{
  while(analog(A0)<white)
  {    followlinestraight(curvespd,forwardspd); }
  brakeall();
}

void FL2CROSS(int curvespd, int forwardspd)
{
  while(analog(A0)<white || analog(A1)<white)
  {    followlinestraight(curvespd, forwardspd); }
  brakeall();
}

void followlinecurve(int speed,int forwardspeed)
{
  result=0;
  
  if (analog(P2)>white && analog(P1)<white && analog(P0)<white) { result = 1; }
  if (analog(P2)<white && analog(P1)>white && analog(P0)<white) { result = 2; }
  else if (analog(P2)>white && analog(P1)>white && analog(P0)<white) { result = 3; }
  else if (analog(P2)<white && analog(P1)>white && analog(P0)>white) { result = 6; }
  else if (analog(P2)<white && analog(P1)<white && analog(P0)>white) { result = 4; }
  else if (analog(P2)>white && analog(P1)>white && analog(P0)>white) { result = 7; }

  
  if (result == 2) {forward(forwardspeed);}
  else if (result == 3) {lineleft(speed);}
  else if (result == 1) {curveleft(speed);}
  else if (result == 6) {lineright(speed);}
  else if (result == 4) {curveright(speed);}
  else if (result == 0) {
    if (checklast == 1) { curveleft(speed);}
    else if (checklast == 4) { curveright(speed);}
  }
  checklast = result;
}


void followlinestraight(int speed,int forwardspeed)
{
  result=0;
  
  if (analog(P2)>white && analog(P1)<white && analog(P0)<white) { result = 1; }
  if (analog(P2)<white && analog(P1)>white && analog(P0)<white) { result = 2; }
  else if (analog(P2)>white && analog(P1)>white && analog(P0)<white) { result = 3; }
  else if (analog(P2)<white && analog(P1)>white && analog(P0)>white) { result = 6; }
  else if (analog(P2)<white && analog(P1)<white && analog(P0)>white) { result = 4; }
  else if (analog(P2)>white && analog(P1)>white && analog(P0)>white) { result = 7; }

  
  if (result == 2) {forward(forwardspeed);}
  else if (result == 3) {lineleft(speed);}
  else if (result == 1) {lineleft(speed);}
  else if (result == 6) {lineright(speed);}
  else if (result == 4) {lineright(speed);}
  else if (result == 0) {
    if (checklast == 1) { curveleft(speed);}
    else if (checklast == 4) { curveright(speed);}
  }
  checklast = result;
}


  // ======================================  motor functionsv ===================================
void forward(int speed)
{
  motor(1,speed);
  motor(2,speed);
}

void backward(int speed)
{
  motor(1,-speed);
  motor(2,-speed);
}

void curveright(int speed)
{
  motor(1,0);
  motor(2,speed);
}

void curveleft(int speed)
{
  motor(1,speed);
  motor(2,0);
}

void spinright(int speed)
{
  motor(1,-speed);
  motor(2,speed);
}

void spinleft(int speed)
{
  motor(1,speed);
  motor(2,-speed);
}

void lineleft(int speed)
{
  motor(1,speed);
  motor(2,speed/2);
}

void lineright(int speed)
{
  motor(1,speed/2);
  motor(2,speed);
}

void brakeall()
{
  motor(1,0);
  motor(2,0);
}
//==============================================================================================================

void checkallvalues()
{
  PA0 = analog(P0);
  PA1 = analog(P1);
  PA2 = analog(P2);
  ADC0 = analog(A0);
  ADC1 = analog(A1);
  
  Serial.print(ADC1); Serial.print("  ");
  Serial.print(PA2); Serial.print("  ");
  Serial.print(PA1); Serial.print("  ");
  Serial.print(PA0); Serial.print("  ");
  Serial.print(ADC0); Serial.println("  ");

}
