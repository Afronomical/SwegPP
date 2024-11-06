#pragma once
#include "../Components/Component.h"
#include "Particle.h"

class Particle;

class Emitter : public Component
{
private:

	int radius;
	int maxParticles;

public:

	/// <summary>
	/// Spawns, moves and removes a single particle
	/// To be used in a loop
	/// </summary>
	/// <param name="range"> How far each particle travels </param>
	/// <param name="duration"> Duration of the entire particle effect </param>
	/// <param name="particleCount"> Max amount of particles </param>
	/// <param name="texture"> What each particle looks like </param>
	/// <param name="position"> Origin point of particles </param>
	void EmitParticles(int range, float duration, int particleCount, const Asset& texture, const Vector2& position);
};

