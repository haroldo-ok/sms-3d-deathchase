#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "SMSlib/src/SMSlib.h"
#include "types.h"
#include "three_d.h"
#include "three_d_tables.h"
#include "gfx.h"

UBYTE map[PF_HEIGHT][PF_WIDTH];

void clear_map() {
  memset(*map, ' ', PF_WIDTH * PF_HEIGHT);
}

void draw_map() {
  UBYTE *o;
  UWORD buffer[PF_WIDTH], *d;
  UBYTE i, j;

  o = map[0];
  for (i = 0; i != PF_HEIGHT; i++) {
    d = buffer;
    for (j = 0; j != PF_WIDTH; j++) {
      *d = *o - 32;
      o++; d++;
    }
    SMS_loadTileMap (0, i, buffer, PF_WIDTH << 1);
  }
}

void draw_tree(int x, int y) {
  UBYTE i, j;

  for (i = 0; i != PF_HEIGHT; i++) {
    for (j = 10; j != 20; j++) {
      map[i][j] = 'H';
    }
  }
}

void load_font (void) {
  unsigned char i, j;
	unsigned char buffer[32], *o, *d;

	o = font_fnt;
	for (i = 0; i != 96; i++) {
		d = buffer;
		for (j = 0; j != 8; j++) {
			*d = *o; d++;
			*d = ~(*o);	d++;
			*d = 0;	d++;
			*d = 0;	d++;
      o++;
		}
		SMS_loadTiles(buffer, i, 32);
    SMS_loadTiles(buffer, i + 256, 32);
	}
}

void main(void) {
  unsigned char i;

  load_font();

  for (i=0;i<16;i++) {
    SMS_setBGPaletteColor(i,0x00);    // black
    SMS_setSpritePaletteColor(i,0x00);    // black
  }
  SMS_setBGPaletteColor(01,0x3f);     // white
  SMS_setSpritePaletteColor(01,0x3f);     // white
  SMS_displayOn();

  while (true) {
    clear_map();
    draw_tree(0, 0);

    SMS_waitForVBlank();
    draw_map();
  }
}

SMS_EMBED_SEGA_ROM_HEADER(9999,0); // code 9999 hopefully free, here this means 'homebrew'
SMS_EMBED_SDSC_HEADER(0,1, 2015,11,22, "Haroldo-OK\\2015", "3D Deathchase",
  "A port/clone of 3D Deathchase to the SMS.\n"
  "Built using devkitSMS & SMSlib - https://github.com/sverx/devkitSMS");
