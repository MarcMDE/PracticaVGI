#include "stdafx.h"
#include "Sound.h"


Sound::Sound() {

	//Constructor

}


Sound::~Sound() {

	// Destructor

}

void Sound::playSound() {

	if (m_Psound) {

		PlaySound(std::wstring(m_sound.begin(), m_sound.end()).c_str(), NULL, SND_FILENAME | SND_ASYNC);

	}

}

void Sound::playMusic() {

	if (m_Pmusic) {
		
		PlaySound(std::wstring(m_music.begin(), m_music.end()).c_str(), NULL, SND_FILENAME | SND_ASYNC);

	}

}

void Sound::stopMusic() {

	

}

void Sound::stopSound() {



}

void Sound::toggleMusic() {

	if (!m_Pmusic) {

		m_Pmusic = true;	
		playMusic();
	
	} else {

		m_Pmusic = false;
		stopMusic();

	}

}

void Sound::toggleSound() {

	if (!m_Psound) {

		m_Psound = true;

		playSound();

	} else {

		m_Psound = false;

		stopSound();

	}

}

void Sound::setMusicOpt(bool value) {

	m_Pmusic = value;

}

void Sound::setSoundOpt(bool value) {

	m_Psound = value;

}
