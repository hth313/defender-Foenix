#include <stdbool.h>
#include "foenix/vicky.h"
#include "images.h"

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

int main () {

  sprite[starshipIndex] = (sprite_t) {
    .enable  = true,
    .data = vicky_address(starship_right),
    .x = 50,
    .y = 100
  };

  return 0;
}
