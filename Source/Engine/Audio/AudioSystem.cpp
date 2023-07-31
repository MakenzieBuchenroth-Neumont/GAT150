#include "AudioSystem.h"
namespace neko {

	AudioSystem g_audioSystem;

	bool AudioSystem::initialize() {
		FMOD::System_Create(&m_fmodSystem);
		void* extradriverdata = nullptr;
		m_fmodSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
		return true;
	}

	void AudioSystem::shutdown() {
		for (auto sound : m_sounds) sound.second->release();
		m_sounds.clear();
		m_fmodSystem->close();
		m_fmodSystem->release();
	}

	void AudioSystem::update() {
		m_fmodSystem->update();
	}

	void AudioSystem::addAudio(const std::string& name, const std::string& filename) {
		if (m_sounds.find(name) == m_sounds.end()) {
			FMOD::Sound* sound = nullptr;
			m_fmodSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
			m_sounds[name] = sound;
		}
	}

	void AudioSystem::playOneShot(const std::string& name, bool loop) {
		auto iter = m_sounds.find(name);
		if (iter != m_sounds.end()) {
			FMOD::Sound* sound = iter->second;

			sound->setMode(loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);

			FMOD::Channel* channel;
			m_fmodSystem->playSound(sound, 0, false, &channel);
		}
	}

	void AudioSystem::stopSound(const std::string& name) {
		auto iter = m_sounds.find(name);
		if (iter != m_sounds.end()) {
			FMOD::Sound* sound = iter->second;
			sound->release(); // Release the sound to stop it from playing
			m_sounds.erase(iter);
		}

	}
}
