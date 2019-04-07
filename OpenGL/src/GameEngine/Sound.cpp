#include "Sound.h"

Sound::Sound(std::string sound_path, Timer& t) :t(t) , mute(false)
{
	std::fstream plik;
	plik.open(sound_path+"sounds.txt", std::ios::in);
	size_t nSounds;
	plik >> nSounds;

	std::string name;
	std::string path;
	std::size_t secs;
	for (size_t i = 0; i < nSounds; ++i)
	{
		plik >> name; plik >> path; plik >> secs;
		sounds.emplace(name,snd(sound_path+path,false,secs));
	}
	engine = irrklang::createIrrKlangDevice();
	Play("start");
}

Sound::~Sound()
{
	engine->drop();
}

void Sound::Play(std::string x)
{
	if (!mute)
	{
		auto& sound = sounds[x];
		if (sound.play == false)
		{
			sound.play = true;
			engine->play2D(sound.path.c_str());
			t.delay(x, sound.time, false);
	
		}
	}
}

void Sound::Refresh()
{
	for (auto& snd : sounds)
	{
		if (!t.CheckState(snd.first))
		{
			Stop(snd.second);
		}
	}
}

void Sound::Stop(snd& snd)
{
	snd.play = false;
	//if(snd.engine != nullptr) snd.engine->drop();
}
