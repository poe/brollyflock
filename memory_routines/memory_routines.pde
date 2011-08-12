#include <avr/pgmspace.h>

PROGMEM prog_uint16_t in_order_list[] = {
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

PROGMEM prog_uint16_t reverse_order_list[] = {
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

prog_uint16_t* listOfLists[] = {in_order_list,reverse_order_list};

class propigationList{
  void nextList();
  int currentList();
  int getFrom(int address);
  int getTo(int address);
  int getDelay(int address);
  int sizeOfList;
};

void setup()			  
{
  Serial.begin(9600);
}


void loop()			  
{
  unsigned int from;
  unsigned int to;
  unsigned int delayMove;  
   
  for (int i = 0; i < sizeof(in_order_list) / sizeof(prog_uint16_t); i+=3){
    Serial.print(" i = ");
    Serial.print(i);
    
    from = pgm_read_word_near(in_order_list + i);
    Serial.print(" from = ");
    Serial.print(from);

    to = pgm_read_word_near(in_order_list + i + 1);
    Serial.print(" to = ");
    Serial.print(to);

    delayMove = pgm_read_word_near(in_order_list + i + 2);
    Serial.print(" delayMove = ");
    Serial.print(delayMove);
    
    Serial.println("");
  }

  Serial.println("");
  Serial.println(" loop ");
  Serial.println("");
}

