#include "PlayState.h"

#include <algorithm>
#include <iostream>
#include <SDL2/SDL_image.h>

#include "Constants.h"
#include "InputHandler.h"
#include "Renderer.h"
#include "TextureHandler.h"

//beurk !
bool isLeftButtonClicked{ false };
bool isLeftButtonReleased{ true };
bool isRightButtonClicked{ false };
bool isRightButtonReleased{ true };

bool isRobotPlaying{false};

std::string currentConfigFileName;

PlayState::PlayState()
{}

void PlayState::update()
{
	GameState::update();
}

void PlayState::render()
{
	GameState::render();
	SDL_RenderPresent(Renderer::Instance().getRenderer());
}

void PlayState::init()
{}

bool PlayState::onEnter()
{

	//TEMPORARY
   //texture black/white

    SDL_Surface *image = IMG_Load("sprites/chess_tile.png");
	SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer::Instance().getRenderer(), image);
	std::string textureID = "chessTiles";
	TextureHandler::registerTexture(textureID, texture);
	SDL_FreeSurface(image);

   //texture green
   image = IMG_Load("sprites/chess_tile_lighted.png");
   texture = SDL_CreateTextureFromSurface(Renderer::Instance().getRenderer(), image);
   textureID = "chessTilesGreen";
   TextureHandler::registerTexture(textureID, texture);
   SDL_FreeSurface(image);

   //texture red
   image = IMG_Load("sprites/chess_tile_lighted_red.png");
   texture = SDL_CreateTextureFromSurface(Renderer::Instance().getRenderer(), image);
   textureID = "chessTilesRed";
   TextureHandler::registerTexture(textureID, texture);
   SDL_FreeSurface(image);

   //texture yellow
   image = IMG_Load("sprites/chess_tile_lighted_yellow.png");
   texture = SDL_CreateTextureFromSurface(Renderer::Instance().getRenderer(), image);
   textureID = "chessTilesYellow";
   TextureHandler::registerTexture(textureID, texture);
   SDL_FreeSurface(image);

   //texture orange
   image = IMG_Load("sprites/chess_tile_lighted_orange.png");
   texture = SDL_CreateTextureFromSurface(Renderer::Instance().getRenderer(), image);
   textureID = "chessTilesOrange";
   TextureHandler::registerTexture(textureID, texture);
   SDL_FreeSurface(image);

   init();

	return true;
}

bool PlayState::onExit()
{
	//std::cout << "exiting PlayState\n";
	for (auto& object : m_stateGameObjects)
		delete object;
	return true;
}


//beurk
static bool isArrowStillDown(SDL_Scancode arrowKey, bool& isArrowDown)
{
	if (isArrowDown)
	{
		if (!InputHandler::isKeyDown(arrowKey)) isArrowDown = false;
		else return true;
	}
	return false;
}

void PlayState::handleInputs()
{
	GameState::handleInputs();

	isLeftButtonClicked = InputHandler::getMouseButtonsStates(mouseButtonType::LEFT);
	if (isLeftButtonClicked)
	{

		if (isLeftButtonReleased)
		{
			isLeftButtonReleased = false;
		}
	}
	else
	{
		isLeftButtonReleased = true;
	}

	isRightButtonClicked = InputHandler::getMouseButtonsStates(mouseButtonType::RIGHT);
	if (isRightButtonClicked)
	{

		if (isRightButtonReleased)
		{
			isRightButtonReleased = false;
			isRobotPlaying = !isRobotPlaying;
		}
	}
	else
	{
		isRightButtonReleased = true;
	}

	/*if (isArrowStillDown(SDL_SCANCODE_RIGHT, isRightArrowDown)
		|| isArrowStillDown(SDL_SCANCODE_LEFT, isLeftArrowDown)
		|| isArrowStillDown(SDL_SCANCODE_UP, isUpArrowDown)
		|| isArrowStillDown(SDL_SCANCODE_DOWN, isDownArrowDown)
		) return;
      */
}
