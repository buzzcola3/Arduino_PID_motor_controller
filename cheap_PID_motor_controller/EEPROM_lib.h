#include <EEPROM.h>

#define EEPROM_version 1 //update this if the EEPROM_store.h has been changed
#define USED_EEPROM_START 0
#define USED_EEPROM_END 255

class EEPROM_lib {
  public:

  void check_wipe_eeprom(void)
{
if (EEPROM_version == EEPROM.read(1) && EEPROM.read(0) == 'V'){Serial.println("EEPROM version is CORRECT");}
else
 {
  short int i = USED_EEPROM_START;
  do {EEPROM.update(i, 0); i++;} while(i<=USED_EEPROM_END);
  EEPROM.update(0+USED_EEPROM_START, 'V');
  EEPROM.update(1+USED_EEPROM_START, EEPROM_version);
  //Serial.println("used EEPROM section cleared and version updated");
 }
}


int save_to_EEPROM(short int bank_number_of_saved_integer, float value_to_save)
 {
   int size_of_integer_to_be_saved = sizeof(value_to_save);
   int selected_eeprom_address = USED_EEPROM_START+2;

   int indexed_data_bank_number = 1;
   int bank_to_write_to = -1;

   int first_free_bank = -1;
   int first_free_bank_size = -1;

   while(bank_to_write_to == -1) //while no write address
   {
       if(EEPROM.read(selected_eeprom_address) == 0) //cuurent address was never used, use it
       {
         //Serial.println("AAAAAAaaaaaaaa");
         bank_to_write_to = selected_eeprom_address;
         break;
       }

       if(bank_number_of_saved_integer == indexed_data_bank_number) // if already saved;
       {
         //Serial.println("BBBBBBBbbbbb");
         first_free_bank = selected_eeprom_address;
         first_free_bank_size = EEPROM.read(selected_eeprom_address+2); //get size of the existing bank
         if(first_free_bank_size <= size_of_integer_to_be_saved){bank_to_write_to = first_free_bank; break;} //if int still fits, use the bank
         
       }

       if(EEPROM.read(selected_eeprom_address+1) == 0) //if the current bank exists but marked for overwrite
       {
         //Serial.println("CCCCcccccccc");
         first_free_bank = selected_eeprom_address;
         first_free_bank_size = EEPROM.read(selected_eeprom_address+2); //get size of the first free bank

         if(first_free_bank_size <= size_of_integer_to_be_saved){bank_to_write_to = selected_eeprom_address; break;} //if int fits, use the bank
         
       }

       indexed_data_bank_number++; //move to the next bank
       selected_eeprom_address = selected_eeprom_address + (3+EEPROM.read(selected_eeprom_address+2));
   }
   
   //Serial.print("bank_to_write_to: ");
   //Serial.println(bank_to_write_to);

   if(EEPROM.read(bank_to_write_to) == 0){EEPROM.update(bank_to_write_to, indexed_data_bank_number);}
   if(first_free_bank_size == -1){EEPROM.update(bank_to_write_to+2, size_of_integer_to_be_saved);}
   
   EEPROM.update(bank_to_write_to+1, bank_number_of_saved_integer);
   EEPROM.put(bank_to_write_to+3, value_to_save);
  return selected_eeprom_address;
 }

float load_from_eeprom(int bank_number_of_saved_integer)
 {
   int bank_to_read_from = -1;
   int selected_eeprom_address = USED_EEPROM_START+2;
   int indexed_data_bank_number = 1;

   while(bank_to_read_from == -1) //while no read address
   {
       if(bank_number_of_saved_integer == indexed_data_bank_number) // if already saved;
       {
         //Serial.print("Found :D  >");
         //Serial.println(indexed_data_bank_number);
         bank_to_read_from = selected_eeprom_address;
         break;
       }

    indexed_data_bank_number++; //move to the next bank
    selected_eeprom_address = selected_eeprom_address + (3+EEPROM.read(selected_eeprom_address+2));
   }
   
   float loaded_int;
   EEPROM.get(bank_to_read_from+3, loaded_int);
   return loaded_int;
 } 

 void dump_eeprom(void)
 {
   int i = USED_EEPROM_START;
   int u = 0;
   int o = 0;
   do
   {
    o = EEPROM.read(i);
    Serial.print(o); Serial.print(" ");
    if(u == 10){Serial.println(); u=0;}
    i++;
    u++;
   } while(i<=USED_EEPROM_END);
 }
};
