#include "CAudioDevice.h"

#include <string>

#include "CAudioOgg.h"
#include "CAudioWav.h"
#include "CAudioMp3.h"
#include "CAudioXm.h"
#include "CAudioMidi.h"

#include "CAudioEffect.h"

namespace agEngine
{
    namespace audio
    {
        CAudioDevice::CAudioDevice()
        : active(true), sourceCount(1)
        {
            if (!(sDevice = alcOpenDevice(NULL)))
            {
                active = false;
            }

            // Check for effects extension
            effectsEnabled = (alcIsExtensionPresent(sDevice, "ALC_EXT_EFX") == AL_TRUE);
            if (effectsEnabled)
            {
                ALint attribs[4];
                attribs[0] = ALC_MAX_AUXILIARY_SENDS;
                attribs[1] = 4;
                sContext = alcCreateContext(sDevice, attribs);
                alcMakeContextCurrent(sContext);

                ALCint sends = 0;
                alcGetIntegerv(sDevice, ALC_MAX_AUXILIARY_SENDS, 1, &sends);

                // Get the functions from the openAL dll.
                alExt.alGenEffects = (LPALGENEFFECTS)alGetProcAddress("alGenEffects");
                alExt.alDeleteEffects = (LPALDELETEEFFECTS)alGetProcAddress("alDeleteEffects");
                alExt.alIsEffect = (LPALISEFFECT)alGetProcAddress("alIsEffect");
                alExt.alEffecti = (LPALEFFECTI)alGetProcAddress("alEffecti");
                alExt.alEffectiv = (LPALEFFECTIV)alGetProcAddress("alEffectiv");
                alExt.alEffectf = (LPALEFFECTF)alGetProcAddress("alEffectf");
                alExt.alEffectfv = (LPALEFFECTFV)alGetProcAddress("alEffectfv");
                alExt.alGetEffecti = (LPALGETEFFECTI)alGetProcAddress("alGetEffecti");
                alExt.alGetEffectiv = (LPALGETEFFECTIV)alGetProcAddress("alGetEffectiv");
                alExt.alGetEffectf = (LPALGETEFFECTF)alGetProcAddress("alGeteffectf");
                alExt.alGetEffectfv = (LPALGETEFFECTFV)alGetProcAddress("alGeteffectfv");

                alExt.alGenFilters = (LPALGENFILTERS)alGetProcAddress("alGenFilters");
                alExt.alDeleteFilters = (LPALDELETEFILTERS)alGetProcAddress("alDeleteFilters");
                alExt.alIsFilter = (LPALISFILTER)alGetProcAddress("alIsFilter");
                alExt.alFilteri = (LPALFILTERI)alGetProcAddress("alFilteri");
                alExt.alFilteriv = (LPALFILTERIV)alGetProcAddress("alFilteriv");
                alExt.alFilterf = (LPALFILTERF)alGetProcAddress("alFilterf");
                alExt.alFilterfv = (LPALFILTERFV)alGetProcAddress("alFilterfv");
                alExt.alGetFilteri = (LPALGETFILTERI)alGetProcAddress("alGetFilteri");
                alExt.alGetFilteriv = (LPALGETFILTERIV)alGetProcAddress("alGetFilteriv");
                alExt.alGetFilterf = (LPALGETFILTERF)alGetProcAddress("alGetFilterf");
                alExt.alGetFilterfv = (LPALGETFILTERFV)alGetProcAddress("alGetFilterfv");

                alExt.alGenAuxiliaryEffectSlots = (LPALGENAUXILIARYEFFECTSLOTS)alGetProcAddress("alGenAuxiliaryEffectSlots");
                alExt.alDeleteAuxiliaryEffectSlots = (LPALDELETEAUXILIARYEFFECTSLOTS)alGetProcAddress("alDeleteAuxiliaryEffectSlots");
                alExt.alIsAuxiliaryEffectSlot = (LPALISAUXILIARYEFFECTSLOT)alGetProcAddress("alIsAuxiliaryEffectSlot");
                alExt.alAuxiliaryEffectSloti = (LPALAUXILIARYEFFECTSLOTI)alGetProcAddress("alAuxiliaryEffectSloti");
                alExt.alAuxiliaryEffectSlotiv = (LPALAUXILIARYEFFECTSLOTIV)alGetProcAddress("alAuxiliaryEffectSlotiv");
                alExt.alAuxiliaryEffectSlotf = (LPALAUXILIARYEFFECTSLOTF)alGetProcAddress("alAuxiliaryEffectSlotf");
                alExt.alAuxiliaryEffectSlotfv = (LPALAUXILIARYEFFECTSLOTFV)alGetProcAddress("alAuxiliaryEffectSlotfv");
                alExt.alGetAuxiliaryEffectSloti = (LPALGETAUXILIARYEFFECTSLOTI)alGetProcAddress("alGetAuxiliaryEffectSloti");
                alExt.alGetAuxiliaryEffectSlotiv = (LPALGETAUXILIARYEFFECTSLOTIV)alGetProcAddress("alGetAuxiliaryEffectSlotiv");
                alExt.alGetAuxiliaryEffectSlotf = (LPALGETAUXILIARYEFFECTSLOTF)alGetProcAddress("alGetAuxiliaryEffectSlotf");
                alExt.alGetAuxiliaryEffectSlotfv = (LPALGETAUXILIARYEFFECTSLOTFV)alGetProcAddress("alGetAuxiliaryEffectSlotfv");

                if (!alExt.alGenEffects || !alExt.alDeleteEffects || !alExt.alIsEffect)
                {
                    effectsEnabled = false;
                }
                else
                {
                    for (effectSlots = 0; effectSlots < 16; ++effectSlots)
                    {
                        alExt.alGenAuxiliaryEffectSlots(1, &effectSlot[effectSlots]);
                        if (alGetError() != AL_NO_ERROR)
                            break;
                    }

                    for (effects = 0; effects < 16; ++effects)
                    {
                        alExt.alGenEffects(1, &effect[effects]);
                        if (alGetError() != AL_NO_ERROR)
                            break;
                    }

                    for (filters = 0; filters < 16; ++filters)
                    {
                        alExt.alGenFilters(1, &filter[filters]);
                        if (alGetError() != AL_NO_ERROR)
                            break;
                    }
                }
            }
            else
            {
                sContext = alcCreateContext(sDevice, NULL);
                alcMakeContextCurrent(sContext);
            }

            ALfloat orient[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };
            alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
            alListenerfv(AL_ORIENTATION, orient);
            alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);

