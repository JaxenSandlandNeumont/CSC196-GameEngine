#include "Input.h"
#include <SDL.h>
#include <iostream>

bool Input::Initialize()
{
	int numKeys;
	const uint8_t* keyBoardState = SDL_GetKeyboardState(&numKeys);

	m_keyboardState.resize(numKeys);

	// Copy curent keyboard state into our keyboard state
	std::copy(keyBoardState, keyBoardState + numKeys, m_keyboardState.begin());
	m_prevKeyboardState = m_keyboardState;

	return true;
}

void Input::Shutdown()
{

}

void Input::Update()
{


	// keyboard input
	m_prevKeyboardState = m_keyboardState;
	const uint8_t* keyBoardState = SDL_GetKeyboardState(nullptr);
	std::copy(keyBoardState, keyBoardState + m_keyboardState.size(), m_keyboardState.begin());

	int x, y;
	uint32_t buttonState = SDL_GetMouseState(&x, &y);

	m_mousePosition.x = (float)x;
	m_mousePosition.y = (float)y;
	//std::cout << m_mousePosition.x << " " << m_mousePosition.y << "\n";

	m_prevMouseButtonState = m_mouseButtonState;

	m_mouseButtonState[0] = buttonState & SDL_BUTTON_LMASK;
	m_mouseButtonState[1] = buttonState & SDL_BUTTON_MMASK;
	m_mouseButtonState[2] = buttonState & SDL_BUTTON_RMASK;
}
