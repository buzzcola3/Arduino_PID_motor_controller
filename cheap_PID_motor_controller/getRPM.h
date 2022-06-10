#define steps_per_rotation 5
void pid();


int encoderStep = 0;

void count(){
  encoderStep++;
}

rpmSetup(){
  attachInterrupt(digitalPinToInterrupt(2), count, RISING);
}


unsigned long prev_time = 0;
float nextRPM = 0;
getRPM(){

  float l = 1000000;
  l = l/(micros() - prev_time);
  l = l*60;
  nextRPM = l; // 1rps = 1R/1,000,000us
                     // 2rps = 1R/500,000
                     // 4rps = 1R/250,000
  
  if (encoderStep >= steps_per_rotation){
      //lastFullRotation = micros();
      encoderStep=encoderStep-steps_per_rotation;

      float unit_in_microS = 1000000;
      float RPS = unit_in_microS/(micros() - prev_time);
      RPM = RPS*60;
      Serial.println(nextRPM-RPM);
     
      prev_time = micros();

      pid();
    
  }
}
