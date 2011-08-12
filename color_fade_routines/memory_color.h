#include "WProgram.h"
#ifndef memory_color_h
#define memory_color_h
#include <avr/pgmspace.h>

class Color {
   public:
     Color();
     Color(int red_in, int green_in, int blue_in);
     Color progressColor(Color oldColor, Color newColor, float fraction);
     int getRed();
     int getGreen();
     int getBlue();
   private:
     int red;
     int green;
     int blue;
};

class ColorList{
  friend class Color;
  public:
    ColorList(prog_int16_t* listPointer,  int sizeOfList);
    Color getLastColor(int address);
    Color getCurrentColor(int address);
    Color getNextColor(int address);
    int getDelay(int address);
    int numberOfElements();
    int decrementAddress(int address);
    int incrementAddress(int address);
  private:
    int currentColor;
    prog_int16_t* _listPointer;
    int _sizeOfList;
};

class MasterColorList{
  public:
    MasterColorList(int numberOfLists,ColorList* listListPointer);
    int incrementList();
    Color getCurrentColor(int address);
    Color getLastColor(int address);
    Color getNextColor(int address);
    int getDelay(int address);
    int numberOfElements();
  private:
    ColorList* _listOfColorListsPointer;
    int _currentList;
    int _numberOfColorLists;
};

extern PROGMEM prog_int16_t devilish_color_list[];

extern ColorList devilish_color;

extern PROGMEM prog_int16_t minty_color_list[];

extern ColorList minty_color;

extern PROGMEM prog_int16_t fire_color_list[];

extern ColorList fire_color;

extern PROGMEM prog_int16_t ocean_color_list[];

extern ColorList ocean_color;

extern PROGMEM prog_int16_t cruise_color_list[];

extern ColorList cruise_color;

extern prog_int16_t in_order_list[];

extern ColorList listOfColorLists[];

extern MasterColorList masterColorList;

#endif
