#include "Sound.h"

Sound::Sound(std::string sound_path, std::string file_name, Timer& t) :t(t) , mute(false), volumeLvl(0.5), _volumecopy(volumeLvl)
{
	std::fstream plik;
	plik.open(sound_path+file_name, std::ios::in);
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
	engine->setSoundVolume((irrklang::ik_f32)volumeLvl);
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
			t.delay(x, (double)sound.time, false);

		}
	}

}

void Sound::PlayGameTheme(std::string sound_name)
{
	Play(sound_name, true);
}

void Sound::DownToZero()
{
	if (volumeLvl > 0)
		volumeLvl -= 0.005;
	if (volumeLvl < 0)
		volumeLvl = 0;

	engine->setSoundVolume((irrklang::ik_f32)volumeLvl);
}

void Sound::UpToMax()
{
	if (volumeLvl < _volumecopy)
		volumeLvl += 0.002;
	if (volumeLvl > _volumecopy)
		volumeLvl = _volumecopy;

	engine->setSoundVolume((irrklang::ik_f32)volumeLvl);
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
	
}

void Sound::VolumeUp()
{
	if (volumeLvl < 1.0)
	{
	volumeLvl += 0.05; 
	engine->setSoundVolume((irrklang::ik_f32)volumeLvl); 
	}
	_volumecopy = volumeLvl;
}

void Sound::VolumeDown()
{	
	if (volumeLvl > 0.0)
	{
		volumeLvl -= 0.05; 
		engine->setSoundVolume((irrklang::ik_f32)volumeLvl); 
	}
	_volumecopy = volumeLvl;
}

bool Sound::isPlaying()
{
	if (volumeLvl > 0)
		return true;
	else
		return false;


}

bool Sound::isFull()
{
	if (volumeLvl < _volumecopy)
		return false;
	else
		return true;
}

void Sound::Stop()
{
	engine->stopAllSounds();
}
