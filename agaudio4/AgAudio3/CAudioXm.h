#pragma once

#include "CAudioData.h"

#include "../xm/testprog.h"

using namespace irr;

namespace agEngine
{
    namespace audio
    {
        struct SXmFile
        {
            xm_context_t* ctx;

            int sample_rate;
            int channels;
        };

        class CAudioXm : public CAudioData
        {
        public:
            CAudioXm(const core::stringc& filename, bool loadToMemory = false);
            ~CAudioXm();

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
            xm_context_t* ctx;
            core::stringc xm_filename;

            FILE* file;
            SXmFile xmData;           

            ALenum format;

            bool finished;
            u32 bufferSize;
        };
    }
}

