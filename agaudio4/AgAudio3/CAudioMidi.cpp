#include "CAudioMidi.h"

struct fx_data_t
{
    fluid_synth_t* synth;
    float gain;
} fx_data_t;

struct fx_data_t fx_data;

#define SAMPLE_RATE 44100 
#define SAMPLE_SIZE 2

char audio_buf[44100 * 40];

long buffer_write_offset = 0;

bool bWrite = false;

int fx_function(void* data, int len,
    int nfx, float** fx,
    int nout, float** out)
{
    bWrite = true;

    struct fx_data_t* fx_data = (struct fx_data_t*)data;

    fluid_synth_write_s16(fx_data->synth, len, audio_buf + buffer_write_offset, 0, nout, audio_buf + buffer_write_offset, 1, nout);

    buffer_write_offset += len * SAMPLE_SIZE * nout;

    bWrite = false;

    return FLUID_OK;
}

namespace agEngine
{
    namespace audio
    {
        CAudioMidi::CAudioMidi(const core::stringc& filename, bool loadToMemory)
        : finished(false)
        {
            open(filename, loadToMemory);
        }

        CAudioMidi::~CAudioMidi()
        {
            close();
        }

        s32 CAudioMidi::open(const core::stringc& filename, bool loadToMemory)
        {
            midiData.sample_rate = 44100;
            format = AL_FORMAT_STEREO16;

            settings = new_fluid_settings();
            synth = new_fluid_synth(settings);
            player = new_fluid_player(synth);

            fluid_synth_sfload(synth, "soundfont.sf2", 1);
            fluid_player_add(player, filename.c_str());
            fluid_settings_setnum(settings, "synth.sample-rate", midiData.sample_rate);

            fx_data.synth = synth;
            fx_data.gain = 10.f;

            adriver = new_fluid_audio_driver2(settings, fx_function, (void*)&fx_data);

            fluid_player_play(player);         

            return 0;
        }

        void CAudioMidi::bufferthis(ALuint *buffer, c8* data, u32 size)
        {
            alBufferData(*buffer, format, data, size, midiData.sample_rate);
        }

        u32 CAudioMidi::getSampleCount()
        {           
            return 0;
        }

        u32 CAudioMidi::getPosition()
        { 
            return 0;
        }

        void CAudioMidi::setPosition(u32 pos)
        {           
        }

        f64 CAudioMidi::getLength()
        {
            return 0;         
        }

        f64 CAudioMidi::getCurrentTime()
        {
            return 0;       
        }

        void CAudioMidi::rewind()
        {          
            buffer_write_offset = 0;
            fluid_player_play(player);
        }

        s32 CAudioMidi::read(c8* buffer, s32 size, s32 bigEndian, s32 word, s32 signedByte, s32* bitstream)
        {
            if (buffer_write_offset == 0) return 0;
            if (bWrite) return 0;

            int byte_count = 0;

            if (size < buffer_write_offset)
                byte_count = size;
            else
                byte_count = buffer_write_offset;

            memcpy(buffer, audio_buf, buffer_write_offset);        

            buffer_write_offset = 0; 

            return byte_count;
        }

        void CAudioMidi::close()
        {
            delete_fluid_audio_driver(adriver);
            delete_fluid_player(player);
            delete_fluid_synth(synth);
            delete_fluid_settings(settings);
        }

        bool CAudioMidi::readSamples(CAudioSource* source, ALuint bufferId)
        {
            s32 section, result;
            u32 size = 0;

            finished = false;

            u32 sBufferSize = source->getBufferSize();
            c8* sBuffer = source->getBuffer();   
           
            while (size < (sBufferSize * 16))
            {
                if (fluid_player_get_status(player) == FLUID_PLAYER_DONE)
                {
                    rewind();
                    if (!source->isLooping())
                        finished = true;

                    break;
                }

                result = read(sBuffer + size, (sBufferSize * 16) - size, 0, 2, 1, &section);

                if (result > 0)
                    size += result;
            }                 

            if (size == 0)
            {
                finished = true;
                return false;
            }          

            bufferthis(&bufferId, source->getBuffer(), size);

            if (alGetError() != AL_NO_ERROR)
            {
                return false;
            }

            return true;
        }

        bool CAudioMidi::readMemorySamples(CAudioSource* source, ALuint bufferId, char* lpBuffer, long nBytes)
        {          
            u32 size = 0;

            finished = false;

            u32 sBufferSize = source->getBufferSize();
            c8* sBuffer = source->getBuffer();           
     
            bufferthis(&bufferId, lpBuffer, nBytes);

            if (alGetError() != AL_NO_ERROR)
            {
                return false;
            }

            return true;
        }

        bool CAudioMidi::hasFinished() const
        {
            return finished;
        }
    }
}
