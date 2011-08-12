/* _3waySystem.pde */
/* brollyflock
   adapted from earlier, serial sending stuff now added
*/

#include "intercom.h"

#define DWELL_TIME  1000

#define NUMSEQUENCES 3
#define NUMEVENTS 3

//#define POTPIN 2
int button8= 8;
int button9= 9;
int button10= 10;
int val=0;
int relayPin2 = 2;   // lamp on button8
int relayPin3 = 3;   // lamp on button9
int relayPin4 = 4;   // lamp on button10
int relayPin5 = 5;
int relayPin6 = 6;
int relayPin7 = 7;

void buttons_dark(void) {
    digitalWrite(relayPin2, LOW);  // button lamp
    digitalWrite(relayPin3, LOW);  // button lamp
    digitalWrite(relayPin4, LOW);   // button lamp
}

void buttons_light(void) {
    digitalWrite(relayPin2, HIGH);  // button lamp
    digitalWrite(relayPin3, HIGH);  // button lamp
    digitalWrite(relayPin4, HIGH);  // button lamp
}

void set_valves(int v1, int v2, int v3) {
  if (v1 == 1)
    digitalWrite(relayPin5, HIGH); // fire
  else
    digitalWrite(relayPin5, LOW);

  if (v2 == 1)
    digitalWrite(relayPin6, HIGH); // fire
  else
    digitalWrite(relayPin6, LOW);

  if (v3 == 1)
    digitalWrite(relayPin7, HIGH); // fire
  else
    digitalWrite(relayPin7, LOW);

}

class s_fire_event_t {
  public:
    s_fire_event_t();
    s_fire_event_t(int in_valve1,int in_valve2,int in_valve3,int in_dwell);
    int valve1;
    int valve2;
    int valve3;
    int dwell;
}; 

s_fire_event_t::s_fire_event_t(){
};

s_fire_event_t::s_fire_event_t(int in_valve1,int in_valve2,int in_valve3,int in_dwell){
  valve1 = in_valve1;
  valve2 = in_valve2;
  valve3 = in_valve3;
  dwell  = in_dwell;
};

s_fire_event_t seq_array[NUMEVENTS][NUMSEQUENCES] = {{s_fire_event_t(1, 0, 0, 200),
                                                     s_fire_event_t(0, 1, 0, 200),
                                                     s_fire_event_t(0, 0, 1, 100)},

                                                     {s_fire_event_t(0, 0, 1, 200),
                                                     s_fire_event_t(0, 1, 0, 200),
                                                     s_fire_event_t(1, 0, 0, 100)},

                                                     {s_fire_event_t(1, 1, 0, 200),
                                                     s_fire_event_t(1, 1, 0, 1000),
                                                     s_fire_event_t(0, 0, 1, 100)}};


void play_sequence(int sequence) {
   int event = 0;
   int v1, v2, v3 = 0;
   
   if (sequence > NUMSEQUENCES - 1)
      return;

   for (event = 0; event < NUMEVENTS; event++) {
      v1 = seq_array[sequence][event].valve1;
      v2 = seq_array[sequence][event].valve2;
      v3 = seq_array[sequence][event].valve3;

      set_valves(v1, v2, v3);
      delay(seq_array[sequence][event].dwell);
   }

   set_valves(0, 0, 0);
}


void setup() {
  pinMode(relayPin2, OUTPUT);  // declare the relay as an OUTPUT
  pinMode(relayPin3, OUTPUT);  
  pinMode(relayPin4, OUTPUT);  
  pinMode(relayPin5, OUTPUT);  
  pinMode(relayPin6, OUTPUT);  
  pinMode(relayPin7, OUTPUT);
  pinMode(button8, INPUT);
  pinMode(button9, INPUT);
  pinMode(button10, INPUT);  

  set_valves(0, 0, 0);
  setup_serial();
  buttons_light();
}

void loop() {
  //val = analogRead(button0);

  if(digitalRead(button8) == HIGH){
    buttons_dark();
// no longer use direct write to valves
//    digitalWrite(relayPin5, HIGH); // fire
    send_to_ledctl(BUTTONONE);
    play_sequence(0);

    delay(1000);

    buttons_light();
// no longer use direct write to valves
//    digitalWrite(relayPin5, LOW);  // fire
  }
  
  else if(digitalRead(button9) == HIGH){
    buttons_dark();
// no longer use direct write to valves
//    digitalWrite(relayPin6, HIGH);  // fire
    send_to_ledctl(BUTTONTWO);
    play_sequence(1);

    delay(1000);

    buttons_light();
// no longer use direct write to valves
//    digitalWrite(relayPin6, LOW);  // fire
  }
  else if(digitalRead(button10) == HIGH){
    buttons_dark();
// no longer use direct write to valves
//    digitalWrite(relayPin7, HIGH);   // fire
    send_to_ledctl(BUTTONTHREE);
    play_sequence(2);

    delay(1000);

    buttons_light();
// no longer use direct write to valves
//    digitalWrite(relayPin7, LOW);   // fire
  }


} 

