#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <gb/gb.h>

/* adopt to tileset in use */
#include "media/tiles_medieval.h"
#include "media/tilemap.h"
#define NUMBER_OF_TILES 90

// 160x144 px = 20x18 tiles
#define WIN_TH 1    /* window size */
#define WIN_PH (WIN_TH*8)

#define PW 160  /* pixel dimensions */
#define PH 144
#define TW 20   /* tile dimensions */
#define TH 18
#define BW 32   /* back dimensions */
#define BH 32
#define CX (BW/2) /* center */
#define CY (BH/2)
#define MW (BW-1) /* maximum dimensions for calulations */
#define MH (BH-1)
#define TPW (BW*8) /* Tile pixel width */
#define TPH (BH*8)
#define SCROLL_W (TPW-PW) /* scrolling */
#define SCROLL_H (TPH-PH + WIN_PH) 
#define SCROLL_MW (SCROLL_W-1) /* maximum scrolling */
#define SCROLL_MH (SCROLL_H-1)
#define SCROLL_X (SCROLL_MW/2)
#define SCROLL_Y (SCROLL_MH/2)

// Tile settings
#define TILE_EMPTY 9
#define TILE_PLAYER 50
#define TILE_FIREBALL 51
#define TILE_ENEMY_BRUTE 63
#define TILE_EXPLOSION 52
#define TILE_GRASS 0
#define TILE_ZERO 10
#define TILE_A 20

#define TILE_CASTLE_LEFT 70
#define TILE_CASTLE_RIGHT 72

#define TILE_WATER 1
#define TILE_WATER_TOP_LEFT 2
#define TILE_WATER_BOTTOM_LEFT 3
#define TILE_WATER_TOP_RIGHT 4
#define TILE_WATER_BOTTOM_RIGHT 5

#define TILE_MOB_0 60
#define TILE_MOBS 5

/* Tile animation colors */
#define TILE_WATER_HIGHLIGHT1 RGB( 0, 16, 28)
#define TILE_WATER_HIGHLIGHT2 RGB( 0, 25, 31)
#define TILE_MOB_HIGHLIGHT RGB( 31, 7, 16 )

#define TILE_DEFAULT TILE_WATER

// TileColor: https://stackoverflow.com/a/1489985
#define PASTER( X, Y ) X ## Y
#define EVALUATOR( X, Y ) PASTER( X, Y )
#define TCOL( X ) EVALUATOR( TilesCGB, X )

#define PASTER4( W, X, Y, Z ) W ## X ## Y ## Z
#define EVALUATOR4( W, X, Y, Z ) PASTER4( W, X, Y, Z )
#define TPALCOL( X, I ) EVALUATOR4( TilesCGBPal, X, c, I ) 

/* palettes */
#define PAL_WATER TCOL(TILE_WATER_TOP_LEFT)
#define PAL_MOB   TCOL(TILE_MOB_0)

#define TARGET_BKG 0
#define TARGET_WIN 1

/* animations */
#define C_MASK( N ) ( (1<<N) | ((1<<N)-1) )
#define C_60Hz C_MASK( 0 )
#define C_30Hz C_MASK( 1 )
#define C_15Hz C_MASK( 2 )
#define C_7Hz  C_MASK( 3 )
#define C_4Hz  C_MASK( 4 )
#define C_2Hz  C_MASK( 5 )
#define C_1Hz  C_MASK( 6 )
#define C_05Hz C_MASK( 7 )
#define C_ANIM( C, N ) (C & N) == C

// convenience macros
#define USE_COLOR_RAM VBK_REG=1
#define USE_DATA_RAM VBK_REG=0

#define set_tile_xy_color(x,y,color) USE_COLOR_RAM; set_tile_xy(x, y, color); USE_DATA_RAM
#define set_tile_xy_with_color(x,y,tile) set_tile_xy(x,y,tile); set_tile_xy_color(x,y,TCOL(tile))

void setTile( uint8_t x, uint8_t y, uint8_t tile );
void setTiles( uint8_t x, uint8_t y, uint8_t startTile, uint8_t w );
void fill_bkg( uint8_t tile );
void fill_win( uint8_t tile );

void drawText( uint8_t x, uint8_t y, const unsigned char *text );

#define SPRITE_PALETTE_SIZE (4*8)

extern uint8_t tileTarget;
extern const uint16_t spritePalette[];

#endif