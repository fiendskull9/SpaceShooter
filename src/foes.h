#define FOES 		3 /* must be (1 < x < 6) */

extern void foes_load_data();

extern void foes_draw();

extern void foes_move_spaceship();
extern void foes_move_bullet();

extern void foes_fire_bullet();

extern void foes_respawn();

extern void foes_check_collision();

extern void foes_get_spaceship_coord(int *x, int *y);
extern void foes_get_bullet_coord(int *x, int *y);
