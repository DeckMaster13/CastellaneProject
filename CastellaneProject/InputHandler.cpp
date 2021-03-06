#include "InputHandler.h"

#include <SDL2/SDL.h>
#include "Renderer.h"
#include <vector>
#include <iostream>

//TODO: rework this part !

static Vector2D *mouseCoordinates{ new Vector2D(0, 0) };
static std::vector<bool> mouseButtonStates (3, false);
static const Uint8 *keyboardState{ nullptr };
static bool quit{ false };
static bool windowResized{ false };

void InputHandler::updateInputs()
{
	keyboardState = SDL_GetKeyboardState(0);
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		//cout << "event.type: " << event.type << endl;
		switch (event.type)
		{
		case SDL_QUIT:
			InputHandler::onQuit();
			break;

		//case SDL_WINDOWEVENT_RESIZED:
		//case SDL_WINDOWEVENT_SIZE_CHANGED:
		case 8192://experimental
			//doesnt work
			InputHandler::onWindowResized();
			cout << "BEUUUUUUUUUUH !" << endl;
			break;

		case SDL_MOUSEMOTION:
			InputHandler::onMouseMove(event);
			break;

		case SDL_MOUSEBUTTONDOWN:
		{
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouseButtonStates[LEFT] = true;
				break;
			case SDL_BUTTON_MIDDLE:
				mouseButtonStates[MIDDLE] = true;
				break;
			case SDL_BUTTON_RIGHT:
				mouseButtonStates[RIGHT] = true;
				break;
			}
			break;
		}
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouseButtonStates[LEFT] = false;
				break;
			case SDL_BUTTON_MIDDLE:
				mouseButtonStates[MIDDLE] = false;
				break;
			case SDL_BUTTON_RIGHT:
				mouseButtonStates[RIGHT] = false;
				break;
			}
			break;
		default:
			break;
		}
	}
}

void InputHandler::onMouseMove(SDL_Event &event)
{
	mouseCoordinates->set(event.motion.x, event.motion.y);
	//std::cout << "onMouseMove: " << mouseCoordinates->getX() << "," << mouseCoordinates->getY() << "\n";
}

void InputHandler::onQuit()
{
	quit = true;
}

bool InputHandler::askedForQuit()
{
	return quit;
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
	if (keyboardState)
		return keyboardState[key];
	return false;
}

bool InputHandler::isWindowResized()
{
	bool res = windowResized;
	windowResized = false;
	return res;
}

void InputHandler::onWindowResized()
{
	windowResized = true;
}

Vector2D InputHandler::getMouseCoordinates()
{
	return *mouseCoordinates;
}

bool InputHandler::getMouseButtonsStates(mouseButtonType buttonType)
{
	return mouseButtonStates[buttonType];
}
