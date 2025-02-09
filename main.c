#define __PORT_sm83

#include <gb/gb.h>
#include <gb/cgb.h>
#include <rand.h>
#include "media/tiles.h"
#include "media/tiles.c"

#define NUMBER_OF_TILES 47
#define TILE_EMPTY 0
#define TILE_PLAYER 1
#define TILE_ROCKET 2
#define TILE_ENEMY 3
#define TILE_RAY 4
#define TILE_EXPLOSION 5
#define TILE_GRADIENT 6
#define TILE_STARFIELD 7
#define TILE_ASTROID 8
#define TILE_LIFE 9
#define TILE_ZERO 10
#define TILE_A 20
#define TILE_X 46

// 160x144 px = 20x18 tiles
#define PW 160
#define PH 144
#define TW 20
#define TH 18
#define BW 32
#define BH 32

// TileColor: https://stackoverflow.com/a/1489985
#define PASTER( X, Y ) X ## Y
#define EVALUATOR( X, Y ) PASTER( X, Y )
#define TCOL( X ) EVALUATOR( TilesCGB, X )

#define TARGET_BKG 0
#define TARGET_WIN 1

INT8 tileTarget = TARGET_BKG;
void setTile( INT8 x, INT8 y, UINT8 tile ) {
    unsigned char buffer[1] = { tile };
    if( tileTarget == TARGET_BKG )
        set_bkg_tiles( x, y, 1, 1, buffer );
    else
        set_win_tiles( x, y, 1, 1, buffer );
}

void setTiles( INT8 x, INT8 y, INT8 startTile, INT8 w ) {
    for( INT8 i = 0; i < w; i++ )
        setTile( x+i, y, startTile+i );
}

void setAllTiles( UINT8 tile ) {
    for( INT8 y = 0; y < TH; y++ )
        for( INT8 x = 0; x < BW; x++ )
            setTile( x, y, tile );
}

UINT16 spritePalette[] = {
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

void drawText( INT8 x, INT8 y, char *text ) {
    for (; *text != '\0'; text++){
        char c = *text;
        UINT8 tile = TILE_X;
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

void main() {
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    UINT8 my_tile = TILE_STARFIELD;
    UINT8 lock_button = 0;

    /* background */
    set_bkg_palette( 0, 8, spritePalette );
    set_bkg_data( 0, NUMBER_OF_TILES, Tiles );
    fill_bkg_rect( 0, 0, BW, BH, my_tile );

    set_tile_xy(1,2,3);

    move_bkg( 0, 0 );
    drawText( 6, 5, "TOWNINGER" );
    drawText( 5, 7, "PRESS START" );

	while (1) {
		UINT8 buttons = joypad();
        if( buttons == 0 && lock_button )
            lock_button = 0;

        if( !lock_button )
            switch( buttons ) {
                case J_LEFT:
                    if( my_tile > 0 )
                        fill_bkg_rect( 0, 0, BW, BH, --my_tile );
                    lock_button = 1;
                break;
                case J_RIGHT:
                    if( my_tile < NUMBER_OF_TILES-1 )
                        fill_bkg_rect( 0, 0, BW, BH, ++my_tile );
                    lock_button = 1;
                break;
            }
	}

	DISPLAY_OFF;
}