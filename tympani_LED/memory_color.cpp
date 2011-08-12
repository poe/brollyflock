//all arduino libs require this
#include "WProgram.h"
#include "memory_color.h"

//empty color constructor for arrays and such.  
Color::Color(){
};

//Here is a constructor that takes 3 ints for red, green and blue.
Color::Color(int red_in, int green_in, int blue_in){
  red   = red_in;
  green = green_in;
  blue  = blue_in;
};

//these three color routines are used for getting the integer values out
//These integers are used in calculations and to feed the array.
//return the red color 
int Color::getRed(){
  return red;
};

//return the green color
int Color::getGreen(){
  return green;
};

//return the blue color
int Color::getBlue(){
  return blue;
};

//debugging printing
void Color::printColor(){
  Serial.print(" red = ");
  Serial.print(red);
  Serial.print(" green = ");
  Serial.print(green);
  Serial.print(" blue = ");
  Serial.print(blue);
};

//this lets you move a fraction of the way from one color to another
Color Color::progressColor(Color oldColor, Color newColor, float fraction){
  red = oldColor.red - ((oldColor.red - newColor.red) * fraction);
  green = oldColor.green - ((oldColor.green - newColor.green) * fraction);
  blue = oldColor.blue - ((oldColor.blue - newColor.blue) * fraction);
  return Color(red,green,blue);
};

//This is the constructor for the color list, a list of colors to cycle through
ColorList::ColorList(prog_int16_t* listPointer,  int sizeOfList){
  //array pointer to the start of the list
  _listPointer = listPointer;
  //size of the list for bounds checking and wrap arround
  _sizeOfList = sizeOfList;
  long totalDelay = 0;
  for(int color = 0;color < getNumberOfElements();color ++){
    totalDelay = totalDelay + getDelay(color);
  };
  //tally up the total number of miliseconds in the list and stuff it in totalTime
  totalTime = totalDelay;
};

int ColorList::getNumberOfElements(){
  //returns the size of the color list for purposes of modulating total delays
  return _sizeOfList;
};

//this returns the delay for the color list, wrapping around to the beginning if it overflows the list.
int ColorList::getDelay(int address){
  if (address != address % _sizeOfList){
    address = address % _sizeOfList;
  }
  int colorDelay = pgm_read_word_near(_listPointer + address * 4 + 3);
  return colorDelay;
};

//This moves to the next color in the list, wrapping around to the beginning.  
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

//This moves to the last color in the list, wrapping around to the end.
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

//This retuns the colors for a given in list address
Color ColorList::getCurrentColor(int address){
  if (address != address % _sizeOfList){
    address = address % _sizeOfList;
  }
  int red = pgm_read_word_near(_listPointer + address * 4);
  int green = pgm_read_word_near(_listPointer + address * 4 + 1);
  int blue = pgm_read_word_near(_listPointer + address * 4 + 2);

  return Color(red,green,blue);
};

//This gets the previos color at a list wise address, wrapping around the bottom to the top.
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

//This gets the next color in the list, wrapping around to the bottom from the top.
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

//This gets the color delaytime + current time of the way along the color list
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

//This gets the color delaytime + current time of the way along the color list for the previous color list
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

/*
Color MasterColorList::getAverageTotalTime(){
  return getTotalTime() * transitionRatio + getLastTotalTime() * (1 - transitionRatio);
};
*/

//This takes the last color (above) and the current color (above) offset for time and uses the transition to smoothly fade them
Color MasterColorList::getSmoothColorNow(int delayTime){
  if(transitionRatio() == 1){
    return getColorNow(delayTime);
  }
  Color colorAverage;
  colorAverage.progressColor(getLastColorNow(delayTime), getColorNow(delayTime), transitionRatio());
  return colorAverage;
};

//This returns the total time for the current color list
long MasterColorList::getTotalTime(){
  return _listOfColorListsPointer[_currentList].totalTime;
};

//This returns the total time for the last color list
long MasterColorList::getLastTotalTime(){
  return _listOfColorListsPointer[_lastList].totalTime;
};

//Here we have a big blog of flash data for the various lists.
//These each have red,green,blue and a delay per line
//They are then wrapped in Colorlists using sizeof for the size of the array.

PROGMEM prog_int16_t devilish_color_list[] = {
  1023,0,0,2367,
  1023,200,0,2367,
  0,0,0,2367,
};

ColorList devilish_color(devilish_color_list,sizeof(devilish_color_list) / (sizeof(prog_int16_t) * 4));

PROGMEM prog_int16_t minty_color_list[] = {
  0,1023,1023,2367,
  0,1023,0,2367,
  0,0,1023,2367,
};

ColorList minty_color(minty_color_list,sizeof(minty_color_list) / (sizeof(prog_int16_t) * 4));

PROGMEM prog_int16_t fire_color_list[] = {
  1023,0,0,2367,
  1023,300,0,2367,
  1023,500,700,2367,
  1023,0,300,2367,
};

ColorList fire_color(fire_color_list,sizeof(fire_color_list) / (sizeof(prog_int16_t) * 4));

PROGMEM prog_int16_t ocean_color_list[] = {
  0,1023,1023,2367,
  0,1023,0,2367,
  500,1023,0,2367,
  0,0,1023,2367,  
};

