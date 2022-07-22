#include "CAudioXm.h"

namespace agEngine
{
    namespace audio
    {
        CAudioXm::CAudioXm(const core::stringc& filename, bool loadToMemory)
        : finished(false)
        {
            open(filename, loadToMemory);
        }

        CAudioXm::~CAudioXm()
        {
            close();
        }

        s32 CAudioXm::open(const core::stringc& filename, bool loadToMemory)
        {
            xm_filename = filename;

            xmData.sample_rate = 44100;
            xmData.channels = 2;

            create_context_from_file(&ctx, xmData.sample_rate, filename.c_str());

            format = AL_FORMAT_STEREO16;
      
            return 0;
        }

        void CAudioXm::bufferthis(ALuint *buffer, c8* data, u32 size)
        {
            alBufferData(*buffer, format, data, size, xmData.sample_rate);
        }

        u32 CAudioXm::getSampleCount()
        {           
            return 0;
        }

        u32 CAudioXm::getPosition()
        {
            return 0;
        }

        void CAudioXm::setPosition(u32 pos)
        {
        }

        f64 CAudioXm::getLength()
        {
            return 0;         
        }

        f64 CAudioXm::getCurrentTime()
        {
            return 0;       
        }

        void CAudioXm::rewind()
        {
            create_context_from_file(&ctx, xmData.sample_rate, xm_filename.c_str());        
        }

        s32 CAudioXm::read(c8* buffer, s32 size, s32 bigEndian, s32 word, s32 signedByte, s32* bitstream)
        {
            size_t buffer_size = 44100;
            

            if (buffer_size * 2 >= (size_t)size)
                buffer_size = size / 2;

            float* float_buffer = new float[buffer_size];

            xm_generate_samples(ctx, float_buffer, buffer_size / xmData.channels);

            int16_t* newBuffer = new int16_t[buffer_size];

            for (size_t i = 0; i < buffer_size; i++)
            {
                float sampleFloat = float_buffer[i];
                sampleFloat *= 32767;

                int16_t sampleInt = (int16_t)sampleFloat;
                newBuffer[i] = sampleInt;
            }

            memcpy(buffer, newBuffer, buffer_size * sizeof(int16_t));

            delete newBuffer;
            delete float_buffer;

            return buffer_size * sizeof(int16_t);
        }

        void CAudioXm::close()
        {
            xm_free_context(xmData.ctx);
        }

        bool CAudioXm::readSamples(CAudioSource* source, ALuint bufferId)
        {
            s32 section, result;
            u32 size = 0;

            finished = false;

            u32 sBufferSize = source->getBufferSize();
            c8* sBuffer = source->getBuffer();
           
            while (size < (sBufferSize * 16))
            {
                if (xm_get_loop_count(ctx) != 0)
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

        bool CAudioXm::readMemorySamples(CAudioSource* source, ALuint bufferId, char* lpBuffer, long nBytes)
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

        bool CAudioXm::hasFinished() const
        {
            return finished;
        }
    }
}
