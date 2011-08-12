#include <avr/pgmspace.h>
#include "memory_propigation.h"

PROGMEM prog_int16_t in_order_list[] = {
   0,1,100,
   1,2,100,
   2,3,100,
   3,4,100,
   4,5,100,
   5,6,100,
   6,7,100,
   7,8,100,
   8,9,100,
   9,10,100,
   10,11,100,
   11,12,100,
   12,13,100,
   13,14,100,
   14,15,100,
   15,16,100,
   16,17,100,
   17,18,100,
   18,19,100,
   19,20,100,
   20,21,100,
   21,22,100,
   22,23,100,
   23,24,100,
   24,25,100,
   25,26,100,
   26,27,100,
   27,28,100,
   28,29,100,
   29,30,100,
   30,31,100,
   31,32,100,
   32,33,100,
   33,34,100,
   34,35,100,
   35,36,100,
   36,37,100,
   37,38,100,
   38,39,100,
   39,40,100,
   40,41,100,
   41,42,100,
   42,43,100,
   43,44,100,
   44,45,100,
   45,46,100,
   46,47,100,
};

PROGMEM prog_int16_t sync_list[] = {
   0,1,1,
   1,2,1,
   2,3,1,
   3,4,1,
   4,5,1,
   5,6,1,
   6,7,1,
   7,8,1,
   8,9,1,
   9,10,1,
   10,11,1,
   11,12,1,
   12,13,1,
   13,14,1,
   14,15,1,
   15,16,1,
   16,17,1,
   17,18,1,
   18,19,1,
   19,20,1,
   20,21,1,
   21,22,1,
   22,23,1,
   23,24,1,
   24,25,1,
   25,26,1,
   26,27,1,
   27,28,1,
   28,29,1,
   29,30,1,
   30,31,1,
   31,32,1,
   32,33,1,
   33,34,1,
   34,35,1,
   35,36,1,
   36,37,1,
   37,38,1,
   38,39,1,
   39,40,1,
   40,41,1,
   41,42,1,
   42,43,1,
   43,44,1,
   44,45,1,
   45,46,1,
   46,47,1,
};

PROGMEM prog_int16_t reverse_order_list[] = {
   47,46,100,
   46,45,100,
   45,44,100,
   44,43,100,
   43,42,100,
   42,41,100,
   41,40,100,
   40,39,100,
   39,38,100,
   38,37,100,
   37,36,100,
   36,35,100,
   35,34,100,
   34,33,100,
   33,32,100,
   32,31,100,
   31,30,100,
   30,29,100,
   29,28,100,
   28,27,100,
   27,26,100,
   26,25,100,
   25,24,100,
   24,23,100,
   23,22,100,
   22,21,100,
   21,20,100,
   20,19,100,
   19,18,100,
   18,17,100,
   17,16,100,
   16,15,100,
   15,14,100,
   14,13,100,
   13,12,100,
   12,11,100,
   11,10,100,
   10,9,100,
   9,8,100,
   8,7,100,
   7,6,100,
   6,5,100,
   5,4,100,
   4,3,100,
   3,2,100,
   2,1,100,
   1,0,100,
};

PropigationList in_order(in_order_list,sizeof(in_order_list) / (sizeof(prog_int16_t) * 3));

PropigationList reverse_order(reverse_order_list,sizeof(reverse_order_list) / (sizeof(prog_int16_t) * 3));

PropigationList sync(sync_list,sizeof(sync_list) / (sizeof(prog_int16_t) * 3));

PropigationList listOfLists[] = {reverse_order,in_order,sync};

MasterList masterList(sizeof(listOfLists) / sizeof(PropigationList),listOfLists);

PropigationList::PropigationList(prog_int16_t* listPointer,  int sizeOfList){
  _listPointer = listPointer;
  _sizeOfList = sizeOfList;
};

int PropigationList::getNumberOfElements(){
  return _sizeOfList;
};

int PropigationList::getFrom(int address){
  if (address != address % _sizeOfList){
    address = address % _sizeOfList;
    Serial.println("address looped in From");
  }
  return pgm_read_word_near(_listPointer + address * 3);
};

int PropigationList::getTo(int address){
  if (address != address % _sizeOfList){
    address = address % _sizeOfList;
    Serial.println("address looped in To");
  }
  return pgm_read_word_near(_listPointer + address * 3 + 1);
};

int PropigationList::getDelay(int address){
  if (address != address % _sizeOfList){
    address = address % _sizeOfList;
    Serial.println("address looped in Delay");
  }
  return pgm_read_word_near(_listPointer + address * 3 + 2);
};

MasterList::MasterList(int numberOfListLists,PropigationList* listListPointer){
    _currentList = 0;
    _listListPointer = listListPointer;
    _numberOfListLists = numberOfListLists;
};

int MasterList::getNumberOfElements(){
  return _listListPointer[_currentList].getNumberOfElements();
};

int MasterList::incrementList(){
  _currentList++;
  if (_currentList >= _numberOfListLists){
    _currentList = 0;
  }  
}

int MasterList::getFrom(int address){
  _listListPointer[_currentList].getFrom(address);
};

int MasterList::getTo(int address){
  _listListPointer[_currentList].getTo(address);
};

int MasterList::getDelay(int address){
  _listListPointer[_currentList].getDelay(address);
};



