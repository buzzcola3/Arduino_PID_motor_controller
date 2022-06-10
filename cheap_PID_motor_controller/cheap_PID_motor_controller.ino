#include "EEPROM_lib.h"

#define IDLE_SPEED 25
#include "BTS7960_control.h"
BTS7960_lib mtr;
unsigned long RPM = 0;

#define display_SCK 12 //shift data register (D12)
#define display_SCK_HIGH PORTB |= B00010000 //shift data register (D12)
#define display_SCK_LOW PORTB &= B11101111 //shift data register (D12)

#define display_DATA 11 //output for display data
#define display_DATA_HIGH PORTB |= B00001000 //output for display data (D11)
#define display_DATA_LOW PORTB &= B11110111 //output for display data (D11)

#define display_RCK 6 //confirm
#define display_RCK_HIGH PORTD |= B01000000 //confirm (D10)
#define display_RCK_LOW PORTD &= B10111111 //confirm (D10)

#define display_input_DATA 5
#define display_input_PL 8 //refresh button status (buffer)


#include "buttonActions.h"
#include "buttonInput.h"
#include "LedDisplay.h"
#include "menu.h"
#include "getRPM.h"
#include "PID.h"




void display_setup(){
  pinMode(display_SCK, OUTPUT); digitalWrite(display_SCK, LOW);
  pinMode(display_DATA, OUTPUT); digitalWrite(display_DATA, LOW);
  pinMode(display_RCK, OUTPUT); digitalWrite(display_RCK, LOW);

  pinMode(display_input_DATA, INPUT);
  pinMode(display_input_PL, OUTPUT); digitalWrite(display_input_PL, LOW);
}


void setup() {
  
  Serial.begin(115200);
  display_setup();
  pidSetup();
  rpmSetup();

  
  pinMode(A0, INPUT);
  writeCharToScreen('S', 1);
  writeCharToScreen('U', 2);
  writeCharToScreen('S', 3);
  writeCharToScreen(' ', 4);
  //writeDotToScreen(2, true);
  
  selectedMenuOption[0]=1;

  EEPROM_lib var;
  var.check_wipe_eeprom();
  var.save_to_EEPROM(1, 2.76);
  Serial.println(var.load_from_eeprom(1));
}


unsigned long displayUpdate = 0;

void loop() {
  sendDisplayBuffer();
  updateButtonStatus();
  getRPM();
  Menu();
  

  if(millis() - displayUpdate > 150){
    //writeNumberToScreen(RPM);
    //Serial.print(selectedMenuOption[0]);
    //Serial.print(selectedMenuOption[1]);
    //Serial.println(selectedMenuOption[2]);
    displayUpdate = millis();
  }
}