            // Clear the error stack
            alGetError();
        }

        CAudioDevice::~CAudioDevice()
        {
            clear();
        }

        CAudioSource* CAudioDevice::createAudioSource(CAudioStream* stream)
        {
            CAudioSource* nSrc = new CAudioSource(this, stream);
            nSrc->setSourceId(sourceCount);
            ++sourceCount;
            sources.push_back(nSrc);
            return nSrc;
        }

        void CAudioDevice::addAudioSource(CAudioSource* newSource)
        {
            newSource->setSourceId(sourceCount);
            ++sourceCount;
            sources.push_back(newSource);
            newSource->grab();
        }

        CAudioStream* CAudioDevice::createAudioStream(const c8* filename, bool loadToMemory)
        {
            std::string filename_str = filename;
            std::string extension = filename_str.substr(filename_str.rfind(".") + 1);            

            for (size_t i = 0; i < strlen(extension.c_str()); i++) 
            {             
                char ch = tolower(extension[i]);
                extension[i] = ch;
            }  

            CAudioData* audioData = NULL;

            if (extension == "ogg")
            {
                audioData = new CAudioOgg(filename, loadToMemory);
            }
            else if (extension == "wav")
            {
                audioData = new CAudioWav(filename, loadToMemory);
            }
            else if (extension == "mp3")
            {
                audioData = new CAudioMp3(filename, loadToMemory);
            }
            else if (extension == "xm")
            {
                audioData = new CAudioXm(filename, loadToMemory);
            }
            else if (extension == "mid")
            {
                audioData = new CAudioMidi(filename, loadToMemory);
            }

            if (audioData != NULL)
            {
                CAudioStream* audStream = new CAudioStream(audioData);
                return audStream;
            }
             
            return NULL;
        }

        void CAudioDevice::playAll()
        {
            for (u32 i = 0; i < sources.size(); ++i)
                sources[i]->updateBuffer(false);
        }

        void CAudioDevice::playBuffer(char* buffer, long nBytes)
        {
            for (u32 i = 0; i < sources.size(); ++i)
                sources[i]->updateMemoryBuffer(false, buffer, nBytes);
        }

        void CAudioDevice::clear()
        {
            for (u32 i = 0; i < sources.size(); ++i)
                sources[i]->drop();

            sources.clear();
        }

        u32 CAudioDevice::getNextAvailableSourceId()
        {
            u32 temp = sourceCount;
            ++sourceCount;
            return temp;
        }

        void CAudioDevice::setListenerPosition(const core::vector3d<float>& newPosition)
        {
            alListener3f(AL_POSITION, newPosition.X, newPosition.Y, newPosition.Z);
        }

        void CAudioDevice::setListenerVelocity(const core::vector3d<float>& newVelocity)
        {
            alListener3f(AL_VELOCITY, newVelocity.X, newVelocity.Y, newVelocity.Z);
        }

        void CAudioDevice::setListenerOrientation(const core::vector3d<float>& orient1, const core::vector3d<float>& orient2)
        {
            ALfloat orient[] = {orient1.X, orient1.Y, orient1.Z, orient2.X, orient2.Y, orient2.Z};
            alListenerfv(AL_ORIENTATION, orient);
        }

        void CAudioDevice::setEffect(const unsigned int& auxSlotId, const unsigned int& effectSlotId, CAudioEffect* aEffect)
        {
            if (auxSlotId > effectSlots || effectSlotId > effects)
                return;

            aEffect->device = this;
            aEffect->activate(effectSlot[auxSlotId], effect[effectSlotId]);
        }
    }
}
