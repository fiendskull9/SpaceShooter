#include <stdlib.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <sndfile.h>

static ALuint		source;

static ALCdevice	*device;
static ALCcontext	*context;

void sound_init() {
	device	= alcOpenDevice(NULL);
	context	= alcCreateContext(device, NULL);

	alcMakeContextCurrent(context);

	alListener3f(AL_POSITION, 0, 0, 0);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListener3f(AL_ORIENTATION, 0, 0, -1);

	alGenSources(1, &source);

	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcei(source, AL_LOOPING, AL_FALSE);
}

void sound_close() {
	alDeleteSources(1, &source);

	alcDestroyContext(context);
	alcCloseDevice(device);
}

unsigned int sample_load(const char *path) {
	int err;

	unsigned int	sample;

	SF_INFO		snd_info;
	SNDFILE		*snd_input;

	short		*input_buffer;
	size_t		buffer_size;

	unsigned int	channels, frames, sample_rate, samples;

	alGenBuffers(1, &sample);

	/* load data to buffer */
	snd_input = sf_open(path, SFM_READ, &snd_info);

	channels	= snd_info.channels;
	frames		= snd_info.frames;
	sample_rate	= snd_info.samplerate;
	samples		= frames * channels;

	buffer_size	= samples * sizeof(short);

	input_buffer = malloc(buffer_size);

	err = sf_read_short(snd_input, input_buffer, frames);

	if (err != frames)
		printf("error: %s\n", sf_strerror(snd_input));

	sf_close(snd_input);

	alBufferData(
		sample,
		(channels == 2 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16),
		input_buffer, buffer_size, sample_rate
	);

	free(input_buffer);

	return sample;
}

void sample_play(unsigned int sample) {
	alSourcei(source, AL_BUFFER, sample);

	alSourcePlay(source);
}

void sample_free(unsigned int sample) {
	alSourcei(source, AL_BUFFER, sample);

	alDeleteBuffers(1, &sample);
}

