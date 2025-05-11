// ================================================================================================
// File: SoundManager.hpp
// Author: Luka Vukorepa (https://github.com/lukav1607)
// Created: ...
// Description: Defines the SoundManager class, which is responsible for managing sound effects in the game.
// ================================================================================================
// License: MIT License
// Copyright (c) 2025 Luka Vukorepa
// ================================================================================================

#pragma once

#include <memory>
#include <unordered_map>
#include <SFML/Audio.hpp>

class SoundManager
{
public:
	SoundManager() { loadSounds(); }
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;

	enum class SoundID
	{
		PLACEHOLDER_ID
	};

	// Removes any sounds that are no longer playing every `interval` seconds
	void cleanupSounds(float fixedTimeStep, float interval = 30.f);

	// Play a sound with optional base pitch, pitch random variation and individual volume scaling.
	// - `basePitch`: Base pitch of the sound (default = 1.0)
	// - `pitchVariancePercentage`: Percent pitch variation from `basePitch`, for example: 0.15f == +/-15%
	// - `localVolume`: Volume for this sound (0.f = mute, 100.f = full), scaled by SoundManager::volume
	// The final volume is: localVolume * (SoundManager::volume / 100)
	void playSound(SoundID soundID, float pitchVariancePercentage = 0.f, float basePitch = 1.f, float localVolume = 100.f);

	float volume = 100.f; // Global volume for all sounds (0.f = mute, 100.f = full)

private:
	void loadSounds();

	std::unordered_map<SoundID, std::shared_ptr<sf::SoundBuffer>> soundBuffers;
	std::vector<std::shared_ptr<sf::Sound>> activeSounds;
};