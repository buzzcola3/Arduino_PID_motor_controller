uint8_t buttonLastUpdated = 0;
bool buttonStatus[8];

void updateButtonStatus(){
  if(buttonLastUpdated < 7){return;}

  int i;
  while (0) {
    Serial.print(buttonStatus[i]);
    i++;
    if (i > 7) {
      break;
    }
  }
  //Serial.println();
  
  digitalWrite(display_input_PL, HIGH);
  digitalWrite(display_input_PL, LOW);
  buttonLastUpdated = 0;
}

void fetchButtonStatus(){
  if(buttonLastUpdated > 7){return;}

  bool old = buttonStatus[buttonLastUpdated];
  buttonStatus[buttonLastUpdated] = digitalRead(display_input_DATA);
  
  while(old < buttonStatus[buttonLastUpdated]){
    if(buttonLastUpdated == 2){button_PrgRst(); break;};
    if(buttonLastUpdated == 3){button_Up(); break;};
    if(buttonLastUpdated == 4){button_Unknown(); break;};
    if(buttonLastUpdated == 5){button_EnterDisp(); break;};
    if(buttonLastUpdated == 6){button_Down(); break;};
    if(buttonLastUpdated == 7){button_RunStop(); break;};
    break;
  }
  
  buttonLastUpdated++;
}


int oldPotValue = 0;
uint16_t inputPotValue(){
  int potValue = analogRead(A0)/100;
  int o = potValue + oldPotValue;
  oldPotValue = potValue;
  return o/2;
}
