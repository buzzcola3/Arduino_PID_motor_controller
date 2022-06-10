  #ifndef L_EN
  #define L_EN 3
  #endif
  
  #ifndef R_EN
  #define R_EN 4
  #endif

class BTS7960_lib {
  public:

  bool getStatus(){
    if(active == true){return true;}
    if(active == false){return false;}
  }
  
  void start(){
    active = 1;
    pinMode(L_EN, OUTPUT);
    digitalWrite(L_EN, HIGH);
    
    pinMode(R_EN, OUTPUT);
    digitalWrite(R_EN, HIGH);

    #ifdef IDLE_SPEED
    idle();
    return;
    #endif
    control(1,0);
    control(0,0);
  }

  void hardStop(){
    active = 0;
    control(0, 0);
    control(1, 0);
    //digitalWrite(L_EN, LOW);
    //digitalWrite(R_EN, LOW);
  }

  void softStop(){
    active = 0;
    digitalWrite(L_EN, LOW);
    digitalWrite(R_EN, LOW);
  }

#ifdef IDLE_SPEED
  void idle(){
    if(IDLE_SPEED > 0){control(1, IDLE_SPEED);}
    if(IDLE_SPEED < 0){control(0, IDLE_SPEED);}
  }
#endif

  void control(bool DIRECTION, int PWM){
    if(DIRECTION == 1){
      P9_10bitPWM(0);
      P10_10bitPWM(PWM);
      return;
    }
    if(DIRECTION == 0){
      P10_10bitPWM(0);
      P9_10bitPWM(PWM);
      return;
    }
  }
  
  private:

  bool active = 0;
  
  void P9_10bitPWM(uint16_t val){ // P9, P10
    pinMode(9, OUTPUT);
    
    TCCR1A |= B10000011;
    TCCR1A &= B10101111;

    TCCR1B |= B00001010;
    TCCR1B &= B00101010;
    
    //TCCR1A = B10000011; //10bit fast
    //TCCR1B = B00001010; //x8
    OCR1A = val;
  }
  void P10_10bitPWM(uint16_t val){ // P9, P10
    pinMode(10, OUTPUT);

    TCCR1A |= B00100011;
    TCCR1A &= B10101111;

    TCCR1B |= B00001010;
    TCCR1B &= B00101010;
    
    //TCCR1A = B00100011; //10bit fast
    //TCCR1B = B00001010; //x8
    OCR1B = val;
  };
  
};
// TCCR1A = COM1A1, COM1A0, COM1B1, COM1B0,    ---,   ---,  WGM11,  WGM10
// TCCR1B =  ICNC1,  ICES1,  -----,  WGM13,  WGM12,  CS12,   CS11,  CS10 

// TCCR1A =   ?   ,  ?    ,  ?    ,  ?    ,  X    ,  X   ,  1    ,  1
// TCCR1B =   ?   ,  ?    ,  X    ,  0    ,  1    ,  0   ,  1    ,  0

// TCCR1A = (TCCR1A & B00001111) | B00000011;
// TCCR1B = (TCCR1B & B00101010) | B00001010;
// 0x03FF = 0x400;

//TCCR1A = B00000011 10bit fast
//TCCR1B = B00001010 x8
//OCR1A = val;
//OCR1B = val;
