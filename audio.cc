#include "audio.h"

AudioManager::AudioManager()
{
}
void AudioManager::add(const char *name)
{
	Sound s = LoadSound(name);
	this->sounds[name] = s;
}
AudioManager::~AudioManager()
{
	cout << "Unloading Sounds" << endl;
	for (auto i : this->sounds)
	{
		UnloadSound(i.second);
		cout << i.first << endl;
	}
}
void AudioManager::play(string name)
{
	if (sounds.count(name) > 0)
	{
		PlaySound(sounds[name]);
	}
}