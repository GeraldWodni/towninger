#include "fast_bcd.h"

void bcd_incr_uint8( uint8_t *value ) {
    if( (value[0] & 0x0F) == 9 )
        value[0] = (value[0] & 0xF0) + 0x10;
    else
        value[0]+= 1;
}
void bcd_incr_2d( BCD *v ) {
    uint8_t *value = (uint8_t *)v;
    bcd_incr_uint8( value );
}
void bcd_incr_4d( BCD *v ) {
    bcd_incr_2d(v);
    uint8_t *value = (uint8_t *)v;
    if( value[0] == 0xA0 ) { /* carry? */
        value[0] = 0x00;
        bcd_incr_uint8( &(value[1]) );
    }
}

void bcd_decr_uint8( uint8_t *value ) {
    if( (value[0] & 0x0F) == 0 )
        value[0]= (value[0] - 0x10) | 0x09;
    else
        value[0]-= 1;
}
void bcd_decr_2d( BCD *v ) {
    bcd_decr_uint8( (uint8_t *)v );
}
void bcd_decr_4d( BCD *v ) {
    bcd_decr_2d(v);
    uint8_t *value = (uint8_t *)v;
    if( value[0] == 0xF9 ) { /* carry? */
        value[0] = 0x99;
        bcd_decr_uint8( &(value[1]) );
    }
}

