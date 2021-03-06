#ifndef SOUND_H
#define SOUND_H

//Our heders
#include "Utility/Timer.h"
//Irklang <3
#include <irrKlang.h>

//Std libs
#include <map>
#include <fstream>
#include <string>

class Sound
{
public:
	struct snd
	{
		snd() = default;
		snd(std::string s, bool b, size_t secs) : path(s), play(b), time(secs) {};
		snd(const snd&) = default;
		std::string path;
		bool play;
		size_t time;
	};
public:
	Sound() = delete;
	Sound(std::string sound_path, std::string file_name, Timer& t);
	~Sound();
public:
	void Play(std::string x, bool looped=false);
	void Refresh();
	void Mute(bool mute);
	void VolumeUp();
	void VolumeDown();
	double getVolume() { return volumeLvl; };
	bool getMute() { return mute; };
	bool isPlaying();
	bool isFull();
	void PlayGameTheme(std::string sound_name);
	void DownToZero();
	void UpToMax();
	void Stop();
private:
	std::map<std::string, snd> sounds;
	Timer& t;
	irrklang::ISoundEngine* engine;
	bool mute;
	double volumeLvl;
	double _volumecopy;
};

#endif