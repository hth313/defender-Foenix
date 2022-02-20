#include <stdbool.h>
#include "foenix/vicky.h"
#include "images.h"
#include <intrinsics65816.h>

void foo (int idx) {
#if 0
  tilemap[1].control = 1;
  tilemap[1].data = vicky_address((vram_ptr)0xbf0000);

  sprite[1].enable = true;
  sprite[1].lut = 3;
  sprite[idx].collisionOn = false;
#endif

  // assembler range error
  sprite[0] = (sprite_t) { .enable = true, .lut = 1, .depth = 2
                         , .collisionOn = true };
}

enum sprite_shapes {
  starshipIndex = 0
};

extern int bar (int x);
int hammer;

vram_ptr b0;
vram_ptr b1;

int main () {
  __enable_interrupts();

  // Enable graphics mode and sprites
  MASTER_CTRL_REG = Mstr_Ctrl_Sprite_En | Mstr_Ctrl_Graph_Mode_En | Mstr_Ctrl_Bitmap_En | Mstr_Ctrl_Video_Mode1;

  sprite[starshipIndex] = (sprite_t) {
    .enable  = true,
//    .data = vicky_address(starship_right),

    .data = (vram_ptr) 0x20000,
    .x = 100,
    .y = 100,
    .lut = 0
  };

  BACKGROUND_COLOR_B = 250;
  BACKGROUND_COLOR_G = 50;
  BACKGROUND_COLOR_R = 50;


  b0 = bitplane[0].start;
  b1 = bitplane[1].start;

  bitplane[0].start = (vram_ptr) 0x10000;
  bitplane[1].start = (vram_ptr) 0x0000;

  GRPH_LUT0_LONG[0] = 0x00101010;
  GRPH_LUT0_LONG[1] = 0x00303030;
  GRPH_LUT0_LONG[2] = 0x00606060;
  GRPH_LUT0_LONG[3] = 0x00A0A0A0;
  GRPH_LUT0_LONG[4] = 0x00B0B0B0;

  for (;;) {
    hammer = bar(hammer+3);
  }
  return 0;
}
