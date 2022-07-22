#pragma once

#include "CAudioData.h"

using namespace irr;

namespace agEngine
{
    namespace audio
    {
        struct SMp3File
        {
            long nTotalFileBytes;
            long bytes_left;
            long bytes_offset;
            unsigned char* dataPtr;          

            int sample_rate;
            int channels;
        };

        class CAudioMp3 : public CAudioData
        {
        public:
            CAudioMp3(const core::stringc& filename, bool loadToMemory = false);
            ~CAudioMp3();

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

            FILE* file;
            SMp3File mp3Data;           

            ALenum format;

            bool finished;
            u32 bufferSize;
        };
    }
}

