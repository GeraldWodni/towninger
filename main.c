#ifndef __PORT_sm83
#define __PORT_sm83
#endif

#include <gb/gb.h>
#include <gb/cgb.h>
#include <rand.h>

#include "graphics.h"

uint8_t animation_counter = 0;

uint8_t animation_water = 0;
uint8_t animation_mobs = 0;
uint8_t animation_mob_dir = 0;
void animations( void ){
    if( C_ANIM( C_4Hz, animation_counter ) ) {
        switch( animation_water ) {
            case 0:
                set_bkg_palette_entry( PAL_WATER, 1, TILE_WATER_HIGHLIGHT1 );
            break;
            case 1:
                set_bkg_palette_entry( PAL_WATER, 1, TPALCOL( PAL_WATER, 1 ) );
            break;
            case 2:
                set_bkg_palette_entry( PAL_WATER, 2, TILE_WATER_HIGHLIGHT2 );
            break;
            case 3:
                set_bkg_palette_entry( PAL_WATER, 2, TPALCOL( PAL_WATER, 2 ) );
            break;
        }
        animation_water = (++animation_water) & 0b11;
    }
    if( C_ANIM( C_60Hz, animation_counter )) {
        if( animation_mobs++ & 0b1 )
            set_bkg_palette_entry(PAL_MOB, 2, TILE_MOB_HIGHLIGHT);
        else
            set_bkg_palette_entry(PAL_MOB, 2, TPALCOL( PAL_MOB, 2 ));
    }
    if( C_ANIM( C_2Hz, animation_counter ) ) {
        if( animation_mob_dir++ & 0x01 ) {
            set_tile_xy_color(CX-3, CY-4, PAL_MOB);
            set_tile_xy_color(CX-3, CY+2, PAL_MOB);
        }
        else {
            set_tile_xy_color(CX-3, CY-4, PAL_MOB | OAMF_XFLIP);
            set_tile_xy_color(CX-3, CY+2, PAL_MOB | OAMF_XFLIP);
        }
    }
    animation_counter++;
}

void main(void) {
    SHOW_BKG;
    SHOW_SPRITES;
    SHOW_WIN;
    DISPLAY_ON;

    uint8_t my_tile = TILE_DEFAULT;
    uint8_t my_color = 0;
    uint8_t lock_button = 0;

    uint8_t bkg_x = SCROLL_X;
    uint8_t bkg_y = SCROLL_Y;
    BCD bcd_bkg_x; uint2bcd( SCROLL_X, &bcd_bkg_x );
    BCD bcd_bkg_y; uint2bcd( SCROLL_Y, &bcd_bkg_y );

    uint8_t player_x = 3;
    uint8_t player_y = 3;

    /* background */
    set_bkg_palette( 0, 8, spritePalette );
    set_bkg_data( 0, NUMBER_OF_TILES, Tiles );
    set_win_data( 0, NUMBER_OF_TILES, Tiles );
    fill_bkg_rect( 0, 0, BW, BH, my_tile );

    USE_COLOR_RAM;
    fill_bkg( TCOL(TILE_DEFAULT) );
    USE_DATA_RAM;

    move_bkg( 0, 0 );
    drawText( 6, 5, DrawBkg, "TOWNINGER" );
    drawText( 5, 7, DrawBkg, "PRESS START" );

    set_tile_xy(1,2,TILE_PLAYER);
    set_tile_xy_color(1,2,TCOL(TILE_PLAYER));

    set_tile_xy_with_color(1,4,TILE_PLAYER);

    /* window */
    set_win_data(0, NUMBER_OF_TILES, Tiles);
    fill_win( TILE_PLAYER );

    /* window text           01234567891123456789*/
    drawText(0, 0, DrawWin, "B XX YYY RDY WEN U R" );

    USE_COLOR_RAM;
    fill_win( PAL_TEXT );
    move_win(7,PH-WIN_PH);
    USE_DATA_RAM;

    
    /* start screen wait */
    waitpad(J_START);
    waitpadup();

    set_tile_map( 0, 0, BW, BH, TileMap );
    USE_COLOR_RAM;
    set_tile_map( 0, 0, BW, BH, TileMapPalettes );
    USE_DATA_RAM;

    set_tile_xy(CX-1,CY-1,70);
    set_tile_xy(CX-1,CY  ,71);
    set_tile_xy(CX  ,CY-1,72);
    set_tile_xy(CX  ,CY  ,73);

    set_tile_xy(CX-3, CY-4, TILE_MOB_0+0);
    set_tile_xy(CX-3, CY-2, TILE_MOB_0+1);
    set_tile_xy(CX-3, CY,   TILE_MOB_0+2);
    set_tile_xy(CX-3, CY+2, TILE_MOB_0+3);
    set_tile_xy(CX-3, CY+4, TILE_MOB_0+4);

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
    set_tile_xy(CX-3, CY-4, PAL_MOB);
    set_tile_xy(CX-3, CY-2, PAL_MOB);
    set_tile_xy(CX-3, CY,   PAL_MOB);
    set_tile_xy(CX-3, CY+2, PAL_MOB);
    set_tile_xy(CX-3, CY+4, PAL_MOB);
    USE_DATA_RAM;

	while(1) {
		uint8_t buttons = joypad();
        if( buttons == 0 && lock_button )
            lock_button = 0;

        if( !lock_button ) {            
            if( buttons & J_LEFT ) {
                if( bkg_x > 0 ) {
                    bkg_x--;
                    bcd_decr_2d( &bcd_bkg_x );
                }
            }
            else if( buttons & J_RIGHT ) {
                if( bkg_x < SCROLL_W ) {
                    bkg_x++;
                    bcd_incr_2d( &bcd_bkg_x );
                }
            }
            if( buttons & J_UP ) {
                if( bkg_y > 0 ) {
                    bkg_y--;
                    bcd_decr_4d( &bcd_bkg_y );
                }
            } else if( buttons & J_DOWN ) {
                if( bkg_y < SCROLL_H ) {
                    bkg_y++;
                    bcd_incr_4d( &bcd_bkg_y );
                }
            }
            if( buttons == J_SELECT )
                break;
        }

        wait_vbl_done();
        animations();
        move_bkg(bkg_x, bkg_y);

        drawBcdRightAligned( 2, 0, 2, &bcd_bkg_x );
        drawBcdRightAligned( 5, 0, 3, &bcd_bkg_y );
	}

	DISPLAY_OFF;
}
