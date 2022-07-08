#include <cstdio>

    #include "./CAudio.h"
    agEngine::Audio::AudioDriver* adevice;

int main ( int argc, char** argv )
{

 agEngine::Audio::AudioDriver* adevice = new agEngine::Audio::AudioDriver();

 //agEngine::Audio::SoundData* soundtest =  new agEngine::Audio::LoadAudio(adevice,"./bling.ogg",1);

 //agEngine::Audio::AudioSource *test = adevice->createASource(soundtest );
 agEngine::Audio::AudioSource *test = adevice->createASource(agEngine::Audio::SoundData::LoadAudio(adevice,"./bling.ogg",1) );

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

//while (1){
 //   if (!test->isPlaying()) {
      //  test3->setLoop(0);
      //  test3->play();
   //      adevice->playAll();
  //    }

//}

		system("PAUSE");
	return 0;
}


