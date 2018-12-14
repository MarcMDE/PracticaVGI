#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <string>
#include <iostream>

class Sound {

private:

	std::string m_music = "res/audio/music.wav";
	std::string m_sound = "res/audio/car.wav";
	bool m_Pmusic = true;
	bool m_Psound = true;

public:

	Sound();
	~Sound();

	void playSound();
	void playMusic();

	void stopMusic();
	void stopSound();

	void toggleMusic();
	void toggleSound();

	void setMusicOpt(bool value);
	void setSoundOpt(bool value);

};

