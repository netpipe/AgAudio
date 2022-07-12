#pragma once
#include <string>
#include <map>
#include <vector>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/efx.h>
#include <irrlicht.h>

using namespace irr;

namespace agEngine
{
    namespace audio
    {
        typedef enum
        {
            EFFECT_NULL,
            EFFECT_REVERB,
            EFFECT_CHORUS,
            EFFECT_DISTORTION,
            EFFECT_ECHO,
            EFFECT_FLANGER,
            EFFECT_FREQUENCY_SHIFTER,
            EFFECT_VOCAL_MORPHER,
            EFFECT_PITCH_SHIFTER,
            EFFECT_RING_MODULATOR,
            EFFECT_AUTOWAH,
            EFFECT_COMPRESSOR,
            EFFECT_EQUALIZER,
            EFFECT_EAXREVERB
        } audioEffects;

        typedef enum
        {
            REVERB_NULL,
            REVERB_PLATE,
            REVERB_ROOM,
            REVERB_HALL,
            REVERB_AUDITORIUM,
            REVERB_ARENA,
            REVERB_HANGAR,
            REVERB_MOUNTAIN,
        } reverbType;

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

        class AudioEffect
        {
        public:
            AudioEffect(const audioEffects &effectType);
           void setReverbType(const reverbType &reverb);
        protected:
            ~AudioEffect();
        private:
            void activate(const unsigned int &auxSlot, const unsigned int &effectSlot);
            audioEffects effectType;
            ALuint effect;
            ALuint auxSlot;
        private:
            // These are all the variables used to set the different effects

            // Reverb
            float reverbDensity;
            float reverbDiffusion;
            float reverbGain;
            float reverbGainHf;
            float reverbDecayTime;
            float reverbDecayHfRatio;
            float reverbReflectionsGain;
            float reverbReflectionsDelay;
            float reverbLateReverbGain;
            float reverbLateReverbDelay;
            float reverbAirAbsorptionGainHf;
            float reverbRoomRolloffFactor;
            int reverbDecayHfLimit;

            // Chorus
            int chorusWaveform;
            int chorusPhase;
            float chorusRate;
            float chorusDepth;
            float chorusFeedback;
            float chorusDelay;

            // Distortion
            float distortionEdge;
            float distortionGain;
            float distortionLowpassCutoff;
            float distortionEQCenter;
            float distortionEQBandwidth;

            // Echo
            float echoDelay;
            float echoLRDelay;
            float echoDamping;
            float echoFeedback;
            float echoSpread;

            // Flanger
            int flangerWaveform;
            int flangerPhase;
            float flangerRate;
            float flangerDepth;
            float flangerFeedback;
            float flangerDelay;

            // Frequency Shifter
            float shifterFrequency;
            unsigned int shifterLeftDirection;
            unsigned int shifterRightDirection;

            // Vocal Morpher
            unsigned int morpherPhonemeA;
            unsigned int morpherPhonemeB;
            int morpherPhonemeACoarseTuning;
            int morpherPhonemeBCoarseTuning;
            unsigned int morpherWaveform;
            float morpherRate;

            // Pitch Shifter
            int shifterCoarseTune;
            int shifterFineTune;

            // Ring Modulator
            float ringModulatorFrequency;
            float ringModulatorHighpassCutoff;
            int ringModulatorWaveform;

            // Autowah
            float autowahAttackTime;
            float autowahReleaseTime;
            float autowahResonance;
            float autowahPeakGain;

            // Equalizer
            float eqLowGain;
            float eqLowCutoff;
            float eqMid1Gain;
            float eqMid1Center;
            float eqMid1Width;
            float eqMid2Gain;
            float eqMid2Center;
            float eqMid2Width;
            float eqHighGain;
            float eqHighCutoff;

            // Compressor
            int compressorOnOff;
        };
    }
}

