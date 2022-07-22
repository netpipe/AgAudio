#include "CAudioEffect.h"

namespace agEngine
{
    namespace audio
    {
        CAudioEffect::CAudioEffect(const audioEffects& eType)
        {
            effectType = eType;

            // Default settings for effects

            // Reverb
            reverbDensity = 1.0f;
            reverbDiffusion = 1.0f;
            reverbGain = 0.32f;
            reverbGainHf = 0.89f;
            reverbDecayTime = 1.49f;
            reverbDecayHfRatio = 0.83f;
            reverbReflectionsGain = 0.5f;
            reverbReflectionsDelay = 0.007f;
            reverbLateReverbGain = 1.26f;
            reverbLateReverbDelay = 0.011f;
            reverbAirAbsorptionGainHf = 0.994f;
            reverbRoomRolloffFactor = 0.0f;
            reverbDecayHfLimit = AL_TRUE;

            // Chorus
            chorusWaveform = AL_CHORUS_WAVEFORM_TRIANGLE;
            chorusPhase = 90;
            chorusRate = 1.1f;
            chorusDepth = 0.1f;
            chorusFeedback = 0.25f;
            chorusDelay = 0.016f;

            // Distortion
            distortionEdge = 0.2f;
            distortionGain = 0.05f;
            distortionLowpassCutoff = 8000.0f;
            distortionEQCenter = 3600.0f;
            distortionEQBandwidth = 3600.0f;

            // Echo
            echoDelay = 0.1f;
            echoLRDelay = 0.1f;
            echoDamping = 0.5f;
            echoFeedback = 0.5f;
            echoSpread = -1.0f;

            // Flanger
            flangerWaveform = AL_FLANGER_WAVEFORM_TRIANGLE;
            flangerPhase = 0;
            flangerRate = 0.27f;
            flangerDepth = 1.0f;
            flangerFeedback = -0.5f;
            flangerDelay = 0.002f;

            // Frequency Shifter
            shifterFrequency = 0.0f;
            shifterLeftDirection = 0;
            shifterRightDirection = 0;

            // Vocal Morpher
            morpherPhonemeA = 0;
            morpherPhonemeB = 10;
            morpherPhonemeACoarseTuning = 0;
            morpherPhonemeBCoarseTuning = 0;
            morpherWaveform = 0;
            morpherRate = 1.41f;

            // Pitch shifter
            shifterCoarseTune = 12;
            shifterFineTune = 0;

            // Ring Modulator
            ringModulatorFrequency = 440.0f;
            ringModulatorHighpassCutoff = 800.0f;
            ringModulatorWaveform = 0;

            // AutoWAH
            autowahAttackTime = 0.06f;
            autowahReleaseTime = 0.06f;
            autowahResonance = 1000.0f;
            autowahPeakGain = 11.22f;

            // Compressor
            compressorOnOff = 1;

            // Equalizer
            eqLowGain = 1.0f;
            eqLowCutoff = 200.0f;
            eqMid1Gain = 1.0f;
            eqMid1Center = 500.0f;
            eqMid1Width = 1.0f;
            eqMid2Gain = 1.0f;
            eqMid2Center = 3000.0f;
            eqMid2Width = 1.0f;
            eqHighGain = 1.0f;
            eqHighCutoff = 6000.0f;
        }

        CAudioEffect::~CAudioEffect()
        {

        }

