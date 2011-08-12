#include "WProgram.h"
#ifndef memory_propigation_h
#define memory_propigation_h
#include <avr/pgmspace.h>

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

class MasterList{
  public:
    MasterList(int numberOfLists,PropigationList* listListPointer);
    int incrementList();
    int getFrom(int address);
    int getTo(int address);
    int getDelay(int address);
    int getNumberOfElements();
  private:
    PropigationList* _listListPointer;
    int _currentList;
    int _numberOfListLists;
};

extern prog_int16_t in_order_list[];

extern PROGMEM prog_int16_t sync_list[];

extern PropigationList in_order;

extern PropigationList reverse_order;

extern PropigationList sync;

extern PropigationList listOfLists[];

extern MasterList masterList;

#endif
