#include <string>
#include "./include/raylib.h"
#include <map>
#include <iostream>
#pragma once
using namespace std;

class AudioManager {
	map<string,Sound> sounds;
	public:
	AudioManager(){
	}
	void add(const char* name){
		Sound s = LoadSound(name);
		this->sounds[name] = s;
	}
	~AudioManager(){
		cout << "Unloading Sounds" << endl;
		for(auto i: this->sounds){
			UnloadSound(i.second);
			cout << i.first << endl;
		}
	}
	void play(string name){
		if (sounds.count(name)>0){
			PlaySound(sounds[name]);
		}
	}
};