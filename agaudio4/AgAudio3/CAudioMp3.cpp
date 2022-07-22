#include "CAudioMp3.h"

#include "../minimp3/libc.h"
#include "../minimp3/minimp3.h"

#define BUFFER_COUNT 2
static mp3_decoder_t* mp3;
static mp3_info_t info;
static signed short sample_buffer[MP3_MAX_SAMPLES_PER_FRAME * BUFFER_COUNT];


namespace agEngine
{
    namespace audio
    {
        CAudioMp3::CAudioMp3(const core::stringc& filename, bool loadToMemory)
        : finished(false)
        {
            mp3 = mp3_create();

            open(filename, loadToMemory);
        }

        CAudioMp3::~CAudioMp3()
        {
            close();

            mp3_free(mp3);
        }

        s32 CAudioMp3::open(const core::stringc& filename, bool loadToMemory)
        {
            if (!(file = fopen(filename.c_str(), "rb")))
            {
                return -1;
            }

            fseek(file, 0, SEEK_END);
            mp3Data.nTotalFileBytes = ftell(file) - 128;

            fseek(file, 0, SEEK_SET);
            mp3Data.dataPtr = new unsigned char[mp3Data.nTotalFileBytes];

            fread(mp3Data.dataPtr, 1, mp3Data.nTotalFileBytes, file);

            mp3Data.bytes_offset = 0;
            mp3Data.bytes_left = mp3Data.nTotalFileBytes;

            format = AL_FORMAT_STEREO16;

            fclose(file);
            return 0;
        }

        void CAudioMp3::bufferthis(ALuint *buffer, c8* data, u32 size)
        {
            alBufferData(*buffer, format, data, size, mp3Data.sample_rate);
        }

        u32 CAudioMp3::getSampleCount()
        {           
            return 0;
        }

        u32 CAudioMp3::getPosition()
        {
            u32 pos = mp3Data.bytes_offset;
            return pos;         
        }

        void CAudioMp3::setPosition(u32 pos)
        {
            mp3Data.bytes_offset = pos;
            mp3Data.bytes_left = mp3Data.nTotalFileBytes - pos;
        }

        f64 CAudioMp3::getLength()
        {
            return 0;         
        }

        f64 CAudioMp3::getCurrentTime()
        {
            return 0;       
        }

        void CAudioMp3::rewind()
        {
            mp3Data.bytes_offset = 0;
            mp3Data.bytes_left = mp3Data.nTotalFileBytes;
        }

        s32 CAudioMp3::read(c8* buffer, s32 size, s32 bigEndian, s32 word, s32 signedByte, s32* bitstream)
        {
            int byte_count;
            byte_count = mp3_decode(mp3, mp3Data.dataPtr + mp3Data.bytes_offset, mp3Data.bytes_left, sample_buffer, &info);

            if (byte_count > 0)
            {
                mp3Data.sample_rate = info.sample_rate;
                mp3Data.channels = info.channels;

                if (mp3Data.channels == 1)
                {
                    format = AL_FORMAT_MONO16;
                }
                else
                {
                    format = AL_FORMAT_STEREO16;
                }
            }
            else
                return 0;

            mp3Data.bytes_left -= byte_count;
            mp3Data.bytes_offset += byte_count;       
            memcpy(buffer, sample_buffer, MP3_MAX_SAMPLES_PER_FRAME * BUFFER_COUNT);
            return MP3_MAX_SAMPLES_PER_FRAME * BUFFER_COUNT;
        }

        void CAudioMp3::close()
        {

        }

        bool CAudioMp3::readSamples(CAudioSource* source, ALuint bufferId)
        {
            s32 section, result;
            u32 size = 0;

            finished = false;

            u32 sBufferSize = source->getBufferSize();
            c8* sBuffer = source->getBuffer();
           
            while (size < (sBufferSize * 16))
            {
                if (mp3Data.bytes_offset >= mp3Data.nTotalFileBytes)
                {
                    rewind();
                    if (!source->isLooping())
                        finished = true;

                    break;
                }

                result = read(sBuffer + size, (sBufferSize * 16) - size, 0, 2, 1, &section);

                if (result > 0)
                    size += result;

                if (!result)
                {
                    finished = true;
                    break;
                }
            }      

            if (size == 0)
                return false;

            bufferthis(&bufferId, source->getBuffer(), size);

            if (alGetError() != AL_NO_ERROR)
            {
                return false;
            }

            return true;
        }

        bool CAudioMp3::readMemorySamples(CAudioSource* source, ALuint bufferId, char* lpBuffer, long nBytes)
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

        bool CAudioMp3::hasFinished() const
        {
            return finished;
        }
    }
}
