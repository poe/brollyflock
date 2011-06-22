#include "WProgram.h"
#include "memory_color.h"

Color::Color(){
};

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

void Color::printColor(){
  Serial.print(" red = ");
  Serial.print(red);
  Serial.print(" green = ");
  Serial.print(green);
  Serial.print(" blue = ");
  Serial.print(blue);
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
  long totalDelay = 0;
  for(int color = 0;color < getNumberOfElements();color ++){
    totalDelay = totalDelay + getDelay(color);
  };
  totalTime = totalDelay;
};

int ColorList::getNumberOfElements(){
  return _sizeOfList;
};

int ColorList::getDelay(int address){
  if (address != address % _sizeOfList){
    address = address % _sizeOfList;
  }
  int colorDelay = pgm_read_word_near(_listPointer + address * 4 + 3);
  return colorDelay;
};

int ColorList::incrementAddress(int address){
  address++;
  if (address != address % _sizeOfList){
    address = address % _sizeOfList;
  }
  if (address < 0){
    address = _sizeOfList - 1;
  }
  return address;
}

int ColorList::decrementAddress(int address){
  address--;
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
  }
  int red = pgm_read_word_near(_listPointer + address * 4);
  int green = pgm_read_word_near(_listPointer + address * 4 + 1);
  int blue = pgm_read_word_near(_listPointer + address * 4 + 2);
  return Color(red,green,blue);
};

Color MasterColorList::getColorNow(int delayTime){
  long currentTime = (millis() + delayTime) % getTotalTime();
  int color;
  for(color = 0;color < getNumberOfElements();color ++){
    if(currentTime < getDelay(color)){
      break;
    };
    currentTime = currentTime - getDelay(color);
  };
  Color colorAverage;
  colorAverage.progressColor(getLastColor(color), getCurrentColor(color), float(currentTime) / float(getDelay(color)));
  return colorAverage;
};

Color MasterColorList::getLastColorNow(int delayTime){
  long currentTime = (millis() + delayTime) % getLastTotalTime();
  int color;
  for(color = 0;color < getLastNumberOfElements();color ++){
    if(currentTime < getLastDelay(color)){
      break;
    };
    currentTime = currentTime - getLastDelay(color);
  };
  Color colorAverage;
  colorAverage.progressColor(getLastLastColor(color), getLastCurrentColor(color), float(currentTime) / float(getLastDelay(color)));
  return colorAverage;
};

Color MasterColorList::getSmoothColorNow(int delayTime){
  if(transitionRatio() == 1){
    return getColorNow(delayTime);
  }
  Color colorAverage;
  colorAverage.progressColor(getLastColorNow(delayTime), getColorNow(delayTime), transitionRatio());
  return colorAverage;
};

long MasterColorList::getTotalTime(){
  return _listOfColorListsPointer[_currentList].totalTime;
};

long MasterColorList::getLastTotalTime(){
  return _listOfColorListsPointer[_lastList].totalTime;
};

PROGMEM prog_int16_t devilish_color_list[] = {
  1023,0,0,16000,
  1023,200,0,16000,
  0,0,0,16000,
};

ColorList devilish_color(devilish_color_list,sizeof(devilish_color_list) / (sizeof(prog_int16_t) * 4));

PROGMEM prog_int16_t minty_color_list[] = {
  0,1023,1023,2000,
  0,1023,0,2000,
  0,0,1023,2000,
};

ColorList minty_color(minty_color_list,sizeof(minty_color_list) / (sizeof(prog_int16_t) * 4));

PROGMEM prog_int16_t fire_color_list[] = {
  1023,0,0,2000,
  1023,1023,0,2000,
  1023,1023,1023,2000,
  1023,1023,0,2000,
};

ColorList fire_color(fire_color_list,sizeof(fire_color_list) / (sizeof(prog_int16_t) * 4));

PROGMEM prog_int16_t ocean_color_list[] = {
  0,1023,1023,2000,
  0,1023,0,2000,
  500,1023,0,2000,
  0,0,1023,2000,  
};

ColorList ocean_color(ocean_color_list,sizeof(ocean_color_list) / (sizeof(prog_int16_t) * 4));

PROGMEM prog_int16_t cruise_color_list[] = {
  1023,1023,0,2000,
  1023,1023,1023,2000,
  0,1023,1023,2000,
};

ColorList cruise_color(cruise_color_list,sizeof(cruise_color_list) / (sizeof(prog_int16_t) * 4));

PROGMEM prog_int16_t slow_red_list[] = {
  1023,0,0,5000,
  0,0,0,5000,
};

ColorList slow_red_color(slow_red_list,sizeof(cruise_color_list) / (sizeof(prog_int16_t) * 4));

//ColorList listOfColorLists[] = {devilish_color,minty_color,fire_color,ocean_color,cruise_color,slow_red_color};
ColorList listOfColorLists[] = {devilish_color,minty_color};

MasterColorList::MasterColorList(int numberOfColorLists,ColorList* listOfColorListsPointer){
    //This is how long it fades between color schemes
    transitionTime = 10000;
    _currentList = 0;
    _lastList = numberOfColorLists - 1;
    _listOfColorListsPointer = listOfColorListsPointer;
    _numberOfColorLists = numberOfColorLists;
};

int MasterColorList::getDelay(int address){
  return _listOfColorListsPointer[_currentList].getDelay(address);
};

int MasterColorList::getLastDelay(int address){
  return _listOfColorListsPointer[_lastList].getDelay(address);
};

int MasterColorList::incrementList(){
  _lastList = _currentList;
  _currentList++;
  if (_currentList >= _numberOfColorLists){
    _currentList = 0;
  }
  transitionBegan = millis();
  return _currentList;  
};

float MasterColorList::transitionRatio(){
  long timeInTransition = millis() - transitionBegan;
  float transitionRatio = float(timeInTransition) / float(transitionTime);
  if(transitionRatio > 1){
    transitionRatio = 1;
  }  
  if(transitionRatio < 0){
    transitionRatio = 0;
  }
  return transitionRatio;  
};

Color MasterColorList::getCurrentColor(int address){
  return _listOfColorListsPointer[_currentList].getCurrentColor(address);
};

Color MasterColorList::getLastColor(int address){
  return _listOfColorListsPointer[_currentList].getLastColor(address);
};

Color MasterColorList::getNextColor(int address){
  return _listOfColorListsPointer[_currentList].getNextColor(address);
};

int MasterColorList::getNumberOfElements(){
  return _listOfColorListsPointer[_currentList].getNumberOfElements();
};

Color MasterColorList::getLastCurrentColor(int address){
  return _listOfColorListsPointer[_lastList].getCurrentColor(address);
};

Color MasterColorList::getLastLastColor(int address){
  return _listOfColorListsPointer[_lastList].getLastColor(address);
};

int MasterColorList::getLastNumberOfElements(){
  return _listOfColorListsPointer[_lastList].getNumberOfElements();
};

MasterColorList masterColorList(sizeof(listOfColorLists) / sizeof(ColorList),listOfColorLists);



