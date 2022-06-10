uint8_t letters[]{
  119, //'A'
  127,//'B'
  57,//'C'
  94,//'D'
  121,//'E'
  113,//'F'
  61,//'G'
  118,//'H'
  6,//'I'
  30,//'J'
  118,//'K'
  56,//'L'
  85,//'M'
  84,//'N'
  92,//'O'
  115,//'P'
  92,//'Q'
  80,//'R'
  109,//'S'
  120,//'T'
  62,//'U'
  42,//'V'
  106,//'W'
  118,//'X'
  110,//'Y'
  91,//'Z'
};

uint8_t numbers[]{
  63, //'0'
  6, //'1'
  91, //'2'
  79, //'3'
  102, //'4'
  109, //'5'
  125, //'6'
  7, //'7'
  127, //'8'
  111, //'9'
};

uint8_t getCharMap(char c){
  if(c == 32){return 0;}
  if(c > 47 && c < 58){return numbers[c-48];}
  if(c > 64 && c < 91){return letters[c-65];}
}
void getCharacterBitmap(char character){
  //if(character == ' '){currentChar[0] = "0000000000000";};
  //if(character == 'a' || character == 'A'){currentChar[0] = "0000001110111";};
  //if(character == 'b'){currentChar[0] = "0000001111100";}; if(character == 'B'){currentChar[0] = "0000001111111";};
  //if(character == 'c'){currentChar[0] = "0000001011000";}; if(character == 'C'){currentChar[0] = "0000000111001";};
  //if(character == 'd'){currentChar[0] = "0000001111100";}; if(character == 'D'){currentChar[0] = "0000000111111";};
  
  //if(character == 'e' || character == 'E'){currentChar[0] = "0000001111001";};
  //if(character == 'f' || character == 'F'){currentChar[0] = "0000001110001";};
  //if(character == 'g' || character == 'G'){currentChar[0] = "0000000111101";};
  //if(character == 'h' || character == 'H'){currentChar[0] = "0000001110100";};
  //if(character == 'i' || character == 'I'){currentChar[0] = "0000000000110";};
  //if(character == 'j' || character == 'J'){currentChar[0] = "0000000011110";};
  //if(character == 'k' || character == 'K'){currentChar[0] = "0000001110110";};
  //if(character == 'l' || character == 'L'){currentChar[0] = "0000000111000";};
  //if(character == 'm' || character == 'M'){currentChar[0] = "0000001010101";};
  //if(character == 'n' || character == 'N'){currentChar[0] = "0000000110111";};
  //if(character == 'o'){currentChar[0] = "0000001011100";}; if(character == 'O'){currentChar[0] = "0000000111111";};
  //if(character == 'p' || character == 'P'){currentChar[0] = "0000001110011";};
  //if(character == 'r' || character == 'R'){currentChar[0] = "0000001010000";};
  //if(character == 's' || character == 'S'){currentChar[0] = "0000001101101";};
  //if(character == 't' || character == 'T'){currentChar[0] = "0000001111000";};
  //if(character == 'u'){currentChar[0] = "0000000011100";}; if(character == 'U'){currentChar[0] = "0000000111110";};
  //if(character == 'v'){currentChar[0] = "0000000011100";}; if(character == 'V'){currentChar[0] = "0000000101010";};
  //if(character == 'W' || character == 'W'){currentChar[0] = "0000001101010";};
  //if(character == 'x' || character == 'X'){currentChar[0] = "0000001110100";};
  //if(character == 'y' || character == 'Y'){currentChar[0] = "0000001101110";};
  //if(character == 'z' || character == 'Z'){currentChar[0] = "0000001011011";};
}
