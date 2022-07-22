#pragma once

#include <irrlicht-1.8.5/irrlicht.h>
#include <OpenAL1.1/al.h>

#include "CAudioSource.h"
#include "CAudioData.h"

using namespace irr;

namespace agEngine
{
    namespace audio
    {
        class CAudioSource;
        class CAudioData;

        class CAudioStream : public virtual IReferenceCounted
        {
        public:
            CAudioStream(CAudioData* data=0);
            virtual ~CAudioStream();

            virtual void attachAudioData(CAudioData* data);
            virtual void detatchAudioData();

            virtual void rewind();
            virtual bool readSamples(CAudioSource* source, ALuint bufferId);
            bool readMemorySamples(CAudioSource* source, ALuint bufferId, char* lpBuffer, long nBytes);

            virtual bool hasFinished() const;

        private:
            CAudioData* attachedData;
        };
    }
}

