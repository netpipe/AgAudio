#pragma once

#include <fluidsynth/fluidsynth.h>

#include "CAudioData.h"

using namespace irr;


namespace agEngine
{
    namespace audio
    {
        struct SMidiFile
        {          
            int sample_rate;
            int channels;
        };

        class CAudioMidi : public CAudioData
        {
        public:
            CAudioMidi(const core::stringc& filename, bool loadToMemory = false);
            ~CAudioMidi();

            s32 open(const core::stringc& filename, bool loadToMemory = false);
            void close();
            u32 getSampleCount();
            u32 getPosition();
            void setPosition(u32 newPosition);
            f64 getLength();
            f64 getCurrentTime();
            void rewind();
            s32 read(c8* buffer, s32 size, s32 bigEndian, s32 word, s32 signedByte, s32* bitstream);
            void bufferthis(ALuint* buffer, c8* data, u32 size);
            bool readSamples(CAudioSource* source, ALuint bufferId);
            bool readMemorySamples(CAudioSource* source, ALuint bufferId, char* lpBuffer, long nBytes);
            bool hasFinished() const;

        private:           
            fluid_settings_t* settings;
            fluid_synth_t* synth;
            fluid_player_t* player;
            fluid_audio_driver_t* adriver;

            //FILE* file;
            SMidiFile midiData;
            

            ALenum format;

            bool finished;
            u32 bufferSize;
        };
    }
}

