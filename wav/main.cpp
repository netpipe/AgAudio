
#include <iostream>
#include "./AgAudio3/CAudioDevice.h"

using namespace std;

int main(int argc, char** argv)
{
	agEngine::audio::CAudioDevice* adevice = new agEngine::audio::CAudioDevice();
	//agEngine::audio::CAudioSource* test = adevice->createAudioSource(adevice->createAudioStream("./bling.ogg", 1));
	//agEngine::audio::CAudioSource* test = adevice->createAudioSource(adevice->createAudioStream("./cAudioTheme1.ogg", 1));
	//agEngine::audio::CAudioSource* test = adevice->createAudioSource(adevice->createAudioStream("./Ring09.wav", 1));
	agEngine::audio::CAudioSource* test = adevice->createAudioSource(adevice->createAudioStream("./bling.wav", 1));
	//agEngine::audio::CAudioSource* test = adevice->createAudioSource(adevice->createAudioStream("./bling.ogg", 1));

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
