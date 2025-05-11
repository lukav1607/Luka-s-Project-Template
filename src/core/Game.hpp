// ================================================================================================
// File: Game.hpp
// Author: Luka Vukorepa (https://github.com/lukav1607)
// Created: ...
// Description: Defines the Game class, which contains the main game loop and manages the game state.
// ================================================================================================
// License: MIT License
// Copyright (c) 2025 Luka Vukorepa
// ================================================================================================

#pragma once

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../audio/SoundManager.hpp"

class Game
{
public:
	Game();
	int run();

private:
	const std::string PROJECT_NAME = "LVProjectTemplate";

	void processInput();
	void update(float fixedTimeStep);
	void render(float interpolationFactor);

	sf::RenderWindow window;
	SoundManager soundManager;
};