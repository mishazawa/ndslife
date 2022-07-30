#include <nds.h>
#include "utils/misc.h"

int field[LENGTH];
int nex_gen_field[LENGTH];

int field_sub[LENGTH];
int nex_gen_field_sub[LENGTH];

void draw() {
  for (int i=0; i < LENGTH; i++) {
    int x = i % GRID_X;
    int y = i / GRID_X;

    field_sub[i] != 0 ? fill(WHITE) : fill(BLACK);
    setScreenSub();
    rect(y*SIZE, x*SIZE, SIZE, SIZE);

    field[i] != 0 ? fill(WHITE) : fill(BLACK);
    setScreenMain();
    rect(y*SIZE, x*SIZE, SIZE, SIZE);
  }
}

void gameLoop() {
  videoSetMode(MODE_FB0);
  videoSetModeSub(MODE_5_2D);

  vramSetBankA(VRAM_A_LCD);
  vramSetBankC(VRAM_C_SUB_BG);

  int bgSub = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0,0);

  videoMemoryMain = VRAM_A;
  videoMemorySub = bgGetGfxPtr(bgSub);


  fill_random(&field);
  fill_random(&field_sub);

  while(1) {
    scanKeys();
    if (keysCurrent() & KEY_TOUCH) {
      fill_random(&field);
      fill_random(&field_sub);
    }

    draw();

    swiWaitForVBlank();

    next_gen(&field, &nex_gen_field);
    next_gen(&field_sub, &nex_gen_field_sub);

    for (int i = 0; i < FPS; i ++) {
      swiWaitForVBlank();
    }
  }
}


int check_valid_cell (int x, int y) {
  if (x < 0 || x >= GRID_X) return -1;
  if (y < 0 || y >= GRID_Y) return -1;
  return x + GRID_X * y;
}

void fill_indicies (int * buff, int index) {
  int x = index % GRID_X;
  int y = index / GRID_X;

  buff[0] = check_valid_cell(x+1, y);
  buff[1] = check_valid_cell(x-1, y);
  buff[2] = check_valid_cell(x, y-1);
  buff[3] = check_valid_cell(x, y+1);
  buff[4] = check_valid_cell(x+1, y-1);
  buff[5] = check_valid_cell(x-1, y-1);
  buff[6] = check_valid_cell(x+1, y+1);
  buff[7] = check_valid_cell(x-1, y+1);
}

void next_gen (int * field, int * newgen) {
  for (int i = 0; i < LENGTH; i++) {
    int count = 0;

    int idx[8];
    fill_indicies(&idx, i);
    for (int j=0; j < 8; j++) {
      if (j != -1 && j < LENGTH) count += field[idx[j]];
    }

    int val = 0;

    if (field[i] == 1) {
      if (count == 2 || count == 3) val = 1;
    } else {
      if (count == 3) val = 1;
    }

    newgen[i] = val;
  }

  for (int i = 0; i < LENGTH; i++) {
    field[i] = newgen[i];
  }
}


int main(void) {
  gameLoop();
  return 0;
}
