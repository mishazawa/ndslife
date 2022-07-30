#define OFFSET(r,c,w) ((r)*(w)+(c))
#define SCREEN_MAIN 1
#define SCREEN_SUB 0
#define FPS (5)

#define SIZE    (4)
#define GRID_X  (SCREEN_WIDTH  / SIZE)
#define GRID_Y  (SCREEN_HEIGHT / SIZE)
#define LENGTH  (GRID_X * GRID_Y)

#define BLACK ARGB16(1, 0, 0, 0)
#define WHITE ARGB16(1, 31, 31, 31)

static int CURRENT_SCREEN;
static u16 CURRENT_COLOR;


int range (int n) {
  return rand() % n + 1;
}


u16* videoMemoryMain;
u16* videoMemorySub;


void rect(int x, int y, int size_x, int size_y) {
    for (int pos_y = y; pos_y < y+size_y; pos_y++) {
        for (int pos_x = x; pos_x < x+size_x; pos_x++) {
            if (CURRENT_SCREEN==SCREEN_MAIN) {
              videoMemoryMain[OFFSET(SCREEN_WIDTH, pos_y, pos_x)] = CURRENT_COLOR;
            } else {
              videoMemorySub[OFFSET(SCREEN_WIDTH, pos_y, pos_x)] = CURRENT_COLOR;
            }
        }
    }
}

void fill(u16 c) {
  CURRENT_COLOR = c;
}


void fill_random(int * field) {
  for (int i=0; i < LENGTH; i++) {
    field[i] = range(10) < 5 ? 1:0;
  }
}

void setScreenMain() {
  CURRENT_SCREEN = SCREEN_MAIN;
}

void setScreenSub() {
  CURRENT_SCREEN = SCREEN_SUB;
}
