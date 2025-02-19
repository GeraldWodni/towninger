#ifndef FAST_BCD_H
#define FAST_BCD_H

#include <gb/bcd.h>

void bcd_incr_2d( BCD *value );
void bcd_incr_4d( BCD *value );

void bcd_decr_2d( BCD *value );
void bcd_decr_4d( BCD *value );

#endif
