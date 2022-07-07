#pragma once

#include <irrlicht-1.8.5/irrlicht.h>

#include <OpenAL1.1/al.h>

#include <libogg-1.3.5/ogg.h>
#include <libvorbis-1.3.7/codec.h>
#include <libvorbis-1.3.7/vorbisfile.h>

#include "CAudioData.h"

using namespace irr;

namespace agEngine
{
    namespace audio
    {
        struct SOggFile
        {
            c8* dataPtr;
            u32 dataSize;
            u32 dataRead;
        };

        class CAudioOgg : public CAudioData
        {
        public:
            CAudioOgg(const core::stringc& filename, bool loadToMemory = false);
            ~CAudioOgg();

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
            SOggFile oggData;
            OggVorbis_File stream;
            ov_callbacks vorbisCallbacks;
            vorbis_info* info;

            ALenum format;

            bool loadedInMemory;
            bool finished;
            u32 bufferSize;
        };
    }
}

