#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <gb/gb.h>

#include "media/tiles.h"

// 160x144 px = 20x18 tiles
#define PW 160
#define PH 144
#define TW 20
#define TH 18
#define BW 32
#define BH 32

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

// TileColor: https://stackoverflow.com/a/1489985
#define PASTER( X, Y ) X ## Y
#define EVALUATOR( X, Y ) PASTER( X, Y )
#define TCOL( X ) EVALUATOR( TilesCGB, X )

#define TARGET_BKG 0
#define TARGET_WIN 1

void setTile( uint8_t x, uint8_t y, uint8_t tile );
void setTiles( uint8_t x, uint8_t y, uint8_t startTile, uint8_t w );
void fill_bkg( uint8_t tile );

void drawText( uint8_t x, uint8_t y, const unsigned char *text );

#define SPRITE_PALETTE_SIZE (4*8)

extern uint8_t tileTarget;
extern const uint16_t spritePalette[];

#endif