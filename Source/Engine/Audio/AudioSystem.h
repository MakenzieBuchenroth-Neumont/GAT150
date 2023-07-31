#pragma once
#include <fmod/core/inc/fmod.hpp>
#include <string>
#include <map>

namespace neko {
	class AudioSystem {
	public:
		AudioSystem() = default;
		~AudioSystem() = default;
		bool initialize();
		void shutdown();
		void update();
		void addAudio(const std::string& name, const std::string& filename);
		void playOneShot(const std::string& name, bool loop = false);
		void stopSound(const std::string& name);

	private:
		FMOD::System* m_fmodSystem;
		std::map<std::string, FMOD::Sound*> m_sounds;
	};

	extern AudioSystem g_audioSystem;
}