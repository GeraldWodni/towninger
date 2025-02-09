#ifndef __PORT_sm83
#define __PORT_sm83
#endif

#include <gb/gb.h>
#include <gb/cgb.h>
#include <rand.h>

#include "graphics.h"

void main(void) {
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    uint8_t my_tile = TILE_STARFIELD;
    uint8_t my_color = 0;
    uint8_t lock_button = 0;

    /* background */
    set_bkg_palette( 0, 8, spritePalette );
    set_bkg_data( 0, NUMBER_OF_TILES, Tiles );
    fill_bkg_rect( 0, 0, BW, BH, my_tile );
    //set_bkg_

    move_bkg( 0, 0 );
    drawText( 6, 5, "TOWNINGER" );
    drawText( 5, 7, "PRESS START" );

    set_tile_xy(1,2,3);

    waitpad(J_START);
    waitpadup();

	while (1) {
		UINT8 buttons = joypad();
        if( buttons == 0 && lock_button )
            lock_button = 0;

        if( !lock_button ) {            
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
                case J_UP:
                    if( my_color < 8-1 ) {
                        VBK_REG=1;
                        setAllTiles(++my_color);
                        VBK_REG=0;
                    }
                    lock_button = 1;
                break;
                case J_DOWN:
                    if( my_color > 0 ) {
                        VBK_REG=1;
                        setAllTiles(--my_color);
                        VBK_REG=0;
                    }
                    lock_button = 1;
                break;
            }
            if( buttons == J_SELECT )
                break;
        }
	}

	DISPLAY_OFF;
}