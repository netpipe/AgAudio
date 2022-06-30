
#include <fluidsynth/fluidsynth.h>

struct fx_data_t
{
    fluid_synth_t* synth;
    float gain;
} fx_data_t;


int fx_function(void* data, int len,
    int nfx, float** fx,
    int nout, float** out)
{
    struct fx_data_t* fx_data = (struct fx_data_t*)data;
    int i, k;

    if (fluid_synth_process(fx_data->synth, len, nout, out, nout, out) != FLUID_OK)
    {
        /* Some error occurred. Very unlikely to happen, though. */
        return FLUID_FAILED;
    }

    for (i = 0; i < nout; i++)
    {
        float* out_i = out[i];
        for (k = 0; k < len; k++)
        {
            out_i[k] *= fx_data->gain;
        }
    }
    /* Apply the same effect to all available effect buffer. */
    for (i = 0; i < nfx; i++)
    {
        float* fx_i = fx[i];
        for (k = 0; k < len; k++)
        {
            fx_i[k] *= fx_data->gain;
        }
    }
    return FLUID_OK;
}

int main(int argc, char** argv)
{

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


    /* Fill in the data of the effects unit */
    fx_data.synth = synth;
    fx_data.gain = 10.0f;

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
    return 0;

}