#pragma once

#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"
#include "Particle.h"
#include "Random.h"
#include "ETime.h"
#include "Color.h"
#include "MathUtils.h"
#include "Model.h"
#include "Transform.h"
#include "Audio.h"
#include "Text.h"
#include "Font.h"


#include <SDL.h>
#include <SDL_ttf.h>

class Engine {

public:
	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	Renderer& GetRenderer() { return *m_renderer; }
	Audio& GetAudio() { return *m_audio; }
	Input& GetInput() { return *m_input; }

private:

	Renderer* m_renderer;
	Input* m_input;
	Audio* m_audio;


};

extern Engine g_engine;