#include <iostream>
#include <thread>
#include <memory>
#include <cassert>
#include <array>
#include <map>

#include "Core/Core.h"
#include "Input/InputSystem.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Audio/AudioSystem.h"

#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/Particle.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Texture.h"

#include "Framework/Emitter.h"

#include "H_AsteroidField.h"
#include "Star.h"

using namespace std;

int main(int argc, char* argv[]) {
	// pre setup
	INFO_LOG("Hello World");


	// initialize memory tracker, set random seed and set file path
	neko::MemoryTracker::initialize();
	neko::seedRandom((unsigned int)time(nullptr));
	neko::setFilePath("Assets");

	// create the game window
	neko::g_renderer.initialize();
	neko::g_renderer.createWindow("CSC196", 800, 600);

	// initialize game
	unique_ptr<H_AsteroidField> game = make_unique<H_AsteroidField>();
	game->initialize();

	//create texture
	shared_ptr<neko::Texture> texture = make_shared<neko::Texture>();
	texture->load("balloonBoy.png", neko::g_renderer);

	// main game loop
	bool quit = false;
	while (!quit) {
		//update engine
		neko::g_time.tick();
		neko::g_inputSystem.update();
		neko::g_audioSystem.update();
		neko::g_particleSystem.update(neko::g_time.getDeltaTime());
		if (neko::g_inputSystem.getKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		// update game
		game->update(neko::g_time.getDeltaTime());

		// input system
		if (neko::g_inputSystem.getMouseButtonDown(0)) {
			cout << "mouse pressed" << endl;
		}


		// draw game
		neko::g_renderer.setColor(0, 0, 0, 255);
		neko::g_renderer.beginFrame();

		game->draw(neko::g_renderer);
		neko::g_renderer.drawTexture(texture.get(), 200.0f, 200.0f, 0.0f);
		neko::g_renderer.endFrame();

	}
		return 0;
}



//Memory tracker
	/*neko::g_memoryTracker.displayInfo();
int* p = new int;
neko::g_memoryTracker.displayInfo();
delete p;
neko::g_memoryTracker.displayInfo();

neko::Time timer;
for (int i = 0; i < 10000000; i++) {}
cout << timer.GetElapsedSeconds() << endl;*/
//Chrono clock
	/*auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000000000; i++) { }
	auto end = std::chrono::high_resolution_clock::now();

	/*cout << (end - start).count() << endl;
	cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << endl;*/
//FileIO test
	/*cout << neko::getFilePath() << endl;
	neko::setFilePath("Assets");
	cout << neko::getFilePath() << endl;
	size_t size;
	neko::getFileSize("game.txt", size);
	cout << size << endl;

	/*std::string s;
	neko::readFile("game.txt", s);
	cout << s << endl;*/
//Random test
	/*neko::seedRandom((unsigned int)time(nullptr));
	for (int i = 0; i < 10; i++) {
		cout << neko::random(5, 10) << endl;
	}*/