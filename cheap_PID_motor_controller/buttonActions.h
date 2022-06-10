void writeCharToScreen(char character, uint8_t screenPosition);

bool up = false;
bool down = false;
bool confirm = false;
bool goBack = false;

void button_PrgRst(){
  goBack = true;
  Serial.println("PrgRst");
}

void button_EnterDisp(){
  Serial.println("EnterDisp");
  confirm = true;
}

unsigned int target_rpm = 200;
void button_RunStop(){
  if(mtr.getStatus() == 1){mtr.hardStop(); return;}
  if(mtr.getStatus() == 0){mtr.start(); return;}
}

void button_Up(){
  up = true;
  Serial.println("Up");
}

void button_Down(){
  down = true;
  Serial.println("Down");
}

void button_Unknown(){
  Serial.println("hi >:|");
  writeCharToScreen('I', 1);
  writeCharToScreen('D', 2);
  writeCharToScreen('K', 3);
  writeCharToScreen(' ', 4);
}
