#include <AccelStepper.h>
#include <MultiStepper.h>
#define ENTER 10

//-------------------------------pin setup-------------------------------//-----------
const int dirPin[]= {2,4};  //Array of the Direction pins 
const int stepPin[] = {3,5}; // Array of the Step pins

//-------------------------------variables definition-------------------------------//-----------
char RecByte;                     //store recieved character
char motor;                       //motor flag
int bEnterMenu, bReadMovement=0;  //flags 
int movement_update=0;            //flags
const int STEPS_PER_REV = 200;    //stepper motors step per revolution
int steps;                        //steps
boolean start_motor_b = 0;        //flags
boolean stop_motor = 0;           //flags
float movement;                   //distance to travel in mm
int pitch = 2;                    //pitch of the linear guide, here: 2mm/revolution
long positions[2]={0,0};          //Array of desired stepper positions
unsigned long startMillis;        //time tracking 
unsigned long currentMillis;      //time tracking 
const unsigned long period = 10000; //the value is a number of milliseconds to wait 

//-------------------------------function prototyping-------------------------------//-----------
int get_steps(float movemment);   //function to return number of steps associated with movement
void update_position(int steps);  //update array of the stepper positions
void run_motor(int steps);        //run motors: this function actually runs the motors
void command();                   //function to get serial inputs
int ReadInt();                    //function to convert serial string input to integer number

//-------------------------------creating an instance/object-------------------------------//-----------
AccelStepper media_stepper(1, stepPin[0], dirPin[0]); // pin 3 = step, pin 2 = direction
AccelStepper air_stepper(1, stepPin[1], dirPin[1]); // pin 5 = step, pin 3 = direction
//AccelStepper Yaxis(1, 4, 7); // pin 4 = step, pin 7 = direction
//AccelStepper Zaxis(1, 5, 9); // pin 5 = step, pin 8 = direction
// Up to 10 steppers can be handled as a group by MultiStepper
MultiStepper steppers;
 
//-------------------------------setup-------------------------------//-----------
void setup(){  
    media_stepper.setMaxSpeed(400.0);
    air_stepper.setMaxSpeed(400.0);
    //stepper.setAcceleration(100.0);
    steppers.addStepper(media_stepper);
    steppers.addStepper(air_stepper);
    Serial.begin(9600);
    bEnterMenu = 1 ;
    
}

//-------------------------------main loop-------------------------------//-----------
void loop(){
  command();
  if(!bEnterMenu){
    if(bReadMovement){    
      movement_update=ReadInt();
      steps=get_steps(movement_update);
      update_position(steps);
    }
    if(movement_update){
      bEnterMenu = 1;
      bReadMovement=0;
    }
    //Serial.println(bEnterMenu);
  }
  if(start_motor_b){
    currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
    if (currentMillis - startMillis >= period)  //test whether the period has elapsed
    {
      positions[1] = positions[1]+100;
      startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
      start_motor_b=0;
      bEnterMenu = 1;
    }
  }    
  Serial.println(positions[0]);
  Serial.println(positions[1]);
  Serial.println(motor);
  if(!stop_motor) run_motor(steps);
}

//-------------------------------function definition-------------------------------//-----------
int get_steps(float movement){
  steps = movement*STEPS_PER_REV/pitch ;
  return steps;
}

void command(){
   if(bEnterMenu){
    if (Serial.available() > 0){
      // read the incoming byte:
      RecByte = Serial.read();
      switch(RecByte){
          case 'a':
              Serial.println("Please enter movement in mm for motor a :");
              motor = 'a';
              bReadMovement = 1;
              stop_motor = 0;
              break;
          case 'b':
              Serial.println("Please enter movement in mm for motor b :");
              motor = 'b';
              bReadMovement = 1;
              stop_motor = 0;
              break;              
          case 's':   //to stop
              stop_motor = 1;
              Serial.println("stop");
              break;    
          case 'g':
              startMillis = millis();  //initial start time
              positions[0] = positions[0]-500;
              start_motor_b = 1;              
              break;  
          case ENTER :
              //No work
              bEnterMenu = 0;
              break ;
          default :
              Serial.println("Invalid  key");
              break ;         
        } 
     }
  }
}

void update_position(int steps){
  if(motor=='a'){
    positions[0] = positions[0]+steps;
  }else if(motor=='b'){
    positions[1] = positions[1]+steps;
  }
}

void run_motor(int steps){ 
//  positions[0] = steps;
//  positions[1] = 2000;
  steppers.moveTo(positions);
  steppers.run(); // Blocks until all are in position
}

int ReadInt(){
  int integer_value;
  String incoming_string ="";
  if(!Serial.available()){    // something came across serial
    integer_value = 0;         // throw away previous integer_value
    incoming_string = Serial.readString();
    integer_value = incoming_string.toInt();
    //Serial.println(integer_value);
    return integer_value ;
  }else{
    return 0;
  }
}
