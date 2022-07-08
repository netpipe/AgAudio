#include <cstdio>

    #include "./CAudio.h"
    agEngine::Audio::AudioDriver* adevice;
    using namespace agEngine;
    using namespace Audio;

int main ( int argc, char** argv )
{
 agEngine::Audio::AudioDriver* adevice = new agEngine::Audio::AudioDriver();
 //agEngine::Audio::SoundData* soundtest =  new agEngine::Audio::LoadAudio(adevice,"./bling.ogg",1);
 //agEngine::Audio::AudioSource *test = adevice->createASource(soundtest );
 agEngine::Audio::AudioSource *test = adevice->createASource(agEngine::Audio::SoundData::LoadAudio(adevice,"./bling.ogg",1) );

 agEngine::Audio::AudioEffect * aeffect = new  agEngine::Audio::AudioEffect(EFFECT_REVERB);
 adevice->setEffect(1,EFFECT_REVERB,aeffect);

 adevice->attachAudioSource( test);

 test->play();

	while (true)
	{
		if (!test->isPlaying())
			test->play();
			//break;
		else
			adevice->playAll();
	}

		system("PAUSE");
	return 0;
}


