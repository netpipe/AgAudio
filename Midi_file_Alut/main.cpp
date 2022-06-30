
#include <iostream>
//#include <Windows.h>

#include "fluid_config.h"
#include "fluidsynth_priv.h"
#include <fluidlite.h>
#include "fluid_lash.h"

#include <AL/alut.h>

struct fx_data_t
{
    fluid_synth_t* synth;
    float gain;
} fx_data_t;

ALuint uiBuffer;
ALuint uiSource;
ALenum ulFormat;

#define SAMPLE_RATE 44100
#define SAMPLE_SIZE 2 //4: Float Buffer   2: Signed Int Buffer

char audio_buf[44100 * 4];

long buffer_offset = 0;
int buffer_count = 0;

int fx_function(void* data, int len,
    int nfx, float** fx,
    int nout, float** out)
{
    struct fx_data_t* fx_data = (struct fx_data_t*)data;

    fluid_synth_set_gain(fx_data->synth, 2.f);
    fluid_synth_write_s16(fx_data->synth, len, audio_buf + buffer_offset, 0, nout, audio_buf + buffer_offset, 1, nout);

    buffer_offset += len * SAMPLE_SIZE * nout;
    buffer_count++;

    if (buffer_count >= 20)
    {
        alSourceRewind(uiSource);
        alSourcei(uiSource, AL_BUFFER, 0);
        alBufferData(uiBuffer, ulFormat, audio_buf, buffer_offset, SAMPLE_RATE);
        alSourcei(uiSource, AL_BUFFER, uiBuffer);
        alSourcePlay(uiSource);
        buffer_count = 0;
        buffer_offset = 0;
    }

   // return FLUID_OK;
    return 1;
}

int main(int argc, char** argv)
{
    if (!alutInit(&argc, argv))
    {
        ALenum error = alutGetError();
        fprintf(stderr, "%s\n", alutGetErrorString(error));
        exit(EXIT_FAILURE);
    }

    ulFormat = AL_FORMAT_STEREO16;
    alGenBuffers(1, &uiBuffer);
    alGenSources(1, &uiSource);

    alSource3i(uiSource, AL_POSITION, 0, 0, -1);
    alSourcei(uiSource, AL_SOURCE_RELATIVE, AL_TRUE);
    alSourcei(uiSource, AL_ROLLOFF_FACTOR, 0);


    fluid_settings_t* settings;
    fluid_synth_t* synth;
    fluid_player_t* player;
    fluid_audio_driver_t* adriver;

    struct fx_data_t fx_data;

    settings = new_fluid_settings();
    synth = new_fluid_synth(settings);
    player = new_fluid_player(synth);

    /* process command line arguments */
    fluid_synth_sfload(synth, "soundfont.sf2", 1);
    fluid_player_add(player, "REGGAE.MID");
    fluid_settings_setnum(settings, "synth.sample-rate", SAMPLE_RATE);


    /* Fill in the data of the effects unit */
    fx_data.synth = synth;
    fx_data.gain = 1.f;

    adriver = new_fluid_audio_driver2(settings, fx_function, (void*)&fx_data);

    /* play the midi files, if any */
    fluid_player_play(player);
    /* wait for playback termination */
    fluid_player_join(player);
    /* cleanup */
    delete_fluid_audio_driver(adriver);
    delete_fluid_player(player);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);


    alDeleteSources(1, &uiSource);
    alDeleteBuffers(1, &uiBuffer);

    alutExit();

    return 0;

}
