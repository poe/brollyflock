/* intercom.h */
/* brollyflock
   22 June 2011
   common file for interprocessor communication between the LED controller and
   the fire controller
*/

#ifndef intercom_h
#define intercom_h


#define BUTTONONE (13+64)
#define BUTTONTWO (7+64)
#define BUTTONTHREE (2+64)

void setup_serial();
void send_to_ledctl(int thing_to_send);
int listen_from_firectl(void);

#endif

