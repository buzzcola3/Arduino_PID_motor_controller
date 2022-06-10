
uint8_t buffer_possition = 0;
bool currentCharNumber[5];
bool currentChar[8];
bool fullCharBitArray[13];
bool fullDisplayBuffer[65];

#include "characterBitmap.h"

void numberToCharNumber(uint8_t number) {
  if (number == 1) {
    bool n1[5] = {0, 1, 0, 0, 0};
    memcpy(currentCharNumber, n1, sizeof(n1));
  }
  if (number == 2) {
    bool n2[5] = {0, 0, 1, 0, 0};
    memcpy(currentCharNumber, n2, sizeof(n2));
  }
  if (number == 3) {
    bool n3[5] = {0, 0, 0, 1, 0};
    memcpy(currentCharNumber, n3, sizeof(n3));
  }
  if (number == 4) {
    bool n4[5] = {0, 0, 0, 0, 1};
    memcpy(currentCharNumber, n4, sizeof(n4));
  }

  int i = 0;
  while (0) {
    Serial.println(currentCharNumber[i]);
    i++;
    if (i >= 5) {
      break;
    }
  }

}
void numberToCurrentChar(uint8_t number) { //convert number to binary(8bit) stored in currentChar[]
  int i = 0;
  int c = 7;
  while (1) {
    currentChar[i] = bitRead(number, c);
    //Serial.print(currentChar[i]);
    i++;
    c--;
    if (i > 7) {
      break;
    }
  }
  //Serial.println();
}
void combineToFullCharBitArray() {
  memcpy(fullCharBitArray + 0, currentCharNumber, sizeof(currentCharNumber));
  memcpy(fullCharBitArray + 5, currentChar, sizeof(currentChar));
}

void moveClock(){
  
  display_SCK_HIGH;
  fetchButtonStatus();
  display_SCK_LOW;
}

void bufferDisplay(){
  //digitalWrite(display_RCK, HIGH);
  //digitalWrite(display_RCK, LOW);
  display_RCK_HIGH;
  buffer_possition++;
  display_RCK_LOW;
}

bool bitShiftToScreen(bool data[]){
  uint8_t o = 0;
  uint8_t i = 13*buffer_possition-1;
  while(1){
    if(data[i]){display_DATA_HIGH;}
    if(!data[i]){display_DATA_LOW;}
    moveClock();
    i++;
    o++;
    if(o > 13){break;}
  }
        
  bufferDisplay();
  
  
  if(buffer_possition > 4){buffer_possition = 0;}
}

void writeCharToScreen(char character, uint8_t screenPosition) { //write to buffer
  if(screenPosition > 4 || screenPosition < 1){return;}
  
  numberToCharNumber(screenPosition);
  numberToCurrentChar(getCharMap(character));
  combineToFullCharBitArray();
  //bitShiftToScreen(fullCharBitArray);

  memcpy(fullDisplayBuffer + (13 * screenPosition), fullCharBitArray, sizeof(fullCharBitArray));

  int i;
  while (0) {
    Serial.print(fullDisplayBuffer[i]);
    i++;
    if (i >= 65) {
      break;
    }
  }
  //Serial.println("<buff");
}

void writeDotToScreen(uint8_t screenPosition, bool TrueFalse){
  if(screenPosition > 4 || screenPosition < 1){return;}
  
  bool c;
  if(TrueFalse == true){c = 1;}
  if(TrueFalse == false){c = 0;}
  
  fullDisplayBuffer[(13 * screenPosition)+5] = c;
}

void writeNumberToScreen(float number){
  float f = 0;
  if(number < f){number = number*(-1);}
  char Ostring[10]; //good up to 9 999 999.00
  dtostrf(number, 4, 2, Ostring);

  int i = 0;
  int o = 1;
  while(1){
    if(Ostring[i] == '.'){writeDotToScreen(i, true);i++;}
    writeCharToScreen(Ostring[i], o);
    i++;
    o++;
    if(i > 4){break;}
  }
  
  
  //Serial.print(Ostring[0]);
  //Serial.print(Ostring[1]);
  //Serial.print(Ostring[2]);
  //Serial.print(Ostring[3]);
  //Serial.println(Ostring[4]);
}

void sendDisplayBuffer() {
  bitShiftToScreen(fullDisplayBuffer);
}
