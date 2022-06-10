#include <FastPID.h>
//float pid_P = 0.02, pid_I = 0.11, pid_D = 0; //todo define here

FastPID myPID(pid_P, pid_I, pid_D, 10, 10, false); //0.11 lower = better ~~~~~~~~!

void pidSetup(){
//  motor.Enable();
}

uint16_t old_output = 0;
uint16_t output = 0;

void pid(){ //run a blind pid to get new output
  if(mtr.getStatus() == 0){return;}
  
  unsigned int setpoint = target_rpm; 
  unsigned long feedback = RPM;

  output = myPID.step(setpoint, feedback);

  
  
  if(output - old_output > 1 || output - old_output < -1){output += old_output; output = output/2;}
  if(output - old_output > 2 || output - old_output < -2){output += old_output; output += old_output; output = output/3;}

  if(output < 25){output = 25;}
  mtr.control(0, output);
  
  old_output = output;
  Serial.print(" sp: "); 
  Serial.print(setpoint); 
  Serial.print(" fb: "); 
  Serial.print(feedback);
  Serial.print(" out: ");
  Serial.println(output);
  
}
