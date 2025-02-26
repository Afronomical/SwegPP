#pragma once

#include "../Components/Component.h"
#include "../AssetLoading/AssetHandler.h"
#include "../Maths/Maths.h"
#include "../Time/Time.h"
#include "../GameObject/GameObject.h"
#include "../Components/Transform.h"

class Particle : public GameObject
{
private:

	float pLifeTime = 0;
	float pSpeed = 0;
	//Vector2 pos;

public:

	using GameObject::GameObject;
	~Particle() override {};

	//Particle(float lifeTime, float size, const Asset& texture, const Vector2& position);
	Particle(float lifeTime);

	void Draw(const Asset& texture, const Vector2& position, float size);

	//Getters
	float GetLifetime() const { return pLifeTime; };
	float GetSpeed() const { return pSpeed; };
	Vector2 GetPosition() { return this->GetComponent<Transform>().lock()->position; };

	// Setters
	void SetLifetime(float duration) { pLifeTime = duration; };
	void SetSpeed(float speed) { pSpeed = speed; };
	void SetPosition(Vector2 pos) { this->GetComponent<Transform>().lock()->position = pos; };

	/// <summary>
	/// Spawns, moves and removes a single particle
	/// To be used in a loop
	/// </summary>
	/// <param name="range"> How far each particle travels </param>
	/// <param name="duration"> Duration of the entire particle effect </param>
	/// <param name="particleCount"> Max amount of particles </param>
	/// <param name="texture"> What each particle looks like </param>
	/// <param name="position"> Origin point of particles </param>
	//void StartParticleSystem(int range, float duration, int particleCount, const Asset& texture, const Vector2& position);
};

