#ifndef GMK_SYSTIME_H_
#define GMK_SYSTIME_H_

#include <avr/io.h>

/* Systime represent a system timestamp in ms
 */
typedef uint16_t Systime_t;

/* InitSystime initialiazes the Systime module. A module that provide
 * a realtime clock of 1ms ticks
 */
void InitSystime();


/* GetSystime return the ticksin ms since initialization modulo
   0xffff. Can only be used to measure relative time of less than
   65,635 seconds */
Systime_t GetSystime();



#endif //GMK_SYSTIME_H_
