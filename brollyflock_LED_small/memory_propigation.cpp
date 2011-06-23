#include "memory_propigation.h"

//Here is the flash ram for some propigation lists
//It contains the from brolly and the to brolly indexes, as well as a delay
//After each there is a wrapper object of type PropigationList that points to the list
//and contains inexes and so on.
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

PropigationList in_order(in_order_list,sizeof(in_order_list) / (sizeof(prog_int16_t) * 3));

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

PropigationList sync(sync_list,sizeof(sync_list) / (sizeof(prog_int16_t) * 3));

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

PropigationList reverse_order(reverse_order_list,sizeof(reverse_order_list) / (sizeof(prog_int16_t) * 3));

//Here is the master sequence list
PropigationList listOfLists[] = {reverse_order,in_order,sync};

//Here is the object wrapper for the master sequence list
MasterSequenceList masterSequenceList(sizeof(listOfLists) / sizeof(PropigationList),listOfLists);

//This is the propigation list object constructor.  It takes a pointer to the list in flash ram and a size
PropigationList::PropigationList(prog_int16_t* listPointer,  int sizeOfList){
  _listPointer = listPointer;
  _sizeOfList = sizeOfList;
};

//This returns the number of elements in the list, mostly for use in the master list
int PropigationList::getNumberOfElements(){
  return _sizeOfList;
};

//This gets the 'from' brolly in the propigation list
int PropigationList::getFrom(int address){
  return pgm_read_word_near(_listPointer + address * 3);
};

//This gets the 'to' brolly in the propigation list
int PropigationList::getTo(int address){
  int returnValue = pgm_read_word_near(_listPointer + address * 3 + 1);
  return returnValue;
};

//This gets the delay in the propigation list, they are recursively totalled when loaded into the brolly objects
int PropigationList::getDelay(int address){
  return pgm_read_word_near(_listPointer + address * 3 + 2);
};

//This is the object for the master sequence list.  It keeps track of what list we are using and the delay involved.
MasterSequenceList::MasterSequenceList(int numberOfListLists,PropigationList* listListPointer){
    _currentList = 0;
    _lastList = numberOfListLists - 1;
    _listListPointer = listListPointer;
    _numberOfListLists = numberOfListLists;
    transitionBegan = 0;
    transitionTime = 1000;
};

//This gets the number of elements in the current list
int MasterSequenceList::getNumberOfElements(){
  return _listListPointer[_currentList].getNumberOfElements();
};

//This gets the number of elements in the previous list
int MasterSequenceList::getLastNumberOfElements(){
  return _listListPointer[_lastList].getNumberOfElements();
};

//Move to the next list, wrapping around at the end.
int MasterSequenceList::incrementList(){
  _lastList = _currentList;
  _currentList++;
  if (_currentList > _numberOfListLists -1){
    _currentList = 0;
  }
  transitionBegan = millis();
  return _currentList;
};

//Get the 'from' brolly at address from the current list
int MasterSequenceList::getFrom(int address){
  return _listListPointer[_currentList].getFrom(address);
};

//Get the 'to' brolly at address from the current list
int MasterSequenceList::getTo(int address){
  return _listListPointer[_currentList].getTo(address);
};

//get the delay at address for the current list 
int MasterSequenceList::getDelay(int address){
  return _listListPointer[_currentList].getDelay(address);
};

//get the 'from' brolly at address from the previous list
int MasterSequenceList::getLastFrom(int address){
  return _listListPointer[_lastList].getFrom(address);
};

//get the 'to' brolly at address from the previous list
int MasterSequenceList::getLastTo(int address){
  return _listListPointer[_lastList].getTo(address);
};

//Get the delay from the previous list at address
int MasterSequenceList::getLastDelay(int address){
  return _listListPointer[_lastList].getDelay(address);
};

//This gives you how far along in time you are in the current sequence list transition
float MasterSequenceList::transitionRatio(){
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

//This gives you the total delay 
long MasterSequenceList::getTotalDelay(int address){
  for(int element = 0;element < getNumberOfElements();element++){
    if(getTo(element) == address){
      return getTotalDelay(getFrom(element)) + getDelay(address);
    };
  };
  return 0;
};

//Gets the total delay for the last list
long MasterSequenceList::getLastTotalDelay(int address){
  for(int element = 0;element < getLastNumberOfElements();element++){
    if(getLastTo(element) == address){
      return getLastTotalDelay(getLastFrom(element)) + getLastDelay(address);
    };
  };
  return 0;
};

//Averages the delay between previous list and this one
long MasterSequenceList::getAverageDelay(int address){
  if(transitionRatio() == 1){
    return getTotalDelay(address);
  }
  return getTotalDelay(address) * transitionRatio() + getLastTotalDelay(address) * (1 - transitionRatio());
};

