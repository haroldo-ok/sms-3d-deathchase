#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "SMSlib/src/SMSlib.h"
#include "types.h"
#include "three_d.h"
#include "three_d_tables.h"
#include "gfx.h"

#define MAX_TREES 8

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
  BYTE i, tx;
  trunk_data *trunk_data = trunk_table + y;
  UBYTE trunk_tile_w = trunk_data->width;
  UBYTE trunk_tile_h = trunk_data->height;
  BYTE projected_x = x >= 0 ? trunk_depth_x[y][x] : -trunk_depth_x[y][-x];

  BYTE start_x = (PF_WIDTH >> 1) + projected_x - (trunk_tile_w >> 1);
  BYTE end_x = start_x + trunk_tile_w;

  BYTE start_y = (PF_HEIGHT >> 1) - (trunk_tile_h >> 1);
  BYTE end_y = start_y + trunk_tile_h;

  if (projected_x < -15 || projected_x > 15) {
    return;
  }

  if (end_x > PF_WIDTH) {
    end_x = PF_WIDTH;
  }

  if (start_y < 0) {
    start_y = 0;
  }
  if (end_y > PF_HEIGHT) {
    end_y = PF_HEIGHT;
  }

  for (i = start_y; i != end_y; i++) {
    for (tx = start_x; tx != end_x; tx++) {
      map[i][tx] = 'H';
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
  unsigned char i, j;
  point points[MAX_TREES], *ppoint;

  load_font();

  for (i=0;i<16;i++) {
    SMS_setBGPaletteColor(i,0x00);    // black
    SMS_setSpritePaletteColor(i,0x00);    // black
  }
  SMS_setBGPaletteColor(01,0x3f);     // white
  SMS_setSpritePaletteColor(01,0x3f);     // white
  SMS_displayOn();

  for (i = 0, ppoint = points; i != MAX_TREES; i++, ppoint++) {
    ppoint->x.b.h = rand() & 0x3F;
    ppoint->y.b.h = rand() & 0x1F;
  }

  while (true) {
    clear_map();
    for (i = 0, ppoint = points; i != MAX_TREES; i++, ppoint++) {
      draw_tree((BYTE) ppoint->x.b.h - 32, ppoint->y.b.h);
    }

    SMS_waitForVBlank();
    draw_map();

    for (i = 0, ppoint = points; i != MAX_TREES; i++, ppoint++) {
      ppoint->y.b.h--;
      if (ppoint->y.b.h > 31) {
        ppoint->x.b.h = rand() & 0x3F;
        ppoint->y.b.h = (rand() & 3) + 28;
      }
    }
  }
}

SMS_EMBED_SEGA_ROM_HEADER(9999,0); // code 9999 hopefully free, here this means 'homebrew'
SMS_EMBED_SDSC_HEADER(0,2, 2015,11,26, "Haroldo-OK\\2015", "3D Deathchase https://github.com/haroldo-ok/sms-3d-deathchase",
  "A clone of 3D Deathchase for the SMS.\n"
  "Built using devkitSMS & SMSlib - https://github.com/sverx/devkitSMS");
