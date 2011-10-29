typedef struct SPACESHIP {
	int x, y;
	int fire;
	int health;
	unsigned int texture;


	int bullet_x, bullet_y;
	unsigned int bullet_texture;
} spaceship_t;

extern spaceship_t *player_load();

extern void player_draw();
