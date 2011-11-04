/*
 * Old-school space shooter game in 2D.
 *
 * Copyright (c) 2011, Alessandro Ghedini
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 *     * Neither the name of the SpaceShooter project, Alessandro Ghedini, nor
 *       the names of its contributors may be used to endorse or promote
 *       products derived from this software without specific prior written
 *       permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <sndfile.h>

#include "debug.h"

static ALCdevice	*device;
static ALCcontext	*context;

void sound_init() {
	device	= alcOpenDevice(NULL);
	context	= alcCreateContext(device, NULL);

	alcMakeContextCurrent(context);

	alListener3f(AL_POSITION, 0, 0, 0);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListener3f(AL_ORIENTATION, 0, 0, -1);
}

void sound_close() {
	alcDestroyContext(context);
	alcCloseDevice(device);
}

unsigned int wav_load(const char *path) {
	int err;

	unsigned int	sample, source;

	SF_INFO		snd_info;
	SNDFILE		*snd_input;

	short		*input_buffer;
	size_t		buffer_size;

	unsigned int	channels, frames, sample_rate, samples;

	alGenBuffers(1, &sample);

	snd_input = sf_open(path, SFM_READ, &snd_info);
	if (snd_input == NULL) fail_printf("%s", sf_strerror(snd_input));

	channels	= snd_info.channels;
	frames		= snd_info.frames;
	sample_rate	= snd_info.samplerate;
	samples		= frames * channels;

	buffer_size	= samples * sizeof(short);

	input_buffer = malloc(buffer_size);
	if (input_buffer == NULL) fail_printf("Out of memory");

	err = sf_read_short(snd_input, input_buffer, frames);
	if (err != frames) fail_printf("%s", sf_strerror(snd_input));

	sf_close(snd_input);

	alBufferData(
		sample,
		(channels == 2 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16),
		input_buffer, buffer_size, sample_rate
	);

	alGenSources(1, &source);

	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcei(source, AL_LOOPING, AL_FALSE);

	alSourcei(source, AL_BUFFER, sample);

	free(input_buffer);

	return source;
}

void wav_play(unsigned int sample) {

	alSourcePlay(sample);

	/*alDeleteSources(1, &source);*/
}

void wav_free(unsigned int sample) {
	ALuint source;

	alGenSources(1, &source);

	alSourcei(source, AL_BUFFER, sample);

	alDeleteBuffers(1, &sample);
	alDeleteSources(1, &source);
}
