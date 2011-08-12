#include "WProgram.h"
#include "memory_color.h"

Color::Color(int red_in, int green_in, int blue_in){
  red   = red_in;
  green = green_in;
  blue  = blue_in;
};

int Color::getRed(){
  return red;
};

int Color::getGreen(){
  return green;
};

int Color::getBlue(){
  return blue;
};

Color Color::progressColor(Color oldColor, Color newColor, float fraction){
  red = oldColor.red - ((oldColor.red - newColor.red) * fraction);
  green = oldColor.green - ((oldColor.green - newColor.green) * fraction);
  blue = oldColor.blue - ((oldColor.blue - newColor.blue) * fraction);
  return Color(red,green,blue);
};

ColorList::ColorList(prog_int16_t* listPointer,  int sizeOfList){
  _listPointer = listPointer;
  _sizeOfList = sizeOfList;
};

int ColorList::numberOfElements(){
  return _sizeOfList;
};

int ColorList::getDelay(int address){
  if (address != address % _sizeOfList){
    address = address % _sizeOfList;
    Serial.println("address looped in Delay");
  }
  return pgm_read_word_near(_listPointer + address * 3 + 3);
};

int ColorList::incrementAddress(int address){
  address--;
  if (address != address % _sizeOfList){
    address = address % _sizeOfList;
  }
  if (address < 0){
    address = _sizeOfList - 1;
  }
  return address;
}

int ColorList::decrementAddress(int address){
  address++;
  if (address != address % _sizeOfList){
    address = address % _sizeOfList;
  }
  if (address < 0){
    address = _sizeOfList - 1;
  }
  return address;
};

Color ColorList::getCurrentColor(int address){
  if (address != address % _sizeOfList){
    address = address % _sizeOfList;
    Serial.println("address looped in getColor");
  }
  int red = pgm_read_word_near(_listPointer + address * 4);
  int green = pgm_read_word_near(_listPointer + address * 4 + 1);
  int blue = pgm_read_word_near(_listPointer + address * 4 + 2);
  return Color(red,green,blue);
};

Color ColorList::getLastColor(int address){
  address--;
  if (address != address % _sizeOfList){
    address = address % _sizeOfList;
    Serial.println("address looped in getColor");
  }
  if (address < 0){
    address+=_sizeOfList;
  }
  int red = pgm_read_word_near(_listPointer + address * 4);
  int green = pgm_read_word_near(_listPointer + address * 4 + 1);
  int blue = pgm_read_word_near(_listPointer + address * 4 + 2);
  return Color(red,green,blue);
};

Color ColorList::getNextColor(int address){
  address++;
  if (address != address % _sizeOfList){
    address = address % _sizeOfList;
    Serial.println("address looped in getColor");
  }
  int red = pgm_read_word_near(_listPointer + address * 4);
  int green = pgm_read_word_near(_listPointer + address * 4 + 1);
  int blue = pgm_read_word_near(_listPointer + address * 4 + 2);
  return Color(red,green,blue);
};

PROGMEM prog_int16_t devilish_color_list[] = {
  1023,0,0,500,
  1023,1023,0,500,
  0,0,0,1000,
};

ColorList devilish_color(devilish_color_list,sizeof(devilish_color_list) / (sizeof(prog_int16_t) * 4));

PROGMEM prog_int16_t minty_color_list[] = {
  0,1023,1023,500,
  0,1023,0,500,
  0,0,1023,500,
};

ColorList minty_color(minty_color_list,sizeof(minty_color_list) / (sizeof(prog_int16_t) * 4));

PROGMEM prog_int16_t fire_color_list[] = {
  1023,0,0,500,
  1023,1023,0,500,
  1023,1023,1023,500,
  1023,1023,0,500,
};

ColorList fire_color(fire_color_list,sizeof(fire_color_list) / (sizeof(prog_int16_t) * 4));

PROGMEM prog_int16_t ocean_color_list[] = {
  0,1023,1023,500,
  0,1023,0,500,
  500,1023,0,500,
  0,0,1023,500,  
};

ColorList ocean_color(ocean_color_list,sizeof(ocean_color_list) / (sizeof(prog_int16_t) * 4));

PROGMEM prog_int16_t cruise_color_list[] = {
  1023,1023,0,500,
  1023,1023,1023,500,
  0,1023,1023,500,
};

ColorList cruise_color(cruise_color_list,sizeof(cruise_color_list) / (sizeof(prog_int16_t) * 4));

ColorList listOfColorLists[] = {fire_color,ocean_color,cruise_color};

Color MasterColorList::getCurrentColor(int address){
  return _listOfColorListsPointer[_currentList].getCurrentColor(address);
};

Color MasterColorList::getLastColor(int address){
  return _listOfColorListsPointer[_currentList].getLastColor(address);
};

Color MasterColorList::getNextColor(int address){
  return _listOfColorListsPointer[_currentList].getLastColor(address);
};

MasterColorList::MasterColorList(int numberOfColorLists,ColorList* listOfColorListsPointer){
    _currentList = 0;
    _listOfColorListsPointer = listOfColorListsPointer;
    _numberOfColorLists = numberOfColorLists;
};

int MasterColorList::incrementList(){
  _currentList++;
  if (_currentList >= _numberOfColorLists){
    _currentList = 0;
  }  
}

int MasterColorList::numberOfElements(){
  return _listOfColorListsPointer[_currentList].numberOfElements();
};

MasterColorList masterColorList(sizeof(listOfColorLists) / sizeof(ColorList),listOfColorLists);



