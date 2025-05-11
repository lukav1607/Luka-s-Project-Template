// ================================================================================================
// File: SoundManager.cpp
// Author: Luka Vukorepa (https://github.com/lukav1607)
// Created: ...
// ================================================================================================
// License: MIT License
// Copyright (c) 2025 Luka Vukorepa
// ================================================================================================

#include <iostream>
#include <algorithm>
#include "SoundManager.hpp"
#include "../core/Utility.hpp"

void SoundManager::loadSounds()
{
	auto load = [&](SoundID soundID, const std::string& filename)
		{
			soundBuffers[soundID] = std::make_shared<sf::SoundBuffer>(filename);
		};

	// Load sound files here:
	//load(SoundID::PLACEHOLDER_ID, "assets/sounds/PLACEHOLDER_FILE_NAME.FORMAT");
}


void SoundManager::playSound(SoundID soundID, float pitchVariancePercentage, float basePitch, float localVolume)
{
	auto it = soundBuffers.find(soundID);
	if (it != soundBuffers.end())
	{
		auto sound = std::make_shared<sf::Sound>(*it->second);

		// Set pitch
		if (pitchVariancePercentage < 0.f || pitchVariancePercentage > 1.f)
		{
			std::cerr << "Warning: Pitch variance percentage must be between 0 and 1! Pitch variance set to default (0%)" << std::endl;
			pitchVariancePercentage = 0.f;
		}
		if (pitchVariancePercentage != 0.f)
			sound->setPitch(Utility::randomPitch(pitchVariancePercentage, basePitch));
		else
			sound->setPitch(basePitch);

		// Set volume
		if (localVolume < 0.f || localVolume > 100.f)
		{
			std::cerr << "Warning: Volume override must be between 0 and 100! Volume override set to default (100%)" << std::endl;
			localVolume = 100.f;
		}
		float actualVolume = localVolume * (volume / 100.f);
		sound->setVolume(actualVolume);

		sound->play();
		activeSounds.push_back(sound);
	}
	else
	{
		std::cerr << "Error: Sound ID not found!" << std::endl;
	}
}

void SoundManager::cleanupSounds(float fixedTimeStep, float interval)
{
	static float timeSinceLastCleanup = 0.f;
	timeSinceLastCleanup += fixedTimeStep;

	if (timeSinceLastCleanup >= interval)
	{
		timeSinceLastCleanup = 0.f;

		activeSounds.erase(
			std::remove_if(activeSounds.begin(), activeSounds.end(),
				[](const std::shared_ptr<sf::Sound>& sound) {
					return sound->getStatus() == sf::Sound::Status::Stopped;
				}),
			activeSounds.end());
	}
}