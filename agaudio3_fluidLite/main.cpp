
#include <iostream>
#include <fluidlite.h>
#include "./AgAudio3/CAudioDevice.h"

using namespace std;

#define SAMPLE_RATE 44100
#define SAMPLE_SIZE 2 //4: Float Buffer   2: Signed Int Buffer
#define NUM_FRAMES SAMPLE_RATE
#define NUM_CHANNELS 2   //cAudioTheme1.ogg 2   //bling.ogg  1
#define NUM_SAMPLES (NUM_FRAMES * NUM_CHANNELS)
#define TIME_INTERVAL 1000000 //1500000:duration

int main(int argc, char** argv)
{
	fluid_settings_t* settings = new_fluid_settings();
	fluid_synth_t* synth = new_fluid_synth(settings);
	int res = fluid_synth_sfload(synth, "soundfont.sf2", 1);

	double dlength = (double)(SAMPLE_RATE * NUM_CHANNELS * SAMPLE_SIZE) * TIME_INTERVAL / 1000000;
	long length = (long)dlength;
	char* audio_buf = (char*)calloc(1, length);

	agEngine::audio::CAudioDevice* adevice = new agEngine::audio::CAudioDevice();
	agEngine::audio::CAudioSource* test = adevice->createAudioSource(adevice->createAudioStream("./cAudioTheme1.ogg", 1));
	//agEngine::audio::CAudioSource* test = adevice->createAudioSource(adevice->createAudioStream("./bling.ogg", 1));

	while (true)
	{
		int nKey = 60 + rand() % 30;
		fluid_synth_noteon(synth, 0, nKey, 127);
		fluid_synth_write_s16(synth, SAMPLE_RATE, audio_buf, 0, NUM_CHANNELS, audio_buf, 1, NUM_CHANNELS);
		fluid_synth_noteoff(synth, 0, 60);

		if (!test->isPlaying())
			test->playFirstBuffer(audio_buf, length);
		else
			adevice->playBuffer(audio_buf, length);
	}

	system("PAUSE");

	free(audio_buf);

	delete_fluid_synth(synth);
	delete_fluid_settings(settings);

	return 0;
}
