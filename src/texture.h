extern unsigned int texture_load(const char *path);

extern void texture_free(unsigned int texture);
extern void texture_draw(unsigned int texture, int x, int y, unsigned int width, unsigned int height);
