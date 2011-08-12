#include "WProgram.h"
#include "brollyflock_data.h"
#include "brollyflock_color.h"

int test_int;

Step colorScheme[] = {
                      Step(Color(0,0,1023),5000),Step(Color(0,1023,0),5000),
                      Step(Color(0,0,1023),5000),Step(Color(0,1023,0),5000),
                      Step(Color(0,0,1023),5000),Step(Color(0,1023,0),5000),
                      };
                      
int colorSteps = sizeof(colorScheme)/sizeof(Step);

/*                      
Direction firstShow[PropigationSteps] = {
                         Direction(0,1,100),
                         Direction(1,2,100),
                         Direction(2,3,100),
                         Direction(3,4,100),
                         Direction(4,5,100),
                         Direction(5,6,100),
                         Direction(6,7,100),
                         Direction(7,8,100),
                         Direction(8,9,100),
                         Direction(9,10,100),
                         Direction(10,11,100),
                         Direction(11,12,100),
                         Direction(12,13,100),
                         Direction(13,14,100),
                         Direction(14,15,100),
                         Direction(15,16,100),
                         Direction(16,17,100),
                         Direction(17,18,100),
                         Direction(18,19,100),
                         Direction(19,20,100),
                         Direction(20,21,100),
                         Direction(21,22,100),
                         Direction(22,23,100),
                         Direction(23,24,100),
                         Direction(24,25,100),
                         Direction(25,26,100),
                         Direction(26,27,100),
                         Direction(27,28,100),
                         Direction(28,29,100),
                         Direction(29,30,100),
                         Direction(30,31,100),
                         Direction(31,32,100),
                         Direction(32,33,100),
                         Direction(33,34,100),
                         Direction(34,35,100),
                         Direction(35,36,100),
                         Direction(36,37,100),
                         Direction(37,38,100),
                         Direction(38,39,100),
                         Direction(39,40,100),
                         Direction(40,41,100),
                         Direction(41,42,100),
                         Direction(42,43,100),
                         Direction(43,44,100),
                         Direction(44,45,100),
                         Direction(45,46,100),
                         Direction(46,47,100),
                        };
*/

