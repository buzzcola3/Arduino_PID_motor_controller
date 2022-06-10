

short int selectedMenuOption[]{-1, 0, 0};
uint8_t currentDepth = 0;

bool adjustingVar = false;
bool adjustable = false;
float adjustmentOffset = 0; //offset of new value to the ORG value

bool adjustUp = false;
bool adjustDown = false;
bool adjustEnd = false;
//down = false;
//confirm = false;
//goBack = false;

float pid_P = 0.02, pid_I = 0.11, pid_D = 0;//todo do not define herre

void menuNavigate(){
  if(adjustingVar == true){return;}
  
  if(up == true){selectedMenuOption[currentDepth]++; Serial.println(selectedMenuOption[currentDepth]); up = false;}
  
  if(down == true){selectedMenuOption[currentDepth]--; Serial.println(selectedMenuOption[currentDepth]); down = false;}
  if(selectedMenuOption[currentDepth] <= 0){selectedMenuOption[currentDepth] = 1;}
  
  if(goBack == true){selectedMenuOption[currentDepth] = 0; goBack = false;}
  
  if(confirm == true && adjustable == false){selectedMenuOption[currentDepth+1] = 1; confirm = false;}
  if(confirm == true && adjustable == true){adjustingVar = true; confirm = false;}
}

void adjustVar(){
  if(adjustingVar == false){return;}

  if(up == true){adjustUp = true; Serial.println("adjust UP"); up = false;}

  if(down == true){adjustDown = true; Serial.println("adjust DOWN"); down = false;}

  if(goBack == true){adjustmentOffset = 0; Serial.println("adjust ABORT"); adjustingVar = false; goBack = false;}
  
  if(confirm == true){adjustEnd = true; Serial.println("adjust END"); adjustingVar = false; confirm = false;}
}

void SettingsPID(){
  currentDepth = 2;

  if(selectedMenuOption[currentDepth] > 3){selectedMenuOption[2] = 3;}
  
  if(selectedMenuOption[currentDepth] == 1){
    adjustable = true;
    if(adjustingVar == true){writeNumberToScreen(pid_P + adjustmentOffset);}
    
    if(adjustUp == true){adjustmentOffset = adjustmentOffset + 0.01; adjustUp = false;}
    if(adjustDown == true){adjustmentOffset = adjustmentOffset - 0.01; adjustDown = false;}
    if(adjustEnd == true){pid_P = pid_P + adjustmentOffset; adjustmentOffset = 0; adjustEnd = false;}

    if(adjustingVar == true){return;}
    
    writeCharToScreen('P', 1);
    writeCharToScreen(' ', 2);
    writeCharToScreen(' ', 3);
    writeCharToScreen(' ', 4);
  }
  if(selectedMenuOption[currentDepth] == 2){
    adjustable = true;
    if(adjustingVar == true){writeNumberToScreen(pid_I + adjustmentOffset);}
    
    if(adjustUp == true){adjustmentOffset = adjustmentOffset + 0.01; adjustUp = false;}
    if(adjustDown == true){adjustmentOffset = adjustmentOffset - 0.01; adjustDown = false;}
    if(adjustEnd == true){pid_I = pid_P + adjustmentOffset; adjustmentOffset = 0; adjustEnd = false;}

    if(adjustingVar == true){return;}
    
    writeCharToScreen('I', 1);
    writeCharToScreen(' ', 2);
    writeCharToScreen(' ', 3);
    writeCharToScreen(' ', 4);
  }
  if(selectedMenuOption[currentDepth] == 3){
    adjustable = true;
    if(adjustingVar == true){writeNumberToScreen(pid_D + adjustmentOffset);}
    
    if(adjustUp == true){adjustmentOffset = adjustmentOffset + 0.01; adjustUp = false;}
    if(adjustDown == true){adjustmentOffset = adjustmentOffset - 0.01; adjustDown = false;}
    if(adjustEnd == true){pid_D = pid_D + adjustmentOffset; adjustmentOffset = 0; adjustEnd = false;}

    if(adjustingVar == true){return;}
    
    writeCharToScreen('D', 1);
    writeCharToScreen(' ', 2);
    writeCharToScreen(' ', 3);
    writeCharToScreen(' ', 4);
  }
}

void Settings123(){
  currentDepth = 2;

  if(selectedMenuOption[currentDepth] > 3){selectedMenuOption[2] = 3;}
  
  if(selectedMenuOption[currentDepth] == 1){
    
    writeCharToScreen('1', 1);
    writeCharToScreen(' ', 2);
    writeCharToScreen(' ', 3);
    writeCharToScreen(' ', 4);
  }
  if(selectedMenuOption[currentDepth] == 2){
    
    writeCharToScreen('2', 1);
    writeCharToScreen(' ', 2);
    writeCharToScreen(' ', 3);
    writeCharToScreen(' ', 4);
  }
  if(selectedMenuOption[currentDepth] == 3){
    
    writeCharToScreen('3', 1);
    writeCharToScreen(' ', 2);
    writeCharToScreen(' ', 3);
    writeCharToScreen(' ', 4);
  }
}

void SettingsPIDMenu(){
  //if(selectedMenuOption[1] == -1){return;}
  currentDepth = 1;
  
  if(selectedMenuOption[currentDepth] > 2){selectedMenuOption[1] = 2;}
  
  if(selectedMenuOption[currentDepth] == 1){
    if(selectedMenuOption[currentDepth+1] != 0){SettingsPID(); return;}
    writeCharToScreen('P', 1);
    writeCharToScreen('I', 2);
    writeCharToScreen('D', 3);
    writeCharToScreen(' ', 4);
  }
  
  if(selectedMenuOption[currentDepth] == 2){
    if(selectedMenuOption[currentDepth+1] != 0){Settings123(); return;}
    writeCharToScreen('1', 1);
    writeCharToScreen('2', 2);
    writeCharToScreen('3', 3);
    writeCharToScreen(' ', 4);
  }
  
}

void MainScreen(){
  currentDepth = 0;
  adjustable = false;


  if(selectedMenuOption[currentDepth] == 0){selectedMenuOption[currentDepth] = 1;}
  if(selectedMenuOption[currentDepth] > 2){selectedMenuOption[currentDepth] = 2;}
 
  if(selectedMenuOption[currentDepth] == 1){
    writeNumberToScreen(RPM);
    adjustingVar = true;
    if(adjustUp == true){target_rpm = target_rpm + 100; adjustUp = false;}
    if(adjustDown == true){target_rpm = target_rpm - 100; adjustDown = false;}
    if(adjustEnd == true){adjustingVar = false; selectedMenuOption[currentDepth] = 2; adjustEnd = false;}
  }
  
  if(selectedMenuOption[currentDepth] == 2){
    if(selectedMenuOption[currentDepth+1] != 0){SettingsPIDMenu(); return;}
    writeCharToScreen('S', 1);
    writeCharToScreen('E', 2);
    writeCharToScreen('T', 3);
    writeCharToScreen('T', 4);
  }


}
void Menu(){
  menuNavigate();
  adjustVar();
  
  
  MainScreen();
}
