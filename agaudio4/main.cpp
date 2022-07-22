
#include <iostream>
#include "./AgAudio3/CAudioDevice.h"
#include "./AgAudio3/CAudioEffect.h"

using namespace std;

int main(int argc, char** argv)
{
	agEngine::audio::CAudioDevice* adevice = new agEngine::audio::CAudioDevice();
	//agEngine::audio::CAudioSource* test = adevice->createAudioSource(adevice->createAudioStream("./bling.ogg", 1));
	//agEngine::audio::CAudioSource* test = adevice->createAudioSource(adevice->createAudioStream("./cAudioTheme1.ogg", 1));	
	//agEngine::audio::CAudioSource* test = adevice->createAudioSource(adevice->createAudioStream("./Ring09.wav", 1));
	//agEngine::audio::CAudioSource* test = adevice->createAudioSource(adevice->createAudioStream("./test.wav", 1));
	agEngine::audio::CAudioSource* test = adevice->createAudioSource(adevice->createAudioStream("./bling.wav", 1));
	//agEngine::audio::CAudioSource* test = adevice->createAudioSource(adevice->createAudioStream("./001.mp3", 1));
	//agEngine::audio::CAudioSource* test = adevice->createAudioSource(adevice->createAudioStream("./test.xm", 1));
	//agEngine::audio::CAudioSource* test = adevice->createAudioSource(adevice->createAudioStream("./REGGAE.MID", 1));


	agEngine::audio::CAudioEffect* aeffect = new  agEngine::audio::CAudioEffect(agEngine::audio::audioEffects::EFFECT_REVERB);
	adevice->setEffect(0, agEngine::audio::audioEffects::EFFECT_REVERB, aeffect);

	aeffect->setReverbType(agEngine::audio::reverbType::REVERB_PLATE);
	test->passThroughEffectSlot(0);	

	while (true)
	{
		if (!test->isPlaying())
			test->play();
		else
			adevice->playAll();		
	}

	system("PAUSE");

	return 0;
}