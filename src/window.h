#define SCREEN_WIDTH		640
#define SCREEN_HEIGHT		480

extern void window_init(int width, int height, const char *title);

extern void window_clear();
extern void window_swap_buf();
extern void window_close();