        // Activates the audio effect type
        void CAudioEffect::activate(const unsigned int& effectSlot, const unsigned int& effects)
        {
            auxSlot = effectSlot;
            effect = device->effect[effects];
            switch (effectType)
            {
            case EFFECT_REVERB:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_REVERB);
                device->alExt.alEffectf(effect, AL_REVERB_DENSITY, reverbDensity);
                device->alExt.alEffectf(effect, AL_REVERB_DIFFUSION, reverbDiffusion);
                device->alExt.alEffectf(effect, AL_REVERB_GAIN, reverbGain);
                device->alExt.alEffectf(effect, AL_REVERB_GAINHF, reverbGainHf);
                device->alExt.alEffectf(effect, AL_REVERB_DECAY_TIME, reverbDecayTime);
                device->alExt.alEffectf(effect, AL_REVERB_DECAY_HFRATIO, reverbDecayHfRatio);
                device->alExt.alEffectf(effect, AL_REVERB_REFLECTIONS_GAIN, reverbReflectionsGain);
                device->alExt.alEffectf(effect, AL_REVERB_REFLECTIONS_DELAY, reverbReflectionsDelay);
                device->alExt.alEffectf(effect, AL_REVERB_LATE_REVERB_GAIN, reverbLateReverbGain);
                device->alExt.alEffectf(effect, AL_REVERB_LATE_REVERB_DELAY, reverbLateReverbDelay);
                device->alExt.alEffectf(effect, AL_REVERB_AIR_ABSORPTION_GAINHF, reverbAirAbsorptionGainHf);
                device->alExt.alEffectf(effect, AL_REVERB_ROOM_ROLLOFF_FACTOR, reverbRoomRolloffFactor);
                device->alExt.alEffecti(effect, AL_REVERB_DECAY_HFLIMIT, reverbDecayHfLimit);
                break;
            case EFFECT_CHORUS:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_REVERB);
                device->alExt.alEffecti(effect, AL_CHORUS_WAVEFORM, chorusWaveform);
                device->alExt.alEffecti(effect, AL_CHORUS_PHASE, chorusPhase);
                device->alExt.alEffectf(effect, AL_CHORUS_RATE, chorusRate);
                device->alExt.alEffectf(effect, AL_CHORUS_DEPTH, chorusDepth);
                device->alExt.alEffectf(effect, AL_CHORUS_FEEDBACK, chorusFeedback);
                device->alExt.alEffectf(effect, AL_CHORUS_DELAY, chorusDelay);
                break;
            case EFFECT_DISTORTION:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_REVERB);
                device->alExt.alEffectf(effect, AL_DISTORTION_EDGE, distortionEdge);
                device->alExt.alEffectf(effect, AL_DISTORTION_GAIN, distortionGain);
                device->alExt.alEffectf(effect, AL_DISTORTION_LOWPASS_CUTOFF, distortionLowpassCutoff);
                device->alExt.alEffectf(effect, AL_DISTORTION_EQCENTER, distortionEQCenter);
                device->alExt.alEffectf(effect, AL_DISTORTION_EQBANDWIDTH, distortionEQBandwidth);
                break;
            case EFFECT_ECHO:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_ECHO);
                device->alExt.alEffectf(effect, AL_ECHO_DELAY, echoDelay);
                device->alExt.alEffectf(effect, AL_ECHO_LRDELAY, echoLRDelay);
                device->alExt.alEffectf(effect, AL_ECHO_DAMPING, echoDamping);
                device->alExt.alEffectf(effect, AL_ECHO_FEEDBACK, echoFeedback);
                device->alExt.alEffectf(effect, AL_ECHO_SPREAD, echoSpread);
                break;
            case EFFECT_FLANGER:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_FLANGER);
                device->alExt.alEffecti(effect, AL_FLANGER_WAVEFORM, flangerWaveform);
                device->alExt.alEffecti(effect, AL_FLANGER_PHASE, flangerPhase);
                device->alExt.alEffectf(effect, AL_FLANGER_RATE, flangerRate);
                device->alExt.alEffectf(effect, AL_FLANGER_DEPTH, flangerDepth);
                device->alExt.alEffectf(effect, AL_FLANGER_FEEDBACK, flangerFeedback);
                device->alExt.alEffectf(effect, AL_FLANGER_DELAY, flangerDelay);
                break;
            case EFFECT_FREQUENCY_SHIFTER:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_FREQUENCY_SHIFTER);
                device->alExt.alEffectf(effect, AL_FREQUENCY_SHIFTER_FREQUENCY, shifterFrequency);
                device->alExt.alEffecti(effect, AL_FREQUENCY_SHIFTER_LEFT_DIRECTION, shifterLeftDirection);
                device->alExt.alEffecti(effect, AL_FREQUENCY_SHIFTER_RIGHT_DIRECTION, shifterRightDirection);
                break;
            case EFFECT_VOCAL_MORPHER:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_VOCAL_MORPHER);
                device->alExt.alEffecti(effect, AL_VOCAL_MORPHER_PHONEMEA, morpherPhonemeA);
                device->alExt.alEffecti(effect, AL_VOCAL_MORPHER_PHONEMEB, morpherPhonemeB);
                device->alExt.alEffecti(effect, AL_VOCAL_MORPHER_PHONEMEA_COARSE_TUNING, morpherPhonemeACoarseTuning);
                device->alExt.alEffecti(effect, AL_VOCAL_MORPHER_PHONEMEB_COARSE_TUNING, morpherPhonemeBCoarseTuning);
                device->alExt.alEffecti(effect, AL_VOCAL_MORPHER_WAVEFORM, morpherWaveform);
                device->alExt.alEffectf(effect, AL_VOCAL_MORPHER_RATE, morpherRate);
                break;
            case EFFECT_PITCH_SHIFTER:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_PITCH_SHIFTER);
                device->alExt.alEffecti(effect, AL_PITCH_SHIFTER_COARSE_TUNE, shifterCoarseTune);
                device->alExt.alEffecti(effect, AL_PITCH_SHIFTER_FINE_TUNE, shifterFineTune);
                break;
            case EFFECT_RING_MODULATOR:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_RING_MODULATOR);
                device->alExt.alEffectf(effect, AL_RING_MODULATOR_FREQUENCY, ringModulatorFrequency);
                device->alExt.alEffectf(effect, AL_RING_MODULATOR_HIGHPASS_CUTOFF, ringModulatorHighpassCutoff);
                device->alExt.alEffecti(effect, AL_RING_MODULATOR_WAVEFORM, ringModulatorWaveform);
                break;
            case EFFECT_AUTOWAH:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_AUTOWAH);
                device->alExt.alEffectf(effect, AL_AUTOWAH_ATTACK_TIME, autowahAttackTime);
                device->alExt.alEffectf(effect, AL_AUTOWAH_RELEASE_TIME, autowahReleaseTime);
                device->alExt.alEffectf(effect, AL_AUTOWAH_RESONANCE, autowahResonance);
                device->alExt.alEffectf(effect, AL_AUTOWAH_PEAK_GAIN, autowahPeakGain);
                break;
            case EFFECT_EQUALIZER:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_EQUALIZER);
                device->alExt.alEffectf(effect, AL_EQUALIZER_LOW_GAIN, eqLowGain);
                device->alExt.alEffectf(effect, AL_EQUALIZER_LOW_CUTOFF, eqLowCutoff);
                device->alExt.alEffectf(effect, AL_EQUALIZER_MID1_GAIN, eqMid1Gain);
                device->alExt.alEffectf(effect, AL_EQUALIZER_MID1_CENTER, eqMid1Center);
                device->alExt.alEffectf(effect, AL_EQUALIZER_MID1_WIDTH, eqMid1Width);
                device->alExt.alEffectf(effect, AL_EQUALIZER_MID2_GAIN, eqMid2Gain);
                device->alExt.alEffectf(effect, AL_EQUALIZER_MID2_CENTER, eqMid2Center);
                device->alExt.alEffectf(effect, AL_EQUALIZER_MID2_WIDTH, eqMid2Width);
                device->alExt.alEffectf(effect, AL_EQUALIZER_HIGH_GAIN, eqHighGain);
                device->alExt.alEffectf(effect, AL_EQUALIZER_HIGH_CUTOFF, eqHighCutoff);
                break;
            case EFFECT_COMPRESSOR:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_COMPRESSOR);
                device->alExt.alEffecti(effect, AL_COMPRESSOR_ONOFF, compressorOnOff);
                break;
            case EFFECT_NULL:
            default:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_NULL);
                break;
            }            

            device->alExt.alAuxiliaryEffectSloti(auxSlot, AL_EFFECTSLOT_EFFECT, effect);

            if (alGetError() != AL_NO_ERROR)
            {
               // *device->output << "Problem loading the effect" << "\n";
            }
        }

        void CAudioEffect::setReverbType(const reverbType& reverb)
        {
            switch (reverb)
            {
            case REVERB_PLATE:
                break;
            case REVERB_NULL:
            default:
                break;
            }
        }
    }
}