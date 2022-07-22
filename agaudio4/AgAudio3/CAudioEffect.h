#pragma once

#include <irrlicht-1.8.5/irrlicht.h>
#include <OpenAL1.1/al.h>
#include <OpenAL1.1/alc.h>
#include <OpenAL1.1/efx.h>

#include "CAudioDevice.h"


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


        class CAudioEffect : public virtual IReferenceCounted
        {
        public:
            CAudioEffect(const audioEffects& effectType);
            virtual ~CAudioEffect();

            void setSlots(u32 auxSlot, const unsigned int& effectSlot);
            void activate(const unsigned int& auxSlot, const unsigned int& effectSlot);
            void setReverbType(const reverbType& reverb);
        
            audioEffects effectType;
           
            CAudioDevice* device;
            ALuint effect;
            ALuint auxSlot;            

        protected:
            // These are all the variables used to set the different effects

            // Reverb
            f32 reverbDensity;
            f32 reverbDiffusion;
            f32 reverbGain;
            f32 reverbGainHf;
            f32 reverbDecayTime;
            f32 reverbDecayHfRatio;
            f32 reverbReflectionsGain;
            f32 reverbReflectionsDelay;
            f32 reverbLateReverbGain;
            f32 reverbLateReverbDelay;
            f32 reverbAirAbsorptionGainHf;
            f32 reverbRoomRolloffFactor;
            s32 reverbDecayHfLimit;

            // Chorus
            s32 chorusWaveform;
            s32 chorusPhase;
            f32 chorusRate;
            f32 chorusDepth;
            f32 chorusFeedback;
            f32 chorusDelay;

            // Distortion
            f32 distortionEdge;
            f32 distortionGain;
            f32 distortionLowpassCutoff;
            f32 distortionEQCenter;
            f32 distortionEQBandwidth;

            // Echo
            f32 echoDelay;
            f32 echoLRDelay;
            f32 echoDamping;
            f32 echoFeedback;
            f32 echoSpread;

            // Flanger
            s32 flangerWaveform;
            s32 flangerPhase;
            f32 flangerRate;
            f32 flangerDepth;
            f32 flangerFeedback;
            f32 flangerDelay;

            // Frequency Shifter
            f32 shifterFrequency;
            u32 shifterLeftDirection;
            u32 shifterRightDirection;

            // Vocal Morpher
            u32 morpherPhonemeA;
            u32 morpherPhonemeB;
            s32 morpherPhonemeACoarseTuning;
            s32 morpherPhonemeBCoarseTuning;
            u32 morpherWaveform;
            f32 morpherRate;

            // Pitch Shifter
            s32 shifterCoarseTune;
            s32 shifterFineTune;

            // Ring Modulator
            f32 ringModulatorFrequency;
            f32 ringModulatorHighpassCutoff;
            s32 ringModulatorWaveform;

            // Autowah
            f32 autowahAttackTime;
            f32 autowahReleaseTime;
            f32 autowahResonance;
            f32 autowahPeakGain;

            // Equalizer
            f32 eqLowGain;
            f32 eqLowCutoff;
            f32 eqMid1Gain;
            f32 eqMid1Center;
            f32 eqMid1Width;
            f32 eqMid2Gain;
            f32 eqMid2Center;
            f32 eqMid2Width;
            f32 eqHighGain;
            f32 eqHighCutoff;

            // Compressor
            s32 compressorOnOff;
        };
    }
}

