#pragma once

#include <irrlicht-1.8.5/irrlicht.h>
#include <OpenAL1.1/al.h>
#include <OpenAL1.1/alc.h>
#include <OpenAL1.1/efx.h>
#include "CAudioSource.h"

using namespace irr;

namespace agEngine
{
    namespace audio
    {        
        // OpenAL extensions
        typedef struct
        {
            // Effect object functions
            LPALGENEFFECTS alGenEffects;
            LPALDELETEEFFECTS alDeleteEffects;
            LPALISEFFECT alIsEffect;
            LPALEFFECTI alEffecti;
            LPALEFFECTIV alEffectiv;
            LPALEFFECTF alEffectf;
            LPALEFFECTFV alEffectfv;
            LPALGETEFFECTI alGetEffecti;
            LPALGETEFFECTIV alGetEffectiv;
            LPALGETEFFECTF alGetEffectf;
            LPALGETEFFECTFV alGetEffectfv;

            // Filter object functions
            LPALGENFILTERS alGenFilters;
            LPALDELETEFILTERS alDeleteFilters;
            LPALISFILTER alIsFilter;
            LPALFILTERI alFilteri;
            LPALFILTERIV alFilteriv;
            LPALFILTERF alFilterf;
            LPALFILTERFV alFilterfv;
            LPALGETFILTERI alGetFilteri;
            LPALGETFILTERIV alGetFilteriv;
            LPALGETFILTERF alGetFilterf;
            LPALGETFILTERFV alGetFilterfv;

            // Auxiliary slot object functions
            LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots;
            LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots;
            LPALISAUXILIARYEFFECTSLOT alIsAuxiliaryEffectSlot;
            LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti;
            LPALAUXILIARYEFFECTSLOTIV alAuxiliaryEffectSlotiv;
            LPALAUXILIARYEFFECTSLOTF alAuxiliaryEffectSlotf;
            LPALAUXILIARYEFFECTSLOTFV alAuxiliaryEffectSlotfv;
            LPALGETAUXILIARYEFFECTSLOTI alGetAuxiliaryEffectSloti;
            LPALGETAUXILIARYEFFECTSLOTIV alGetAuxiliaryEffectSlotiv;
            LPALGETAUXILIARYEFFECTSLOTF alGetAuxiliaryEffectSlotf;
            LPALGETAUXILIARYEFFECTSLOTFV alGetAuxiliaryEffectSlotfv;

        } EFX_EXTENSION_STRUCT;

        class CAudioSource;
        class CAudioStream;
        class CAudioEffect;


        class CAudioDevice : public virtual IReferenceCounted
        {
        public:
            CAudioDevice();
            virtual ~CAudioDevice();

            virtual CAudioSource* createAudioSource(CAudioStream* stream = 0);
            virtual void addAudioSource(CAudioSource* newSource);          

            virtual CAudioStream* createAudioStream(const c8* filename, bool loadToMemory = false);

            virtual void playAll();
            virtual void clear();

            void playBuffer(char* buffer, long nBytes);

            virtual void setListenerPosition(const core::vector3d<float>& newPosition);
            virtual void setListenerVelocity(const core::vector3d<float>& newVelocity);
            virtual void setListenerOrientation(const core::vector3d<float>& orient1, const core::vector3d<float>& orient2);
            void setEffect(const unsigned int& auxSlotId, const unsigned int& effectSlotId, CAudioEffect* aEffect);

            virtual u32 getNextAvailableSourceId();        

        private:
            core::array<CAudioSource*> sources;

            bool active;
            bool effectsEnabled;

            ALCcontext *sContext;
            ALCdevice *sDevice;

            u32 sourceCount;

        public:
            // OpenAL extensions
            EFX_EXTENSION_STRUCT alExt;

            ALuint effectSlot[16];
            ALuint effect[16];
            ALuint filter[16];

            unsigned int effectSlots;
            unsigned int effects;
            unsigned int filters;

            unsigned int usedEffectSlots;
            unsigned int usedEffects;
            unsigned int usedFilters;

        };
    }
}

