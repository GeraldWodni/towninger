#include "graphics.h"

#include "media/tiles_medieval.c"
#include "media/tilemap.c"

const uint16_t spritePalette[] = {
    /* 0 3 2 1 */
    TilesCGBPal0c0, TilesCGBPal0c1, TilesCGBPal0c2, TilesCGBPal0c3,
    TilesCGBPal1c0, TilesCGBPal1c1, TilesCGBPal1c2, TilesCGBPal1c3,
    TilesCGBPal2c0, TilesCGBPal2c1, TilesCGBPal2c2, TilesCGBPal2c3,
    TilesCGBPal3c0, TilesCGBPal3c1, TilesCGBPal3c2, TilesCGBPal3c3,
    TilesCGBPal4c0, TilesCGBPal4c1, TilesCGBPal4c2, TilesCGBPal4c3,
    TilesCGBPal5c0, TilesCGBPal5c1, TilesCGBPal5c2, TilesCGBPal5c3,
    TilesCGBPal6c0, TilesCGBPal6c1, TilesCGBPal6c2, TilesCGBPal6c3,
    TilesCGBPal7c0, TilesCGBPal7c1, TilesCGBPal7c2, TilesCGBPal7c3
};

void fill_bkg( uint8_t tile ) {
    fill_bkg_rect( 0, 0, BW, BH, tile );
}

void fill_win( uint8_t tile ) {
    fill_win_rect( 0, 0, BW, BH, tile );
}

void drawBcdRightAligned( uint8_t x, const uint8_t y, const uint8_t w, const BCD *value ) {
    uint8_t i = sizeof(BCD) - w;
    x += w - 1;
    for ( i = 0; i < w; i++ ){
        unsigned char c = ((unsigned char *) value)[i>>1];
        if( i & 0x01 )
            c >>= 4;
        else
            c &= 0x0F;
        uint8_t tile = TILE_ZERO + c;
        set_win_tile_xy( x--, y, tile );
    }
}

void drawText( uint8_t x, const uint8_t y, drawTarget target, const unsigned char *text ) {
    for (; *text != '\0'; text++){
        unsigned char c = *text;
        uint8_t tile = TILE_EMPTY;
        if( c == ' ' )
            tile = TILE_GRASS;
        else if( '0' <= c && c <= '9' )
            tile = TILE_ZERO + (c-'0');
        else if( 'A' <= c && c <= 'Z')
            tile = TILE_A + (c-'A');

        if( target == DrawBkg )
            set_bkg_tile_xy( x++, y, tile );
        else
            set_win_tile_xy( x++, y, tile );
    }
}
