#include <gb/gb.h>
#include <stdio.h>

void main() {
	DISPLAY_ON;
	SHOW_BKG;
	
	printf("ABC0123\nHi Mato?");

	while (1) {
		if (joypad() && J_A)
			break;
	}

	DISPLAY_OFF;
}