ColorList ocean_color(ocean_color_list,sizeof(ocean_color_list) / (sizeof(prog_int16_t) * 4));

PROGMEM prog_int16_t cruise_color_list[] = {
  1023,1023,0,2367,
  1023,1023,1023,2367,
  0,1023,1023,2367,
};

ColorList cruise_color(cruise_color_list,sizeof(cruise_color_list) / (sizeof(prog_int16_t) * 4));

PROGMEM prog_int16_t slow_red_list[] = {
  0,0,0,3187,
  0,0,0,3187,
  0,0,0,3187,
  1023,0,0,3187,
  1023,500,20,3187,
};

ColorList slow_red_color(slow_red_list,sizeof(slow_red_list) / (sizeof(prog_int16_t) * 4));

PROGMEM prog_int16_t flamey_purple_list[] = {
  1023,0,0,529,
  0,0,0,529,
  1023,0,529,
  
};

ColorList flamey_purple_color(flamey_purple_list,sizeof(flamey_purple_list) / (sizeof(prog_int16_t) * 4));

PROGMEM prog_int16_t rave_bow_list[] = {
  1023,0,0,11,
  0,1023,0,11,
  0,0,1023,11,  
};

ColorList rave_bow_color(rave_bow_list,sizeof(rave_bow_list) / (sizeof(prog_int16_t) * 4));

PROGMEM prog_int16_t glitter_list[] = {
  1023,0,0,11,
  0,0,0,1432,
  0,0,0,1432,
  0,0,0,1432,
  1023,600,0,11,
  0,0,0,1432,
  0,0,0,1432,
  0,0,0,1432,
  600,0,1023,11,  
  0,0,0,1432,
  0,0,0,1432,
  0,0,0,1432,
};

ColorList glitter_color(glitter_list,sizeof(glitter_list) / (sizeof(prog_int16_t) * 4));

PROGMEM prog_int16_t flash_list[] = {
  1023,1023,1023,1,
  0,0,0,1432,
  0,0,0,1432,
  0,0,0,1432,
};

ColorList flash_color(flash_list,sizeof(flash_list) / (sizeof(prog_int16_t) * 4));

PROGMEM prog_int16_t white_blink_list[] = {
  1023,1023,1023,100,
  0,0,0,100,
};

ColorList white_blink_color(white_blink_list,sizeof(white_blink_list) / (sizeof(prog_int16_t) * 4));


//ColorList listOfColorLists[] = {devilish_color,minty_color,fire_color,ocean_color,cruise_color,slow_red_color};
//ColorList listOfColorLists[] = {devilish_color,flamey_purple_color,fire_color,slow_red_color};
ColorList listOfColorLists[] = {fire_color,devilish_color,flamey_purple_color,flash_color};

//This is the object for the list of color lists.  
MasterColorList::MasterColorList(int numberOfColorLists,ColorList* listOfColorListsPointer){
    //This is how long it fades between color schemes
    transitionTime = 1000;
    //This keeps track of which color list we are on
    _currentList = 0;
    //This is the number of the last color list in the list of lists.
    _lastList = numberOfColorLists - 1;
    //This is the pointer to the list of lists.
    _listOfColorListsPointer = listOfColorListsPointer;
    //This is the total number of color lists.
    _numberOfColorLists = numberOfColorLists;
};

//This gets the current delay returned by the current list at address
int MasterColorList::getDelay(int address){
  return _listOfColorListsPointer[_currentList].getDelay(address);
};

//This gets the current delay returned by the previous list at address
int MasterColorList::getLastDelay(int address){
  return _listOfColorListsPointer[_lastList].getDelay(address);
};

//This moves to the next color list, also starting the fading loop
//The fading loop works by setting transitionBegan
int MasterColorList::incrementList(){
  _lastList = _currentList;
  _currentList++;
  if (_currentList >= _numberOfColorLists){
    _currentList = 0;
  }
  transitionBegan = millis();
  return _currentList;  
};

//This calculates how far along we are between color lists.
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

//This returns the color for the current list at address
Color MasterColorList::getCurrentColor(int address){
  return _listOfColorListsPointer[_currentList].getCurrentColor(address);
};

//This returns the color for the last list at address
Color MasterColorList::getLastColor(int address){
  return _listOfColorListsPointer[_currentList].getLastColor(address);
};

//This gest the number of elements in the current list
int MasterColorList::getNumberOfElements(){
  return _listOfColorListsPointer[_currentList].getNumberOfElements();
};

//This gets the current color at address for the last list in the masterlist list.
Color MasterColorList::getLastCurrentColor(int address){
  return _listOfColorListsPointer[_lastList].getCurrentColor(address);
};

//This gets the last color at address for the last list in the masterlist list.
Color MasterColorList::getLastLastColor(int address){
  return _listOfColorListsPointer[_lastList].getLastColor(address);
};

//This returns the number of elements in the previous color list.
int MasterColorList::getLastNumberOfElements(){
  return _listOfColorListsPointer[_lastList].getNumberOfElements();
};

//This is the master color list, encapsulated in the master color list object.
MasterColorList masterColorList(sizeof(listOfColorLists) / sizeof(ColorList),listOfColorLists);



