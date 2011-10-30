#define PLAYER_BULLET_WIDTH 	7
#define PLAYER_BULLET_HEIGHT 	7

extern void player_load_data();

extern void player_draw();

extern void player_move_spaceship();
extern void player_move_bullet();

extern void player_fire_bullet();

extern void player_get_spaceship_coord(int *x, int *y);
extern void player_get_bullet_coord(int *x, int *y);

extern void player_reset_bullet();
