//All arduino libs require this
#include "WProgram.h"

//make sure it isn't included more than once.
#ifndef memory_propigation_h
#define memory_propigation_h
//This is the flash ram access lib
#include <avr/pgmspace.h>

//This is the propigation list wrapper class.  It has pointers to the propigation list array and data about it.
class PropigationList{
  public:
    PropigationList(prog_int16_t* listPointer,  int sizeOfList);
    int getFrom(int address);
    int getTo(int address);
    int getDelay(int address);
    int getNumberOfElements();
  private:
    prog_int16_t* _listPointer;
    int _sizeOfList;
};

//Here is the class for the master sequence list
class MasterSequenceList{
  public:
    //Constructor
    MasterSequenceList(int numberOfLists,PropigationList* listListPointer);
    
    //This moves to the next sequence
    int incrementList();
    
    //Here we get values from the current list at address
    int getFrom(int address);
    int getTo(int address);
    int getDelay(int address);
    long getTotalDelay(int address);
    //this is the number of elements in the current list
    int getNumberOfElements();
    
    //Here we get values from the last list at address
    int getLastFrom(int address);
    int getLastTo(int address);
    int getLastDelay(int address);    
    long getLastTotalDelay(int address);
    //This is the number of elements from the previous list
    int getLastNumberOfElements();
    
    //This returns the average between last and current list delays at address
    long getAverageDelay(int address);
    
    //This returns a float between 0 and 1 representing how far along the current transition we are
    float transitionRatio();
    
  private:
    //This is the time the current list transition began.
    long transitionBegan;
    //This is the time we have been in the transition between lists
    long transitionTime;
    
    //This points to the array of lists
    PropigationList* _listListPointer;
    
    //These keep track of the last and current list
    int _lastList;
    int _currentList;
    
    //This is the total number of lists
    int _numberOfListLists;
};

//Here are some flash ram variables for various propigation delay lists
//Note that they are all wrapped in a PropigationList object.
extern PROGMEM prog_int16_t in_order_list[];

extern PropigationList in_order;

extern PROGMEM prog_int16_t sync_list[];

extern PropigationList sync;

extern PROGMEM prog_int16_t reverse_order_list[];

extern PropigationList reverse_order;

//This is the master list of sequence lists, also wrapped in an object.
extern PropigationList listOfLists[];

extern MasterSequenceList masterSequenceList;

#endif
