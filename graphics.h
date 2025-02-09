#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <gb/gb.h>

#include "media/tiles.h"

// 160x144 px = 20x18 tiles
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
#define SCROLL_H (TPH-PH) 
#define SCROLL_MW (SCROLL_W-1) /* maximum scrolling */
#define SCROLL_MH (SCROLL_H-1)
#define SCROLL_X (SCROLL_MW/2)
#define SCROLL_Y (SCROLL_MH/2)

// Tile settings
#define NUMBER_OF_TILES 64
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

#define TILE_FACE_LEFT 48
#define TILE_FACE_RIGHT 50

#define TILE_TOP_LEFT 60
#define TILE_BOTTOM_LEFT 61
#define TILE_TOP_RIGHT 62
#define TILE_BOTTOM_RIGHT 63

// TileColor: https://stackoverflow.com/a/1489985
#define PASTER( X, Y ) X ## Y
#define EVALUATOR( X, Y ) PASTER( X, Y )
#define TCOL( X ) EVALUATOR( TilesCGB, X )

#define TARGET_BKG 0
#define TARGET_WIN 1

// convenience macros
#define USE_COLOR_RAM VBK_REG=1
#define USE_DATA_RAM VBK_REG=0

void setTile( uint8_t x, uint8_t y, uint8_t tile );
void setTiles( uint8_t x, uint8_t y, uint8_t startTile, uint8_t w );
void fill_bkg( uint8_t tile );

void drawText( uint8_t x, uint8_t y, const unsigned char *text );

#define SPRITE_PALETTE_SIZE (4*8)

extern uint8_t tileTarget;
extern const uint16_t spritePalette[];

#endif