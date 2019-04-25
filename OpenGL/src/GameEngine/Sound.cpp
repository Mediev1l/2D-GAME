#include "Sound.h"

Sound::Sound(std::string sound_path, Timer& t) :t(t) , mute(true), volumeLvl(1.0)
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
	PlayGameTheme();
}

Sound::~Sound()
{
	engine->drop();
}

void Sound::Play(std::string x, bool looped)
{
	if (!mute)
	{

		auto& sound = sounds[x];
		if (sound.play == false)
		{
			sound.play = true;
			engine->play2D(sound.path.c_str(), looped);
			t.delay(x, sound.time, false);

		}
	}

}

void Sound::PlayGameTheme()
{
	Play("main", true);
}

void Sound::Refresh()
{
	for (auto& snd : sounds)
	{
		if (!t.CheckState(snd.first))
		{
			snd.second.play = false;
		}
	}
}

void Sound::Mute(bool mute)
{
	this->mute = mute;

	if (this->mute == true)
		Stop();
	else
		PlayGameTheme();
}

void Sound::VolumeUp()
{
	if (volumeLvl < 1.0)
	{
	volumeLvl += 0.05; 
	engine->setSoundVolume((irrklang::ik_f32)volumeLvl); 
	}
}

void Sound::VolumeDown()
{	
	if (volumeLvl > 0.0)
	{
		volumeLvl -= 0.05; 
		engine->setSoundVolume((irrklang::ik_f32)volumeLvl); 
	}
}

void Sound::Stop()
{
	engine->stopAllSounds();
}
