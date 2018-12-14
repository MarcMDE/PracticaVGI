#include "stdafx.h"
#include "Sound.h"


Sound::Sound() {

	//Constructor

}


Sound::~Sound() {

	// Destructor

}

void Sound::play() {

	if (m_play) {
		
		PlaySound(std::wstring(m_music.begin(), m_music.end()).c_str(), NULL, SND_FILENAME | SND_ASYNC);

	}

}

void Sound::stop() {

	PlaySound(NULL, NULL, NULL);

}

void Sound::toggle() {

	if (!m_play) {

		m_play = true;	
		play();
	
	} else {

		m_play = false;
		stop();

	}

}

void Sound::setOpt(bool value) {

	m_play = value;

}
