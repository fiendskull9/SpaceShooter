extern void sound_init();
extern void sound_close();

extern unsigned int sample_load(const char *path);

extern void sample_play(unsigned int sample);
extern void sample_free(unsigned int sample);
