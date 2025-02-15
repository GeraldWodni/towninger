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
    SHOW_WIN;
    DISPLAY_ON;

    uint8_t my_tile = TILE_GRASS;
    uint8_t my_color = 0;
    uint8_t lock_button = 0;

    uint8_t bkg_x = SCROLL_X;
    uint8_t bkg_y = SCROLL_Y;

    uint8_t player_x = 3;
    uint8_t player_y = 3;

    /* background */
    set_bkg_palette( 0, 8, spritePalette );
    set_bkg_data( 0, NUMBER_OF_TILES, Tiles );
    fill_bkg_rect( 0, 0, BW, BH, my_tile );

    USE_COLOR_RAM;
    fill_bkg(0);
    USE_DATA_RAM;

    move_bkg( 0, 0 );
    drawText( 6, 5, "TOWNINGER" );
    drawText( 5, 7, "PRESS START" );

    set_tile_xy(1,2,TILE_PLAYER);
    set_tile_xy_color(1,2,TCOL(TILE_PLAYER));

    set_tile_xy_with_color(1,4,TILE_PLAYER);

    /* window */
    set_win_data(0, NUMBER_OF_TILES, Tiles);
    fill_win( TILE_PLAYER );

    USE_COLOR_RAM;
    fill_win( TCOL(TILE_PLAYER) );
    move_win(7,PH-WIN_PH);
    USE_DATA_RAM;

    
    /* start screen wait */
    waitpad(J_START);
    waitpadup();

    set_tile_xy(CX-1,CY-1,70);
    set_tile_xy(CX-1,CY  ,71);
    set_tile_xy(CX  ,CY-1,72);
    set_tile_xy(CX  ,CY  ,73);

    set_tile_xy( 0, 0,TILE_WATER_TOP_LEFT    );
    set_tile_xy( 0,MH,TILE_WATER_BOTTOM_LEFT );
    set_tile_xy(MW, 0,TILE_WATER_TOP_RIGHT   );
    set_tile_xy(MW,MH,TILE_WATER_BOTTOM_RIGHT);

    USE_COLOR_RAM;
    fill_bkg_rect(CX-1,CY-1,1,2, TCOL( TILE_CASTLE_LEFT ) );
    fill_bkg_rect(CX  ,CY-1,1,2, TCOL( TILE_CASTLE_RIGHT ) );
    set_tile_xy( 0, 0,TCOL(TILE_WATER_TOP_LEFT    ));
    set_tile_xy( 0,MH,TCOL(TILE_WATER_BOTTOM_LEFT ));
    set_tile_xy(MW, 0,TCOL(TILE_WATER_TOP_RIGHT   ));
    set_tile_xy(MW,MH,TCOL(TILE_WATER_BOTTOM_RIGHT));
    USE_DATA_RAM;

	while (1) {
		UINT8 buttons = joypad();
        if( buttons == 0 && lock_button )
            lock_button = 0;

        if( !lock_button ) {            
            switch( buttons ) {
                case J_LEFT:
                    if( bkg_x > 0 )
                        bkg_x--;
                break;
                case J_RIGHT:
                    if( bkg_x < SCROLL_W )
                        bkg_x++;
                break;
                case J_UP:
                    if( bkg_y > 0 )
                        bkg_y--;
                break;
                case J_DOWN:
                    if( bkg_y < SCROLL_H )
                        bkg_y++;
                break;
            }
            if( buttons == J_SELECT )
                break;
        }

        wait_vbl_done();
        move_bkg(bkg_x, bkg_y);
	}

	DISPLAY_OFF;
}