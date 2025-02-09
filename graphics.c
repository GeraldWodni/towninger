#include "graphics.h"

#include "media/tiles.c"

uint8_t tileTarget = TARGET_BKG;

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

void setTile( uint8_t x, uint8_t y, uint8_t tile ) {
    unsigned char buffer[1] = { tile };
    if( tileTarget == TARGET_BKG )
        set_bkg_tiles( x, y, 1, 1, buffer );
    else
        set_win_tiles( x, y, 1, 1, buffer );
}

void setTiles( uint8_t x, uint8_t y, uint8_t startTile, uint8_t w ) {
    for( uint8_t i = 0; i < w; i++ )
        setTile( x+i, y, startTile+i );
}

void setAllTiles( uint8_t tile ) {
    for( uint8_t y = 0; y < TH; y++ )
        for( uint8_t x = 0; x < BW; x++ )
            setTile( x, y, tile );
}

void drawText( uint8_t x, uint8_t y, const unsigned char *text ) {
    for (; *text != '\0'; text++){
        unsigned char c = *text;
        uint8_t tile = TILE_X;
        if( c == ' ' )
            tile = TILE_EMPTY;
        else if( '0' <= c && c <= '9' )
            tile = TILE_ZERO + (c-'0');
        else if( 'A' <= c && c <= 'Z')
            tile = TILE_A + (c-'A');
        else if( c == 'a' )
            tile = TILE_ASTROID;

        setTile( x++, y, tile );
    }
}
