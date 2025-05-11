// ================================================================================================
// File: Game.cpp
// Author: Luka Vukorepa (https://github.com/lukav1607)
// Created: ...
// ================================================================================================
// License: MIT License
// Copyright (c) 2025 Luka Vukorepa
// ================================================================================================

#include <SFML/Graphics.hpp>
#include "Game.hpp"

Game::Game()
{
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;
	window.create(sf::VideoMode(sf::Vector2u(800, 600)), PROJECT_NAME, sf::Style::Close, sf::State::Windowed, settings);
	window.setVerticalSyncEnabled(true);
}

int Game::run()
{
	const float FIXED_TIME_STEP = 1.f / 60.f; // Fixed time step per update
	sf::Clock clock;						  // Clock to measure time
	float timeSinceLastUpdate = 0.f;		  // Time accumulator for fixed timestep
	float interpolationFactor = 0.f;		  // Interpolation factor for rendering

	while (window.isOpen())
	{
		timeSinceLastUpdate += clock.restart().asSeconds();
		processInput();

		while (timeSinceLastUpdate >= FIXED_TIME_STEP)
		{
			update(FIXED_TIME_STEP);
			timeSinceLastUpdate -= FIXED_TIME_STEP;
		}

		interpolationFactor = timeSinceLastUpdate / FIXED_TIME_STEP;
		render(interpolationFactor);
	}
	return 0;
}

void Game::processInput()
{
	// Handle window events regardless of current game state
	while (const std::optional event = window.pollEvent())
		if (event->is<sf::Event::Closed>())
			window.close();

	// Input code here
}

void Game::update(float fixedTimeStep)
{
	// Update code here
}

void Game::render(float interpolationFactor)
{
	window.clear();

	// Render code here

	window.display();
}