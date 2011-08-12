#include "WProgram.h"
#ifndef memory_color_h
#define memory_color_h
#include <avr/pgmspace.h>

//This is the class that wraps up colors, prints them and moves a fraction of 1 from one color to another. 
//At the end of the day these are stored mostly in flash or the LED array, but they are encapsulated here.

class Color {
   public:
     Color();
     Color(int red_in, int green_in, int blue_in);
     Color progressColor(Color oldColor, Color newColor, float fraction);
     void printColor();
     int getRed();
     int getGreen();
     int getBlue();
   private:
     int red;
     int green;
     int blue;
};

//This is the class that wraps up an array of colors and the delays between each color.  
//Note that it accesses the flash ram directly, so some of the data cannot be written to.  
class ColorList{
  friend class Color;
  public:
    //Here is the constructor, taking values for flash ram access
    ColorList(prog_int16_t* listPointer,  int sizeOfList);

    //These are the routines that retrieve colors by address
    Color getLastColor(int address);
    Color getCurrentColor(int address);
    Color getNextColor(int address);

    //Gets the delay for a given color in the list at address
    int getDelay(int address);
    //Get the number of elements in this list
    int getNumberOfElements();
    //subtract one from the input, looping around at zero
    int decrementAddress(int address);
    //add one to the input, looping around at the size of the list
    int incrementAddress(int address);
    //This is the total time in the list
    unsigned long totalTime;
  private:
    //This is where we currently are in the list
    int currentColor;
    //A pointer to the list in flash ram
    prog_int16_t* _listPointer;
    //the size of this list
    int _sizeOfList;
};

class MasterColorList{
  public:
    //Master list constructor, taking the pointer to it in flash and the size.
    MasterColorList(int numberOfLists,ColorList* listListPointer);
    //Move to the next list of colors
    int incrementList();
    //Get the color at address in the current list
    Color getCurrentColor(int address);
    //Get the previous color in the list
    Color getLastColor(int address);
    
    //Get the color offset by the delay time (over the whole current list)
    Color getColorNow(int delayTime);
    //Get the color offset by the delay time (over the whole previous list)
    Color getLastColorNow(int delayTime);
    
    //Get a smoothed average of getColorNow and getLastColorNow
    Color getSmoothColorNow(int delayTime);
    
    //This returns the delay for a given address in the current list
    int getDelay(int address);
    
    //Get the number of elements in the current list
    int getNumberOfElements();

    //This gives you how far into the transition between color lists you are
    float transitionRatio();
    
    long getAverageTotalTime();
    
    //This gives you the total time in the current list
    long getTotalTime();
    
    //Get the number of elements in the current list    
    int getLastNumberOfElements();
    
    //Get the previous color in the previous list
    Color getLastLastColor(int address);
    
    //Get the current color in the previous list
    Color getLastCurrentColor(int address); 
    
    //Get the delay at address in the previous list
    int getLastDelay(int address);
    
    //Get the total time in the previous list
    long getLastTotalTime();

  private:
    //The time at which the transition began
    long transitionBegan;
    //The time we have been in this transition
    long transitionTime;
    //This is a pointer to the array of lists
    ColorList* _listOfColorListsPointer;
    //The number of the last list
    int _lastList;
    //The number of the current list
    int _currentList;
    //The number of color lists in the master list
    int _numberOfColorLists;
};

//Here are a bunch of arrays of pointers to locations in flash ram
//These locations contain various color lists which are associated with 
//objects of type ColorList
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

//Here is the master list

extern ColorList listOfColorLists[];

extern MasterColorList masterColorList;

#endif
