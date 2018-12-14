#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <string>
#include <iostream>

class Sound {

private:

	std::string m_music = "res/audio/music2.wav";
	bool m_play = true;

public:

	Sound();
	~Sound();

	void play();

	void stop();

	void toggle();

	void setOpt(bool value);

};

