#include <Servo.h> 
Servo Base;  // create servo object to control a servo
Servo Shoulder;  // create servo object to control a servo 
Servo Elbow;  // create servo object to control a servo 
//Servo WristUpDown;  // create servo object to control a servo 
//Servo WristRotate;  // create servo object to control a servo 
Servo Gripper;  // create servo object to control a servo 

int value[36] = {159,170,58,120,159,175,58,120,159,175,58,160,159,146,58,160,129,146,58,160,129,166,58,160,129,166,58,120,129,146,58,120,159,146,58,120};
int a = 0;// block start address
int stepno = 1;
int buffer = 0;
int offset = 5; // initiallize for green
//int b = 0;// accumulative start address
int OutPut= 11;//naming pin11 as output
unsigned int rPulseWidth = 0;
unsigned int bPulseWidth = 0;
unsigned int gPulseWidth = 0;

 //const int inputPinA = 0; //  Pins 0 & 1 are connected to push buttons.
// const int inputPinB = 1;
//int pot_input[0];
int pot_input[2] = {0};
void setup() 
{ 
  Serial.begin(9600);
  Base.attach(13);  // attaches the servo on pin 2 to the servo object
  Shoulder.attach(10);  // attaches the servo on pin 3 to the servo object
  Elbow.attach(9);  // attaches the servo on pin 4 to the servo object
//  WristUpDown.attach(8);  // attaches the servo on pin 5 to the servo object
//  WristRotate.attach(7);  // attaches the servo on pin 6 to the servo object
  Gripper.attach(6);  // attaches the servo on pin 7 to the servo object

 // Initiallized ARM positions on power on ///  
  Base.write(161); 
  Shoulder.write(146); 
  Elbow.write(58); 
  Gripper.write(120);  
///////////////////////////////////////////

                pinMode(5, OUTPUT);//Sensor S0
                pinMode(4, OUTPUT);//Sensor S1
                pinMode(3, OUTPUT);//Sensor S2
                pinMode(2, OUTPUT);//Sensor S3
                pinMode(11, INPUT);//Sensor OUT
 
                digitalWrite(5,HIGH);//setting frequency selection to 20%
                digitalWrite(4,LOW);

                pinMode(A1, OUTPUT);//GND
                pinMode(A2, OUTPUT);//Yellow LED
                pinMode(A3, OUTPUT);//Blue LED
                pinMode(A4, OUTPUT);//Green LED
                pinMode(A5, OUTPUT);//Red LED

                digitalWrite(A1, LOW);// for GND
                digitalWrite(A2,LOW);
                digitalWrite(A3,LOW);
                digitalWrite(A4,LOW);
                digitalWrite(A5,LOW);
colour_sense();
Serial.print(offset);
} 

void loop() 
{    
  Serial.println(offset);
   //offset = buffer;
   //colour_sense();
           
 
    //pot_input[0]=analogRead(0);
    //pot_input[1]=analogRead(1);
    //pot_input[0]= map( pot_input[0],0,1023,15,-15);
    // pot_input[1]= map( pot_input[1],0,1023,15,-15);

    //value[a]=(value[a] + pot_input[0]);
    //value[a+1]=(value[a+1] + pot_input[1]);

for (int count=0;count<200;count++)
{ 
 if (stepno >= 5 && stepno <= 8)
  { 
    Base.write(value[a] + offset);     
    Shoulder.write(value[a+1]);
    Elbow.write(value[a+2]);
    Gripper.write(value[a+3]);
    delay(10);     
  }
  else{
    Base.write(value[a]);
    Shoulder.write(value[a+1]);
    Elbow.write(value[a+2]);
    Gripper.write(value[a+3]);
    delay(10);  
  }
      } 
  a=a + 4;
  stepno++;
  if (a>=36)
  {
    a=0;
    stepno = 1;
    offset = buffer;
    colour_sense();
  }                         
//colour_sense();
}

void colour_sense()
{
   digitalWrite(3,LOW);
                digitalWrite(2,LOW);//setting for RED color sensor
                rPulseWidth = pulseIn(OutPut, LOW);//read pulse width
                if (rPulseWidth > 10000)
                { rPulseWidth = 10000;
                }
                //rPulseWidth = (256-rPulseWidth);
                 rPulseWidth = map(rPulseWidth, 0,10000,255,0);
          
                delay(300);

                digitalWrite(3,LOW);
                digitalWrite(2,HIGH);// setting for BLUE color sensor
                bPulseWidth = pulseIn(OutPut, LOW);// read pulse width
                 if (bPulseWidth > 10000)
                { bPulseWidth = 10000;
                }
               
                bPulseWidth = map(bPulseWidth, 0,10000,255,0);

                delay(300);
               

                digitalWrite(3,HIGH);
                digitalWrite(2,HIGH);// setting for GREEN color sensor
                gPulseWidth = pulseIn(OutPut, LOW);// read pulse width
                 if (gPulseWidth > 10000)
                { gPulseWidth = 10000;
                }
               
                 gPulseWidth = map(gPulseWidth, 0,10000,255,0);
                delay(300);  
                
                if ((rPulseWidth > gPulseWidth) && (gPulseWidth > bPulseWidth) && ((rPulseWidth + gPulseWidth + bPulseWidth) > 600))// test for yellow
                {
                  buffer = -55;// Yellow
                  digitalWrite(A2, HIGH);
                  digitalWrite(A3,LOW);
                  digitalWrite(A4,LOW);
                  digitalWrite(A5,LOW);
             }
                
                else if ((rPulseWidth > bPulseWidth) && (bPulseWidth > gPulseWidth))// && ((rPulseWidth + gPulseWidth + bPulseWidth) > 500))// test for red
                
                 { 
                  buffer = 15;// Red
                  digitalWrite(A2,LOW);
                  digitalWrite(A3,LOW);
                  digitalWrite(A4,LOW);
                  digitalWrite(A5,HIGH);
        }
        
        else if ((bPulseWidth > rPulseWidth) && (bPulseWidth + gPulseWidth))// test for blue
        
         { 
          buffer = -35;// blue

          digitalWrite(A2, LOW);
                  digitalWrite(A3,HIGH);
                  digitalWrite(A4,LOW);
                  digitalWrite(A5,LOW);
      }
                
               else
      { buffer = 5;// green
      digitalWrite(A2, LOW);
                  digitalWrite(A3,LOW);
                  digitalWrite(A4,HIGH);
                  digitalWrite(A5,LOW);
      }
                }
